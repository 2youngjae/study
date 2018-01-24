/*
임의의 지점에 대해 어떤점에서 출발할 경우 그점이 3번만에 도착 할 수 있고

어떤 점에 대해서는 그 점이 5번만에 도착 할 수있는데,

l이 10 5번만에 도착하는방법이 먼저 방문했을 경우 그 지점부터 얼마 나아가지 못하므로,

몇번만에 도착한 지점인지를 계속해서 visited 배열에 갱신하면서 풀었다.
*/

#include <stdio.h>
#include <memory.h>
using namespace std;

int t, n, m, r, c, l, dest;
int map[50][50];
int visited[50][50];
// {상, 하, 좌, 우}
int direct[8][4] = { { 0,0,0,0 },{ 1,1,1,1 },{ 1,1,0,0 },{ 0,0,1,1 },
{ 1,0,0,1 },{ 0,1,0,1 },{ 0,1,1,0 },{ 1,0,1,0 } };
int dx[] = { -1,1,0,0 };
int dy[] = { 0,0,-1,1 };

void solve(int x, int y, int time) {
	if (time == l) {
		return;
	}

	for (int i = 0; i < 4; i++) {
		int ax = x + dx[i];
		int ay = y + dy[i];

		if (i == 0) dest = 1;
		else if (i == 1) dest = 0;
		else if (i == 2) dest = 3;
		else dest = 2;

		if (ax >= 0 && ay >= 0 && ax < n && ay < m) {
			if (direct[map[x][y]][i] == 1 && direct[map[ax][ay]][dest] == 1) {
				if (!visited[ax][ay] || visited[ax][ay]>visited[x][y]+1) {
					visited[ax][ay] = time+1;
					solve(ax, ay, time + 1);
				}
			}
		}
	}
}

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

void init() {
	memset(visited, false, sizeof(visited));
	memset(map, 0, sizeof(map));
}

int main() {
	scanf("%d", &t);
	for (int tc = 1; tc <= t; tc++) {
		init();

		scanf("%d %d %d %d %d", &n, &m, &r, &c, &l);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				scanf("%d", &map[i][j]);
			}
		}

		visited[r][c] = 1;
		solve(r, c, 1);
		printf("#%d %d\n", tc, getResult());
	}
}
