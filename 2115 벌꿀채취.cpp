#include <stdio.h>
#include <vector>
#include <memory.h>
using namespace std;

int n, m, c, res;
int map[10][10];
bool visited[10][10];

int max(int a, int b) {
	return (a > b) ? a : b;
}

void calcResult(vector<int> &vec, int v ,int sum, int p,int &res) {
	if (sum > c) {

	}
	else {
		if (res < p) {
			res = p;
		}

		for (int i = v + 1; i < m; i++) {
			calcResult(vec, i, sum+vec.at(i), p+vec.at(i)*vec.at(i), res);
		}
	}
}

// c를 초과하지 않는 경우에 대해 백트래킹
int getResult(vector<int> &vec) {
	int res = 0;
	int max = 0;
	for (int i = 0; i < m; i++) {
		calcResult(vec, i, vec.at(i), vec.at(i)*vec.at(i), res);
		if (max < res) {
			max = res;
		}
	}
	return max;
}

void calc() {
	int cnt = 0;
	vector<int> a;
	vector<int> b;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (visited[i][j]) {
				if (cnt == 0) {
					cnt++;
					for (int k = 0; k < m; k++) {
						a.push_back(map[i][j + k]);
					}
				}
				else {
					for (int k = 0; k < m; k++) {
						b.push_back(map[i][j + k]);
					}
				}
				j += m-1;
			}
		}
	}
	// 계산하기
	int resa = getResult(a);
	int resb = getResult(b);
	if (res < resa+resb) {
		res = resa + resb;
	}
}

//m개씩 묶을 수 있는 경우에 대해 백트래킹
void solve(int x, int y, int cnt) {
	if (y + m > n) return;

	for (int i = 0; i < m; i++) {
		visited[x][y+i] = true;
	}

	if (cnt == 1) {
		for (int i = y + m; i < n; i++) {
			solve(x, i, cnt+1);
		}
		for (int i = x + 1; i < n; i++) {
			for (int j = 0; j < n; j++) {
				solve(i, j, cnt+1);
			}
		}
	}
	else {
		// 계산하기
		calc();
	}

	for (int i = 0; i < m; i++) {
		visited[x][y + i] = false;
	}
}

void init() {
	memset(visited, 0, sizeof(visited));
	res = 0;
}

int main() {
	int t;
	scanf("%d", &t);
	for (int tc = 1; tc <= t; tc++) {
		init();
		scanf("%d %d %d", &n, &m, &c);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				scanf("%d", &map[i][j]);
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				solve(i,j,1);
			}
		}
		printf("#%d %d\n", tc, res);
	}
}
