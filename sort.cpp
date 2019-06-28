#include <stdio.h>

const int MAX_SIZE = 1000000;

int ms[MAX_SIZE+1], qs[MAX_SIZE+1], buf[MAX_SIZE+1];

// qsort와 다르게 배열의 길이를 받음
// 왜? 전체 배열이 아닌 항상 같은 크기로 분할된 부분 배열을 넘겨받기 때문
void merge_sort(int *p, int len) {
    if(len < 2) return; // 1개로 쪼개질 때까지 분할! -> 합칠 일만 남음
    int i, j, k, mid;
    mid = len/2;
    i=0, j=mid, k=0; // k는 버퍼를 위한 인덱스
    
    merge_sort(p, mid); // qsort와 달리 쪼개는 것을 먼저함
    merge_sort((p + mid), (len - mid)); // (p+mid) is &p[mid]
    
    while(i < mid && j < len) { // 끝나면 보통 둘 중 하나는 끝까지 못 갔음
        if(p[i] < p[j]) {
            buf[k++] = p[i++];
        }
        else {
            buf[k++] = p[j++];
        }
    }
    while(i < mid) { // 뭔지 모르겠지만 남은 것 버퍼에 넣어줌
        buf[k++] = p[i++];
    }
    while(j < len) { // 얘도
        buf[k++] = p[j++];
    }
    for(int i=0; i<len; ++i) {
        p[i] = buf[i]; // p는 원 배열의 부분 배열이기 때문에 p[0] is
    }
}

void qsort(int *p, int left, int right) {
    if(left >= right) return; // left==right는 길이 1, left>right는 길이 2 이상. 종료
    int l = left - 1;
    int r = right + 1;
    int mid = p[(l+r) / 2]; // 중앙 값이 피벗. 하지만 인덱스가 아닌 값을 mid로 해야 한다. 왜? 사실 피벗을 기준으로 나눌 건 아니거든.
    while(1) {              // 오히려 l, r 교환의 종료 조건은 단지 l과 r의 l>=r일 때이다. (중요!!)
        while(p[++l] < mid); // mid보다 왼쪽인데 크거나 같은 요소 찾으면 stop
        while(p[--r] > mid); // mid보다 오른쪽인데 작거나 같은 요소 찾으면 stop
        if(l >= r) break;
        int temp = p[l];
        p[l] = p[r];
        p[r] = temp;
    }
    qsort(p, left, l-1); // l==r 일 때, 요소 한 개가 딸려가지 않아도 괜찮다.
    qsort(p, r+1, right);
}

int main() {
    int n;
    scanf("%d", &n);
    for(int i=0; i<n; ++i) {
        scanf("%d", &qs[i]);
    }
    merge_sort(qs, n);
    for(int i=0; i<n; ++i) {
        printf("%d\n", qs[i]);
    }
}
