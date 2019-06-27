#include <stdio.h>
using namespace std;

struct NODE {
    int prev;
    int next;
    int val;
};

const int NODE_SIZE = 30000;

struct MY_LIST {
    int HEAD = NODE_SIZE; // 처음에는 30000. HEAD는 맨 첫 요소의 prev
    int TAIL = NODE_SIZE + 1; // 처음에는 30001. TAIL은 맨 마지막 요소의 next
    int pos;
    NODE node[NODE_SIZE + 2]; // [30000]에 HEAD, [30001]에 TAIL 저장한다.

    MY_LIST() { // 초기화
        pos = 0; // 선형적으로 증가
        node[HEAD].next = TAIL; // HEAD의 next는 TAIL
        node[TAIL].prev = HEAD; // TAIL의 prev는 HEAD로 설정하고 시작
    }

    void push_back(int data) {
        int prev = node[TAIL].prev; // 현재 push될 노드의 prev 위치
        int next = node[prev].next; // 그리고 next 위치 : 항상 TAIL

        node[pos].val = data;

        node[pos].prev = prev; // prev와 pos 간의 설정
        node[prev].next = pos;

        node[pos].next = next; // pos와 next 간의 설정
        node[next].prev = pos;
        ++pos;
    }

    void push_front(int data) {
        int next = node[HEAD].next;
        int prev = node[next].prev; // HEAD;

        node[pos].val = data;

        node[pos].prev = prev;
        node[prev].next = pos;

        node[pos].next = next;
        node[next].prev = pos;
        ++pos;
    }

    void insert(int p, int data) { // p+1번째로 삽입
        int next = node[HEAD].next; // 0번째
        for(int i=0; i<p; ++i) { // p번 더 뒤로 이동
            next = node[next].next;
        }
        int prev = node[next].prev; // 이동한 만큼의 next의 prev

        node[pos].val = data;

        node[pos].prev = prev;
        node[prev].next = pos;

        node[pos].next = next;
        node[pos].prev = pos;
        ++pos;
    }

    void pop_back() {
        int target = node[TAIL].prev;

        int prev = node[target].prev;
        int next = node[target].next;

        node[prev].next = next;
        node[next].prev = prev;
    }

    void pop_front() {
        int target = node[HEAD].next;

        int prev = node[target].prev;
        int next = node[target].next;

        node[prev].next = next;
        node[next].prev = prev;
    }

    void erase(int p) { // p+1번째 노드 삭제
        int target = node[HEAD].next; // 여기서는 target이 이동. 삭제는 모두 target이 중심
        for(int i=0; i<p; ++i) {
            target = node[target].next;
        }
        int prev = node[target].prev;
        int next = node[target].next;

        node[prev].next = next; // target을 기준으로 prev, next를 연결함
        node[next].prev = prev;
    }

    void print_list() {
        int now = node[HEAD].next; // 첫 요소
        printf("%d ", node[now].val);
        now = node[now].next;
        while(now != TAIL) {
            printf("-> %d ", node[now].val);
            now = node[now].next;
        }
        printf("\n");
    }
};

MY_LIST my_list;

int main() {
    int n;
    scanf("%d", &n);
    while(n--) {
        int comm, input, idx;
        scanf("%d", &comm);
        if(!(0<=comm&&comm<=6)) {
            printf("잘못된 입력입니다.\n");
            continue;
        }
        switch(comm) {
            case 0:
                scanf("%d", &input);
                my_list.push_back(input);
                break;
            case 1:
                scanf("%d", &input);
                my_list.push_front(input);
                break;
            case 2:
                scanf("%d %d", &idx, &input);
                my_list.insert(idx, input);
                break;
            case 3:
                my_list.pop_back();
                break;
            case 4:
                my_list.pop_front();
                break;
            case 5:
                scanf("%d", &idx);
                my_list.erase(idx);
                break;
            case 6:
                my_list.print_list();
                break;
        }
    }
}
