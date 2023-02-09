#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <cstdlib>

#define NUM_VALUES 10
#define MAX_CLIENTS 5

int values[NUM_VALUES];
pthread_mutex_t lock;
pthread_cond_t cond_read;
pthread_cond_t cond_update;
bool updating = false;
int reading = 0;

void* client_thread(void* arg) {
    int id = *((int*)arg);
    while (1) {
        int j = rand() % NUM_VALUES;
        int choice = rand() % 2;
        if (choice == 0) {
            pthread_mutex_lock(&lock);
            while (updating) {
                pthread_cond_wait(&cond_read, &lock);
            }
            ++reading;
            int value = values[j];
            printf("Client %d: read value[%d] = %d\n", id, j, value);
            --reading;
            if (reading == 0) {
                pthread_cond_signal(&cond_update);
            }
            pthread_mutex_unlock(&lock);
        }
        else {
            pthread_mutex_lock(&lock);
            while (reading) {
                pthread_cond_wait(&cond_update, &lock);
            }
            updating = true;
            int new_value = rand() % NUM_VALUES;
            values[j] = new_value;
            printf("Client %d: updated value[%d] = %d\n", id, j, new_value);
            printf("after updating the list is\n");
            for (int i = 0;i < NUM_VALUES; ++i) {
                printf("%d ", values[i]);
            }
            printf("\n");
            updating = false;
            pthread_cond_broadcast(&cond_read);
            pthread_cond_signal(&cond_update);
            pthread_mutex_unlock(&lock);

        }
        sleep(3);
    }
    return NULL;
}
int main(int argc, char* argv[]) {

    pthread_t client_tids[MAX_CLIENTS];
    int client_ids[MAX_CLIENTS];

    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond_read, NULL);
    pthread_cond_init(&cond_update, NULL);

    for (int i = 0; i < NUM_VALUES; i++) {
        values[i] = rand() % 100;
    }
    printf("initial value\n");
    for (int i = 0;i < NUM_VALUES; ++i) printf("%d ", values[i]);
    printf("\n");


    for (int i = 0; i < MAX_CLIENTS; i++) {
        client_ids[i] = i;
        pthread_create(&client_tids[i], NULL, client_thread, &client_ids[i]);
    }



    for (int i = 0; i < MAX_CLIENTS; i++) {
        pthread_join(client_tids[i], NULL);
    }

    pthread_cond_destroy(&cond_read);
    pthread_cond_destroy(&cond_update);
    pthread_mutex_destroy(&lock);
    return 0;
}