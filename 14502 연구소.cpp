#include <stdio.h>
#include <vector>
#define P pair<int,int>
using namespace std;

int n, m, res;
int map[8][8];
int tmp[8][8];
vector<P> virus;
bool visited[8][8];
int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

//안전구역 갯수 세기
void countSafetyZone() {
	int ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (tmp[i][j] == 0) {
				ans++;
			}
		}
	}
	if (res < ans) {
		res = ans;
	}
}

//바이러스 퍼뜨리기
void spreadVirus(int x,int y) {
	tmp[x][y] = 2;
	int ax, ay;
	for (int i = 0; i < 4; i++) {
		ax = x + dx[i];
		ay = y + dy[i];
		if (ax >= 0 && ay >= 0 && ax < n&&ay < m && tmp[ax][ay] == 0) {
			spreadVirus(ax, ay);
		}
	}
}
//백트래킹
void dfs(int x, int y, int cnt) {
	map[x][y] = 1;

	if (cnt == 3) {
		//바이러스 퍼뜨리기
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++) 
				tmp[i][j] = map[i][j];

		for (auto p : virus) 
			spreadVirus(p.first, p.second);
		//안전구역 갯수 세기
		countSafetyZone();
	}
	else {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (!visited[i][j] && map[i][j] == 0)
				{
					visited[i][j] = true;
					dfs(i, j, cnt + 1);
					visited[i][j] = false;
				}
					
			}
		}
	}

	map[x][y] = 0;
}

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 2) {
				virus.push_back(P(i, j));
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j] == 0) {
				visited[i][j] = true;
				dfs(i, j, 1);
			}
		}
	}

	printf("%d\n", res);
}
