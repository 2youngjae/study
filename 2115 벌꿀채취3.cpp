#include <stdio.h>

int map[10][10];
int d[10][10];
bool visited[10][10];
int n, m, c, res;

int max(int a, int b) {
	return (a > b) ? a : b;
}

//비용 구하기
void getPrice(int x,int y,int a,int sum,int price) {
	if (sum > c) return;
	res = max(res, price);
	if (a == m)return;
	getPrice(x, y + 1, a + 1, sum + map[x][y], price + map[x][y] * map[x][y]);
	getPrice(x, y + 1, a + 1, sum, price);
}

//m개묶음 1개를 골라 놓은 상태에서 나머지 고를 수 있는 경우에 대해 최대값 찾기
int getResult(int x,int y) {
	for (int i = 0; i < m; i++) {
		visited[x][y + i] = true;
	}

	int ans=0;
	for (int i = x; i < n; i++) {
		for (int j = 0; j < n - m + 1; j++) {
			if (!visited[i][j]) {
				ans = max(ans, d[i][j]);
			}
		}
	}
	return ans;
}

int main() {
	int t;
	scanf("%d", &t);
	for (int tc = 1; tc <= t; tc++) {
		scanf("%d %d %d", &n, &m, &c);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				scanf("%d", &map[i][j]);
				d[i][j] = 0;
				visited[i][j] = false;
			}
		}
		//각각의 지점에서 나올 수 있는 최대값 저장
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n - m + 1; j++) {
				res = 0;
				getPrice(i, j, 0, 0, 0);
				d[i][j] = res;
			}
		}

		//m개씩 2가지 고르는 모든 경우에 대해 합 비교하여 최대값 구하기
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n - m + 1; j++) {
				res = max(res, getResult(i, j) + d[i][j]);
			}
		}
		printf("#%d %d\n", tc, res);
	}
}
