#include<bits/stdc++.h>
#define debug(val) cout << val << endl;
using namespace std;
const int INF = 1e9;
class node {
public:
    int key;
    node* parent;
    node* child;
    node* sibling;
    int degree;
    node() {
        key = degree = -1;
        child = sibling = NULL;
    }
    node(int _key) {
        key = _key;
        degree = 0;
        child = parent = sibling = NULL;
    }


};

class binHeap {
    node* head;

public:
    binHeap() {
        head = NULL;
    }
    binHeap(node* _head) {
        head = _head;
    }
    bool isEmpty() {
        return head == NULL;
    }
    node* findMax() {
        node* temp = head;
        node* ans = NULL;
        int maxKey = -(INF);
        while (temp != NULL) {
            if (temp->key > maxKey) {
                maxKey = temp->key;
                ans = temp;
            }
            temp = temp->sibling;
        }
        return ans;
    }
    void print() {
        node* temp = head;
        int cnt = 1;
        cout << "\n\nprinting binomial heap...\n\n" << endl;
        while (temp != NULL) {/// at a  root of a binomial tree
            cout << "Binomial Tree, B" << cnt << endl;
            node* levelTemp = temp;
            int cnt2 = 1;
            cout << "Level 0: " << levelTemp->key << endl;
            levelTemp = levelTemp->child;
            while (levelTemp != NULL) { // traversing throgh a btree. usually indicates 
            // the first node on ith cnt2_th level;
                cout << "Level " << cnt2 << " : ";
                node* temp1 = levelTemp; /// nodes on a cnt2_th level;
                while (temp1 != NULL) {
                    cout << temp1->key << " ";
                    temp1 = temp1->sibling;
                }
                cout << endl;
                levelTemp = levelTemp->child;
                ++cnt2;
            }
            temp = temp->sibling; // moving to another tree
            ++cnt;
        }
    }

    void increaseKey(int prevKey, int newKey) {
        node* temp = head;
        node* target = NULL;
        while (temp != NULL) {
            node* levelTemp = temp;
            if (levelTemp->key == prevKey) {
                target = levelTemp;
                goto g;
            }
            levelTemp = levelTemp->child;
            while (levelTemp != NULL) {
                node* temp1 = levelTemp;
                while (temp1 != NULL) {
                    if (temp1->key == prevKey) {
                        target = temp1;
                        goto g;
                    }
                    temp1 = temp1->sibling;
                }
                levelTemp = levelTemp->child;
            }
            temp = temp->sibling;
        }
        if (target == NULL) {
            cout << "key does not exist" << endl;
            return;
        }
        g:
        target->key = newKey;


        node* par = target->parent;
        while (par != NULL) {
            if (target->key > par->key) {
                int tempKey = par->key;
                par->key = target->key;
                target->key = tempKey;
            }
            target = par;
            par = par->parent;
           


        }

    }




    // ~binHeap() {
    //     if (head != NULL)
    //         delete head;
    //     head = NULL;
    // }




    static binHeap  merge(binHeap h1, binHeap h2) {

        node* head1 = h1.head;
        node* head2 = h2.head;
        node* curr = NULL;
        node* prev = NULL;
        node* newHead = NULL;
        while (head1 != NULL and head2 != NULL) {
            if (head1->degree <= head2->degree) {
                curr = new node(head1->key);
                // curr->parent = prev;
                curr->sibling = NULL;
                curr->child = head1->child;
                curr->degree = head1->degree;
                head1 = head1->sibling;
            }
            else {
                curr = new node(head2->key);
                //  curr->parent = prev;
                curr->sibling = NULL;
                curr->child = head2->child;
                curr->degree = head2->degree;
                head2 = head2->sibling;
            }
            if (prev == NULL) newHead = curr;
            else prev->sibling = curr;
            prev = curr;
        }

        while (head1 != NULL) {
            curr = new node(head1->key);
            //  curr->parent = prev;
            curr->sibling = NULL;
            curr->child = head1->child;
            curr->degree = head1->degree;
            if (prev == NULL) newHead = curr;
            else prev->sibling = curr;
            prev = curr;

            head1 = head1->sibling;

        }

        while (head2 != NULL) {
            curr = new node(head2->key);
            // curr->parent = prev;
            curr->sibling = NULL;
            curr->child = head2->child;
            curr->degree = head2->degree;
            if (prev == NULL) newHead = curr;
            else prev->sibling = curr;
            prev = curr;

            head2 = head2->sibling;

        }

        binHeap h(newHead);
        return h;
    }


