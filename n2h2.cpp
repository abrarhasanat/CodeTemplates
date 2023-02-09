#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include<cstdlib>
#include<time.h>
#include<unistd.h>

int moleculeCount = 0;
int hydrogenCount = 0;
int currentTemp = 100;
int MIN_TEMP = 100;
int MAX_THREAD = 1000;
pthread_mutex_t mutex, temp_lock;
pthread_cond_t hydrogenCond;
pthread_cond_t oxygenCond;
pthread_cond_t tempWaiting;


void bond(void) {
    printf("A water molecule was formed\n");
    printf("h2 : %d\t o2 : %d\n", hydrogenCount, moleculeCount);

}

void* updateTemp(void* arg) {
    while (true) {
        int res = rand() % 10;
        int incr = rand() % 50;
        int ntemp = currentTemp;
        if (currentTemp > 100) {
            if (res <= 8) ntemp -= incr;
            else ntemp += incr;
        }
        else {
            if (res <= 8) ntemp += incr;
            else ntemp -= incr;
        }
        sleep(1);
        pthread_mutex_lock(&mutex);
        currentTemp = ntemp;
        printf("temperture has been updated to %d\n", currentTemp);
        if (currentTemp >= MIN_TEMP) {
            pthread_cond_broadcast(&tempWaiting);
        }
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void* oxygen(void* arg) {
    pthread_mutex_lock(&mutex);
    while (true) {
        moleculeCount++;
        printf("a new o2 has come; Total count %d\n ", moleculeCount);
        while (hydrogenCount < 2) {
            pthread_cond_wait(&hydrogenCond, &mutex);
        }
        //
        while (currentTemp < MIN_TEMP) {
            pthread_cond_wait(&tempWaiting, &mutex);
        }
        if (moleculeCount > 0 and hydrogenCount > 1) {
            hydrogenCount -= 2;
            moleculeCount--;
            bond();
        }
        pthread_cond_broadcast(&oxygenCond);
        break;
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* hydrogen(void* arg) {
    pthread_mutex_lock(&mutex);
    while (true) {
        hydrogenCount++;
        printf("a new h2 has come: total count %d\n", hydrogenCount);
        while (moleculeCount < 1 || hydrogenCount < 2) {
            pthread_cond_wait(&oxygenCond, &mutex);
        }
        while (currentTemp < MIN_TEMP) {
            pthread_cond_wait(&tempWaiting, &mutex);
        }
        if (moleculeCount > 0 and hydrogenCount > 1) {
            moleculeCount--;
            hydrogenCount -= 2;
            bond();
        }
        pthread_cond_broadcast(&hydrogenCond);
        break;
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}



int main(int argc, char* argv[]) {
    pthread_t h1, h2, h3, o1, o2;
    pthread_t h[MAX_THREAD];
    pthread_t o[MAX_THREAD];
    pthread_t update;
    pthread_t initializer;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&hydrogenCond, NULL);
    pthread_cond_init(&oxygenCond, NULL);
    pthread_cond_init(&tempWaiting, NULL);


    pthread_create(&update, NULL, updateTemp, NULL);
    int h_index = 0, o_index = 0;
    while (h_index < MAX_THREAD or o_index < MAX_THREAD) {
        if (h_index >= MAX_THREAD) {
            while (o_index < MAX_THREAD) {
                sleep(1);
                pthread_create(&o[o_index], NULL, oxygen, NULL);
                ++o_index;
            }
        }

        else if (o_index >= MAX_THREAD) {
            while (h_index < MAX_THREAD) {
                sleep(1);
                pthread_create(&h[h_index], NULL, hydrogen, NULL);
                ++h_index;
            }
        }
        else {
            int res = rand() % 2;
            sleep(1);
            if (res == 0) {
                pthread_create(&h[h_index], NULL, hydrogen, NULL);
                ++h_index;
            }
            else {
                pthread_create(&o[o_index], NULL, oxygen, NULL);
                ++o_index;

            }
        }
    }
    // pthread_create(&h1, NULL, hydrogen, NULL);
    // pthread_create(&h2, NULL, hydrogen, NULL);
    // pthread_create(&o1, NULL, oxygen, NULL);
    // pthread_create(&h3, NULL, hydrogen, NULL);
    // pthread_create(&o2, NULL, oxygen, NULL);

    // pthread_join(h1, NULL);
    // pthread_join(h2, NULL);
    // pthread_join(h3, NULL);
    // pthread_join(o1, NULL);
    // pthread_join(o2, NULL);

    for (int i = 0; i < MAX_THREAD; ++i) {
        pthread_join(h[i], NULL);
    }

    for (int i = 0; i < MAX_THREAD; ++i) {
        pthread_join(o[i], NULL);
    }

    pthread_join(update, NULL);
    pthread_cond_destroy(&hydrogenCond);
    pthread_cond_destroy(&oxygenCond);
    pthread_cond_destroy(&tempWaiting);
    pthread_mutex_destroy(&mutex);

    return 0;
}
