/*
시작점부터 끝점까지 최저비용을 누적시키면서 탐색하면 된다.

처음에 visited 배열을 안쓰려고 했는데, 시작점부터 0 0 으로 진행되는경우 무한루프에 빠져서 visited 배열을 사용하여 풀었다.
*/

#include <stdio.h>
#include <queue>
#include <memory.h>
using namespace std;

int t, n;
int map[100][100];
int d[100][100];
bool visited[100][100];

struct Node {
	int x;
	int y;
	Node(int _x, int _y) {
		x = _x;
		y = _y;
	}
};

void bfs() {
	queue<Node> q;
	q.push(Node(0, 0));
	visited[0][0] = true;
	int dx[] = { 1,-1,0,0 };
	int dy[] = { 0,0,1,-1 };
	while (!q.empty()) {
		int x = q.front().x;
		int y = q.front().y;
		q.pop();
		for (int i = 0; i < 4; i++) {
			int ax = x + dx[i];
			int ay = y + dy[i];
			if (ax >= 0 && ay >= 0 && ax < n&&ay < n) {
				if (!visited[ax][ay] || d[ax][ay] > d[x][y] + map[ax][ay]) {
					d[ax][ay] = d[x][y] + map[ax][ay];
					q.push(Node(ax, ay));
					visited[ax][ay] = true;
				}
			}
		}
	}
}

void init() {
	memset(d, 0, sizeof(d));
	memset(visited, false, sizeof(visited));
}

int main() {
	scanf("%d", &t);
	for (int tc = 1; tc <= t; tc++) {
		init();
		scanf("%d", &n);
		char buf[101];
		for (int i = 0; i < n; i++) {
			scanf("%s", &buf);
			for (int j = 0; j < n; j++) {
				map[i][j] = buf[j] - '0';
			}
		}

		bfs();
		printf("#%d %d\n", tc, d[n - 1][n - 1]);
	}
}