    static binHeap Union(binHeap h1, binHeap h2) {
        if (h1.head == NULL) {
            node* x = h2.getHead();
            node* temp = new node(x->key);
            temp->child = x->child;
            temp->sibling = x->sibling;
            temp->parent = NULL;
            temp->degree = x->degree;
            binHeap h(temp);
            return  h;
        }
        if (h2.head == NULL) {
            node* x = h1.getHead();
            node* temp = new node(x->key);
            temp->child = x->child;
            temp->sibling = x->sibling;
            temp->parent = NULL;
            temp->degree = x->degree;
            binHeap h(temp);
            return h;
        }
        binHeap h = merge(h1, h2);
        if (h.head == NULL) return NULL;
        node* prev = NULL;
        node* curr = h.head;
        node* next = curr->sibling;
        node* newHead = NULL;
        while (next != NULL) {
            if (curr->degree != next->degree) {

                prev = curr;
                curr = next;
                next = next->sibling;

            }
            else if (next->sibling != NULL and curr->degree == (next->sibling)->degree) {
                prev = curr;
                curr = next;
                next = next->sibling;
            }

            else if (curr->key > next->key) {
                curr->sibling = next->sibling;
                next->parent = curr;
                next->sibling = curr->child;
                curr->child = next;
                curr->degree++;
                next = curr->sibling;

            }
            else {
                curr->parent = next;
                curr->sibling = next->child;
                next->child = curr;
                next->degree++;
                if (prev == NULL) h.head = next;
                else prev->sibling = next;
                curr = next;
                next = next->sibling;
            }


        }
        //node* temp = h.head;
        // while (temp != NULL) {
        //     temp->parent = NULL;
        //     temp = temp->sibling;
        // }

        return h;
    }

    node* extractMax() {
        if (head == NULL) return NULL;
        node* curr = head;
        node* prev = NULL;
        node* minNode = NULL;
        node* prevOfMinNode = NULL;
        node* nextOfMinNode = NULL;
        int maxKey = -INF;
        while (curr != NULL) {
            if (curr->key > maxKey) {
                maxKey = curr->key;
                prevOfMinNode = prev;
                nextOfMinNode = curr->sibling;
                minNode = curr;
            }
            prev = curr;
            curr = curr->sibling;
        }



        binHeap h1;
        if (prevOfMinNode == NULL and nextOfMinNode != NULL) {
            h1.head = nextOfMinNode;
        }
        else if (prevOfMinNode != NULL and nextOfMinNode == NULL) {
            h1.head = head;
            prevOfMinNode->sibling = NULL;
        }
        else if (prevOfMinNode != NULL and nextOfMinNode != NULL) {
            h1.head = head;
            prevOfMinNode->sibling = nextOfMinNode;
        }
        else {
            h1.head = NULL;
        }



        stack<node*>st;
        node* childs = minNode->child;
        node* root = NULL;
        while (childs != NULL) {
            root = childs;
            st.push(childs);
            childs = childs->sibling;
        }
        curr = root;
        while (!st.empty()) {
            if (curr != NULL)
                curr->sibling = st.top();
            curr = st.top();
            st.pop();
        }
        if (curr != NULL)
            curr->sibling = NULL;
        curr = root;
        binHeap h2(root);
        if (h1.head == NULL and h2.head == NULL) this->head = NULL;
        else {
            binHeap  h = Union(h1, h2);
            head = h.head;
        }
        return minNode;
    }


    void fff() {
        node* temp = head;
        while (temp != NULL) {
            cout << temp->key << " " << temp->child << endl;
            temp = temp->sibling;

        }
    }
    node* getHead() {
        return head;
    }
};
binHeap h1;
void insert(int key) {
    node* temp = new node(key);
    binHeap h2(temp);
    h1 = binHeap::Union(h1, h2);
}
int main() {
    while (true) {
        string s;  cin >> s;
        if (s == "INS") {
            int key; cin >> key;
            insert(key);
            cout << "Inserted " << key << endl;
        }
        if (s == "PRI") {
            h1.print();
        }
        if (s == "FIN") {
            cout << "FindMax returned " << h1.findMax()->key << endl;
        }
        if (s == "EXT") {
            cout << "ExtractMax returned " << h1.extractMax()->key << endl;
        }
        if (s == "INC") {
            int prev, next; cin >> prev >> next;
            h1.increaseKey(prev, next);
            cout << "Increased " << prev << ". The updated value is " << next << "." << endl;
        }


    }

}

