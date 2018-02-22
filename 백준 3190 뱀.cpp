/*
*map[x][y] == 0 : 일반땅
           == 1 : 사과
           == 2 : 뱀

1. 방향에대한 정보를 dir 에 저장하고 방향전환함수 turn을 만들어, 주어진 시간에 대해 방향전환이 필요할 경우 방향전환 시킴

2. 방향에 따라 x,y값 변화 시킴

3. 이동할 곳이 벽이거나 몸통인경우 종료

4. 이동할 곳이 일반땅인 경우 뱀의 꼬리부분 삭제

5. 뱀의 머리부분 추가 및 맵에 갱신

6. 종료시까지 반복
*/

#include <iostream>
#include <vector>
#define P pair<int,int>
using namespace std;

int map[102][102];
int n, k, l, snake_dir, info_idx;
vector<P> snake;
P info[100];
int dx[] = { 0,1,0,-1 };
int dy[] = { 1,0,-1,0 };

//0동,1남,2서,3북
//방향 전환하기
int turn(int dir, char c) {
	if (c == 'D') {
		return (dir + 1) % 4;
	}
	else {
		return (dir == 0) ? 3 : (dir - 1);
	}
}

int main() {
	scanf("%d %d", &n, &k);
	while (k--) {
		int x, y;
		scanf("%d %d", &x, &y);
		map[x][y] = 1;
	}
	scanf("%d", &l);
	while (l--) {
		int x, y;
		scanf("%d %c", &x, &y);
		info[info_idx++] = P(x, y);
	}

	//뱀의 시작점 추가
	snake.push_back(P(1, 1));
	map[1][1] = 2;
	int idx = 0;
	int time = 0;

	while (true) {
		//방향 전환정보가 있으면 방향전환하기
		if (idx != info_idx) {
			if (time == info[idx].first) {
				snake_dir = turn(snake_dir, info[idx++].second);
			}
		}
		time++;

		//다음위치 x,y 에 저장
		int x = snake[snake.size() - 1].first + dx[snake_dir];
		int y = snake[snake.size() - 1].second + dy[snake_dir];

		//벽에 부딪힘
		if (x == 0 || y == 0 || x == n + 1 || y == n + 1) break;
		//몸통에 부딪힘
		if (map[x][y] == 2) break;

		//일반땅일 경우 뱀의 꼬리 삭제
		if (map[x][y] == 0) {
			map[snake[0].first][snake[0].second] = 0;
			snake.erase(snake.begin());
		}
		//머리부분 맵과 벡터에 추가
		map[x][y] = 2;
		snake.push_back(P(x, y));
	}
	printf("%d\n", time);
}
