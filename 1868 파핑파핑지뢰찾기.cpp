/*

1. 지뢰를 기준으로 주변 8곳에 지뢰가 아니면 +1 해준다.

2. map[i][j] 가 0인 점들에 대해서 주변 8방향으로 탐색

-> 탐색할때 res++
-> 폭탄이면 리턴
-> 0이 아닌 숫자가 나오면 방문여부 체크 해주고 리턴
-> 0을만나면 계속해서 탐색

3. 폭탄이 아니고 방문되지 않은 점들에 대해서 카운팅

*/

#include <iostream>
using namespace std;

int t, n, res;
int map[302][302];
bool visited[302][302];
int dx[] = { 1,1,-1,-1,0,1,0,-1 };
int dy[] = { 1,-1,1,-1,1,0,-1,0 };

void numbering(int x,int y) {
	for (int i = 0; i < 8; i++) {
		int ax = x + dx[i];
		int ay = y + dy[i];
		if (ax > 0 && ay > 0 && ax <= n && ay <= n && map[ax][ay] != '*') {
			map[ax][ay]++;
		}
	}
}

void dfs(int x,int y,bool flag) {
	visited[x][y] = true;
	if (!flag) return;
	for (int i = 0; i < 8; i++) {
		int ax = x + dx[i];
		int ay = y + dy[i];
		if (ax > 0 && ay > 0 && ax <= n && ay <= n) {
			if (map[ax][ay] == '*') continue;
			if (!visited[ax][ay]) {
				if (map[ax][ay] == 0) {
					dfs(ax, ay, true);
				}
				else {
					dfs(ax, ay, false);
				}
			}
		}
	}
}

int main() {
	scanf("%d", &t);
	for (int tc = 1; tc <= t; tc++) {
		scanf("%d",&n);
		res = 0;
		char buf[301];
		for (int i = 1; i <= n; i++) {
			scanf("%s", &buf);
			for (int j = 1; j <= n; j++) {
				map[i][j] = buf[j-1];
				if (map[i][j] == '.') map[i][j] = 0;
				visited[i][j] = false;
			}
		}
		
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (map[i][j] == '*') numbering(i, j);
			}
		}

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (!visited[i][j] && map[i][j] == 0) {
					dfs(i, j, true);
					res++;
				}
			}
		}

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (map[i][j] == '*') continue;
				if (!visited[i][j]) res++;
			}
		}

		printf("#%d %d\n", tc, res);
	}
}
