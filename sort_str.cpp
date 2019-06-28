#include <stdio.h>

const int MAX_SIZE = 10000;

char str[MAX_SIZE][100];
int len;

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
    if (left >= right) return;
    int l = left - 1;
    int r = right + 1;

    int mid_idx = (l + r) / 2;

    char mid[100];
    int i;
    for(i=0; v[mid_idx][i] != 0; ++i) {
        mid[i] = v[mid_idx][i];
    }
    mid[i] = 0;

    while (1) {
        while(my_strcmp(v[++l], mid) < 0);
        while(my_strcmp(v[--r], mid) > 0);
        if(l >= r) break;
        swap(v[l], v[r]);
    }
    qsort(v, left, l - 1);
    qsort(v, r + 1, right);
}

int main() {
    scanf("%d", &len);
    for(int i=0; i<len; ++i) {
        scanf("%s", str[i]);
    }
    qsort(str, 0, len-1);
    for(int i=0; i<len; ++i) {
        printf("%s\n", str[i]);
    }
}
