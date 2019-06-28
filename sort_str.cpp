#include <stdio.h>

const int MAX_SIZE = 10000;

char str[MAX_SIZE][100], buf[MAX_SIZE][100];
int n;

void my_strcpy(char a[], char b[]);

void swap(char a[], char b[]) {
    char temp[100];
    my_strcpy(temp, a);
    my_strcpy(a, b);
    my_strcpy(b, temp);
}

int my_strcmp(char a[], char b[]) {
    int i = 0, j = 0;
    while(a[i]) {
        if(a[i++] != b[j++]) {
            --i, --j;
            break;
        }
    }
    return a[i] - b[j];
}

void my_strcpy(char a[], char b[]) { // 문자열은 사실 포인터 형이다!
    int i;
    for(i=0; b[i] != 0; ++i) {
        a[i] = b[i];
    }
    a[i] = 0;
}

void qsort(char v[][100], int left, int right) {
    if(left >= right) return;
    int l = left - 1;
    int r = right + 1;

    int mid_idx = (l + r) / 2;

    char mid[100];
    int i;
    for(i=0; v[mid_idx][i] != 0; ++i) {
        mid[i] = v[mid_idx][i];
    }
    mid[i] = 0;

    while(1) {
        while(my_strcmp(v[++l], mid) < 0);
        while(my_strcmp(v[--r], mid) > 0);
        if(l >= r) break;
        swap(v[l], v[r]);
    }
    qsort(v, left, l - 1);
    qsort(v, r + 1, right);
}

void merge_sort(char v[][100], int len) {
    if(len < 2) return;
    int mid = len / 2;
    int i=0, j = mid, k=0;

    merge_sort(v, mid);
    merge_sort(v + mid, len - mid);

    while(i < mid && j < len) {
        if(my_strcmp(v[i], v[j]) < 0) {
            my_strcpy(buf[k++], v[i++]);
        }
        else {
            my_strcpy(buf[k++], v[j++]);
        }
    }
    while(i < mid) {
        my_strcpy(buf[k++], v[i++]);
    }
    while(j < len) {
        my_strcpy(buf[k++], v[j++]);
    }
    for(int i=0; i<len; ++i) {
        my_strcpy(v[i], buf[i]);
    }
}

int main() {
    scanf("%d", &n);
    for(int i=0; i<n; ++i) {
        scanf("%s", str[i]);
    }
    merge_sort(str, n);
    for(int i=0; i<n; ++i) {
        printf("%s\n", str[i]);
    }
}
