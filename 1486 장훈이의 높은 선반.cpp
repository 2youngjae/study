/*
백트래킹을 이용하여
가능한 모든 경우에 대해 비교하며
결과를 찾아냈다.
*/

#include <stdio.h>

int t, n, b, res;
int a[20];

void dfs(int v, int sum) {
	int s = sum + a[v] - b;
	if (s >= 0) {
		if (res > s) res = s;
	}
	if (v == n - 1) return;
	dfs(v + 1, sum);
	dfs(v + 1, sum + a[v]);
}

int main() {
	scanf("%d", &t);
	for (int tc = 1; tc <= t; tc++) {
		scanf("%d %d", &n, &b);
		for (int i = 0; i < n; i++) {
			scanf("%d", &a[i]);
		}
		res = 987654321;
		dfs(0, 0);

		printf("#%d %d\n", tc, res);
	}
}
