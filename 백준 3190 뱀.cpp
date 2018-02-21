/*
*map[x][y] == 0 : 일반땅
           == 1 : 사과
           == 2 : 뱀
1. 방향에대한 정보를 dir 에 저장하고 방향전환함수 turn을 만들어, 주어진 시간에 대해 방향전환이 필요할 경우 방향전환 시킴

2. 방향에 따라 x,y값 변화 시킴

3. 사과를 먹고 뱀의 길이가 추가될 경우 뒤쪽이 아닌 앞쪽에 붙기 때문에 초기인덱스를 10000으로 설정하고 사과를 먹을때마다 idx-- 를 통해 길이를 늘려줌.

4. 사과를 먹지 않았을경우 뒤쪽부터 한칸씩 땡겨준다.

5. 벽에 부딪히거나 몸통에 부딪히면 종료
*/

#include <iostream>
using namespace std;

//x,y좌표 저장용 구조체
struct Node {
	int x;
	int y;
};

//방향전환정보를 구조화시킨 구조체
struct Dir {
	int time;
	char c;
	Dir() {}
	Dir(int _t, char _c) {
		time = _t;
		c = _c;
	}
};

//방향전환
void turn(int &dir, int c) {
	if (c == 'L') {
		dir = dir - 1;
		if (dir < 0) dir += 4;
	}
	else {
		dir = (dir + 1) % 4;
	}
}

int n, k, l, snake_dir, idx, info_idx;
int map[102][102];
Node snake[10001];
Dir info[100];
int dx[] = { 0,1,0,-1 };
int dy[] = { 1,0,-1,0 };

int main() {
	scanf("%d%d", &n, &k);
	while (k--) {
		int x, y;
		scanf("%d %d", &x, &y);
		map[x][y] = 1;
	}
	scanf("%d", &l);
	while (l--) {
		int x;
		char c;
		scanf("%d %c", &x, &c);
		info[info_idx++] = Dir(x, c);
	}

	// 정보들 초기화
	int time = 0;
	int info_i = 0;
	idx = 10000;
	snake[idx].x = 1;
	snake[idx].y = 1;
	map[1][1] = 2;

	while (true) {
		//방향 전환
		if (info_i != info_idx) {
			if (time == info[info_i].time) {
				turn(snake_dir, info[info_i++].c);
			}
		}

		time++;

		//뱀 이동
		//머리 좌표 이동
		int x, y;
		x = snake[idx].x + dx[snake_dir];
		y = snake[idx].y + dy[snake_dir];

		//종료조건
		//벽에 부딪히면
		if (x == 0 || x == n + 1
			|| y == 0 || y == n + 1) {
			break;
		}
		//몸통에 부딪히면
		if (map[x][y] == 2) break;

		//사과가 있을경우 몸통 당기지 않고
		//머리 위치 유지
		if (map[x][y] == 1) {
			idx--;
			snake[idx].x = x;
			snake[idx].y = y;
			map[x][y] = 2;
		}
		//사과가 없을경우 몸통 당기기
		else {
			map[snake[10000].x][snake[10000].y] = 0;
			for (int i = 10000; i > idx; i--) {
				snake[i].x = snake[i - 1].x;
				snake[i].y = snake[i - 1].y;
			}
			snake[idx].x = x;
			snake[idx].y = y;
			map[x][y] = 2;
		}
	}
	printf("%d\n", time);
}
