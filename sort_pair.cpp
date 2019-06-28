#include <stdio.h>
#include <iostream>
using namespace std;

const int MAX_SIZE = 100000;

struct MY_PAIR {
    int first, second;

    bool operator < (MY_PAIR p) const {
        if(first < p.first) {
            return 1;
        }
        else if(first == p.first) {
            if(second < p.second) {
                return 1;
            }
            return 0;
        }
        else {
            return 0;
        }
    }
    bool operator == (MY_PAIR p) const {
        return first == p.first && second == p.second;
    }
    bool operator > (MY_PAIR p) const {
        if(first > p.first) {
            return 1;
        }
        else if(first == p.first) {
            if(second > p.second) {
                return 1;
            }
            return 0;
        }
        else {
            return 0;
        }
    }
};

MY_PAIR my_pair[MAX_SIZE + 1];

void qsort(MY_PAIR *p, int left, int right) {
    if (left >= right) return;
    int l = left - 1;
    int r = right + 1;
    MY_PAIR mid = p[(l + r) / 2];
    while (1) {
        while (p[++l] < mid);
        while (p[--r] > mid);
        if (l >= r)	break;
        MY_PAIR temp = p[l];
        p[l] = p[r];
        p[r] = temp;
    }
    qsort(p, left, l - 1);
    qsort(p, r + 1, right);
}

int main() {
    int n;
    scanf("%d", &n);
    for(int i=0; i<n; ++i) {
        scanf("%d %d", &my_pair[i].first, &my_pair[i].second);
    }
    qsort(my_pair, 0, n-1);
    for(int i=0; i<n; ++i) {
        printf("%d %d\n", my_pair[i].first, my_pair[i].second);
    }
}
