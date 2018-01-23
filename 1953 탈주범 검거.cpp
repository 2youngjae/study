/*
bfs를 통해 탐색하였다.

그러나 여러 조건들이 있어 구조체에 time,stat 정보를 추가로 저장하였고,

이를 토대로 비교하며 갈 수 있을 경우에만 큐에 넣으면서 문제를 해결했다.
*/

#include <stdio.h>
#include <queue>
#include <memory.h>
using namespace std;

int t, n, m, sx, sy, l, x, y, ax, ay, time, stat, cnt;
int map[50][50];
bool visited[50][50];
int dx[] = { 1,-1,0,0 };
int dy[] = { 0,0,1,-1 };

struct Node {
	int x;
	int y;
	int time;
	int stat;
	Node(int _x, int _y, int _time, int s) {
		x = _x;
		y = _y;
		time = _time;
		stat = s;
	}
};

int getResult() {
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (visited[i][j]) {
				cnt++;
			}
		}
	}
	return cnt;
}

void bfs(int a, int b) {
	queue<Node> q;
	q.push(Node(a, b, 1, map[a][b]));
	visited[a][b] = true;

	while (!q.empty()) {
		x = q.front().x;
		y = q.front().y;
		time = q.front().time;
		stat = q.front().stat;
		q.pop();

		if (time == l) {
			continue;
		}

		for (int i = 0; i < 4; i++) {
			ax = x + dx[i];
			ay = y + dy[i];
			if (ax >= 0 && ay >= 0 && ax < n&&ay < m) {
				// i : 0=하,1=상,2=우,3=좌
				// stat :
				// 1 : 상하좌우
				// 2 : 상하
				// 3 : 좌우
				// 4 : 상우
				// 5 : 우하
				// 6 : 좌하
				// 7 : 좌상
				if (!visited[ax][ay]) {
					if (stat == 2) {
						if (i == 2 || i == 3) continue;
					}
					else if (stat == 3) {
						if (i == 0 || i == 1) continue;
					}
					else if (stat == 4) {
						if (i == 0 || i == 3) continue;
					}
					else if (stat == 5) {
						if (i == 1 || i == 3) continue;
					}
					else if (stat == 6) {
						if (i == 1 || i == 2) continue;
					}
					else if (stat == 7) {
						if (i == 0 || i == 2) continue;
					}

					if (i == 0) {
						if (map[ax][ay] == 1 || map[ax][ay] == 2 || map[ax][ay] == 4 || map[ax][ay] == 7) {
							q.push(Node(ax, ay, time + 1, map[ax][ay]));
							visited[ax][ay] = true;
						}
					}
					else if (i == 1) {
						if (map[ax][ay] == 1 || map[ax][ay] == 2 || map[ax][ay] == 5 || map[ax][ay] == 6) {
							q.push(Node(ax, ay, time + 1, map[ax][ay]));
							visited[ax][ay] = true;
						}
					}
					else if (i == 2) {
						if (map[ax][ay] == 1 || map[ax][ay] == 3 || map[ax][ay] == 6 || map[ax][ay] == 7) {
							q.push(Node(ax, ay, time + 1, map[ax][ay]));
							visited[ax][ay] = true;
						}
					}
					else {
						if (map[ax][ay] == 1 || map[ax][ay] == 3 || map[ax][ay] == 4 || map[ax][ay] == 5) {
							q.push(Node(ax, ay, time + 1, map[ax][ay]));
							visited[ax][ay] = true;
						}
					}
				}
			}
		}
	}
}

void init() {
	memset(visited, false, sizeof(visited));
	memset(map, 0, sizeof(map));
}

int main() {
	scanf("%d", &t);
	for (int tc = 1; tc <= t; tc++) {
		init();

		scanf("%d %d %d %d %d", &n, &m, &sx, &sy, &l);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				scanf("%d", &map[i][j]);
			}
		}

		bfs(sx, sy);
		printf("#%d %d\n", tc, getResult());
	}
}


