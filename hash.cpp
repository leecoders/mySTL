#include <stdio.h>
using namespace std;

const int PN = 23; // 최대한 분산된 키들을 생성하기 위해 소수를 사용함
const int HASH_SIZE = 10000; // 생성된 키를 이 수로 나머지를 취함. 생성된 키의 수(행의 수)가 됨

int table[HASH_SIZE][50]; // 각 키 행에 데이터 최대 50개(열)를 저장
int hash_size = 0; // 테이블에 들어간 총 문자열 개수
char hash_raw[30000][100]; // 테이블 사이즈를 줄이기 위해 테이블에는 정수 값만 넣어두고 hash_raw 배열의 인덱스로 사용함

unsigned int get_key(char str[]) { // 키 생성 함수
   unsigned int key = 0, p = 1; // unsigned는 바로 해시 테이블의 행 인덱스로 쓰여야 하기 때문. p는 PN의 각 자리 만큼의 제곱수를 얻기 위함

   for(int i = 0; str[i] != 0; ++i) {
       key += (str[i] * p); // key에 (각 자리 값 * p^자리 수)를 더함
       p *= PN; // 다음 자리로 갈 때 PN을 한 번 더 곱해줌
   }

   return (key % HASH_SIZE); // 0 ~ 9999. 위 연산에서 오버플로우가 나도 상관 없음(어차피 양수)
}

int my_strcmp(char a[], char b[]) { // strcmp 함수 구현
   int i = 0, j = 0;
   while(a[i]) { // NULL이면 탈출
       if (a[i++] != b[j++]) {
           --i, --j; // 후위 연산자에 의해 비교된 자리보다 1 커졌으므로 빼줌
           break;
       }
   }
   return (a[i] - b[j]); // strcmp 함수는 앞이 더 크면 양수가 반환됨
}

int contain(char str[]) { // 해당 문자열이 테이블에 존재하는 지 확인하는 함수
   unsigned int key = get_key(str); // 테이블의 행 인덱스를 위해 키 생성
   int size = table[key][0]; // 테이블의 0열에는 각 행의 사이즈가 저장되어 있음
   for(int i = 1; i <= size; ++i) {
       int pos = table[key][i]; // 테이블에 있는 hash_raw의 인덱스 값
       if(my_strcmp(hash_raw[pos], str) == 0) {
           return pos; // 검색 성공 시 raw 인덱스 반환
       }
   }
   return -1; // 검색 실패(성공 시 0 이상의 값)
}

void add(char str[]) { // 문자열을 hash_raw와 테이블에 추가하는 함수. 문자열이 char[]라서 한 자리씩 넣어야 함
   int len = 0;
   for(len = 0; str[len] != 0; ++len) { // 0은 NULL(문자열의 끝)을 뜻함
       hash_raw[hash_size][len] = str[len];
   }
   hash_raw[hash_size][len] = 0; // 문자열의 끝!! 필수

   unsigned int key = get_key(str); // hash_raw에 넣었으니 테이블에도 넣어야지
   int& size = table[key][0];
   table[key][++size] = hash_size;

   ++hash_size; // 많이 쓰이므로 따로 증가
}

bool remove(char str[]) { // 삭제 함수. 테이블에서만 지우면 raw는 찾을 일이 없다.
   unsigned int key = get_key(str);
   int& size = table[key][0];
   for(int i = 1; i <= size; ++i) {
       int pos = table[key][i];
       if(my_strcmp(hash_raw[pos], str) == 0) { // 삽입, 삭제 빈번해도 정확한 size를 계산하기 위해 한 칸씩 땡김
           for(int j = i + 1; j <= size; ++j) {
               table[key][j - 1] = table[key][j];
           }
           --size;
           return true; // 삭제 성공
       }
   }
   return false; // 삭제 실패 (검색 실패)
}

int main() {

}
