#include <stdio.h>

struct MY_VECTOR {
    int _size;
    int capacity;
    
    int *arr;
    
    MY_VECTOR() {
        _size = 0;
        capacity = 32;
        arr = new int[capacity];
    }
    
    void resize(int k) {
        int *temp = new int[k];
        
        for(int i=0; i < _size; ++i) {
            temp[i] = arr[i];
        }
        delete[] arr; // 메모리 반환
        arr = temp; // 변수를 삭제하는 것처럼 보이지만 사실이 아니다! 포인터 변수는 여전히 이전과 동일한 범위를 가지며 다른 변수와 마찬가지로 새 값을 할당받을 수 있다.
        _size = capacity = k;
    }
    
    int size() const {
        return _size;
    }
    
    int* begin() const {
        return &arr[0];
    }
    
    int* end() const {
        return &arr[0] + _size;
    }
    
    void push_back(int data) {
        if(_size == capacity) {
            resize(_size * 2);
            _size /= 2;
        }
        arr[_size++] = data;
    }
    
    void pop_back() {
        _size--;
    }
    
    int& operator [](int idx) {
        return arr[idx];
    }
    
    int operator [](int idx) const {
        return arr[idx];
    }
};

int n;
MY_VECTOR my_vector;

int main() {
    scanf("%d", &n);
    for(int i=0; i<n; ++i) {
        int input;
        scanf("%d", &input);
        my_vector.push_back(input);
    }
    for(int i=0; i<n; ++i) {
        printf("%d ", my_vector[i]);
    }
}
