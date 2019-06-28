#include <stdio.h>

const int MAX_SIZE = 1000001;

// MAX_HEAP
struct MY_HEAP {
    int heap_size;
    int heap[MAX_SIZE];
    
    MY_HEAP() {
        heap_size = 0;
    }
    
    void push(int data) {
        int target = heap_size + 1;
        while (target != 1 && heap[target / 2] < data) {
            heap[target] = heap[target / 2];
            target /= 2;
        }
        heap[target] = data;
        ++heap_size;
    }
    
    void pop() {
        int parent = 1, child = 2;
        int temp = heap[heap_size];
        while (child < heap_size) {
            if (child + 1 < heap_size && heap[child] < heap[child + 1]) {
                ++child;
            }
            if (temp >= heap[child]) {
                break;
            }
            heap[parent] = heap[child];
            parent = child;
            child *= 2;
        }
        heap[parent] = temp;
        --heap_size;
    }
};

// MIN_HEAP
struct MY_MIN_HEAP {
    int heap_size;
    int heap[MAX_SIZE];
    
    MY_MIN_HEAP() {
        heap_size = 0;
    }
    
    void push(int data) {
        int target = heap_size + 1;
        while (target != 1 && heap[target / 2] > data) {
            heap[target] = heap[target / 2];
            target /= 2;
        }
        heap[target] = data;
        ++heap_size;
    }
    
    void pop() {
        int parent = 1, child = 2;
        int temp = heap[heap_size];
        while (child < heap_size) {
            if (child + 1 < heap_size && heap[child] > heap[child + 1]) {
                ++child;
            }
            if (temp <= heap[child]) {
                break;
            }
            heap[parent] = heap[child];
            parent = child;
            child *= 2;
        }
        heap[parent] = temp;
        --heap_size;
    }
};

MY_MIN_HEAP my_heap;

int main() {
    int n;
    scanf("%d", &n);
    for(int i=0; i<n; ++i) {
        int input;
        scanf("%d", &input);
        my_heap.push(input);
    }
    for(int i=1; i<=n; ++i) {
        printf("%d\n", my_heap.heap[1]);
        my_heap.pop(); // 이렇게 안하고 my_heap.heap[] 배열에 순차 접근하면 정렬 보장X. 왜? 형제 간에는 정렬 순서를 보장하지 않으니까.
    }
}
