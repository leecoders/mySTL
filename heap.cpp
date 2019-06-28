#include <stdio.h>

const int MAX_SIZE = 1000001;

// MAX_HEAP
struct MY_HEAP {
    int heap_size;
    int heap[MAX_SIZE]; // heap_size와 싱크를 맞추기 위해 0은 비워둔다.
    
    MY_HEAP() {
        heap_size = 0;
    }
    
    void push(int data) {
        int target = heap_size + 1;
        while (target != 1 && heap[target / 2] < data) { // data가 부모보다 크다면 (target이 0이 되는 UB를 조심하자)
            heap[target] = heap[target / 2]; // 부모만 밑으로 내림(swap은 마지막에 하면 되니까)
            target /= 2; // 한 칸 올라감
        }
        heap[target] = data;
        ++heap_size;
    }
    
    void pop() {
        int parent = 1, child = 2; // 부모를 루트, 자식은 왼쪽으로 초기화. 오른쪽/왼쪽 모르기 때문에 child 변수도 필요
        int temp = heap[heap_size]; // 맨 마지막 요소를 임시 저장
        while (child < heap_size) {
            if (child + 1 < heap_size && heap[child] < heap[child + 1]) { // 둘 중 더 큰 자식을 위로 올리기 위함
                ++child;
            }
            if (temp >= heap[child]) { // 더 이상 child를 위로 올리지 않아도 된다는 뜻
                break;
            }
            heap[parent] = heap[child]; // child를 한 칸 올림
            parent = child; // 다음 반복에 사용할 parent
            child *= 2; // 다음 반복에 사용할 child
        }
        heap[parent] = temp; // 결국 parent가 pop()에서의 마지막 target이 됨
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
