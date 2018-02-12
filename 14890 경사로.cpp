#include <stdio.h>
#include <memory.h>

int map[102][102];
bool visited[100];
int n, l, res;

void f1(int r,int c) {
	if (c == n) {
		res++;
		return;
	}
	
	//다음칸과 높이가 같을때
	if (map[r][c] == map[r][c + 1]) {
		f1(r, c + 1);
	}
	//다음칸보다 높이가 높을때
	else if (map[r][c] - 1 == map[r][c + 1] ) {
		if (c + l > n) return;
		for (int i = 1; i <= l; i++) {
			if (map[r][c] - 1 != map[r][c + i]) return;
			visited[c + i] = true;
		}
		f1(r, c + 1);
	}
	//다음칸보다 높이가 낮을때
	else if (map[r][c] + 1 == map[r][c + 1]) {
		if (c - l + 1 < 1)return;
		for (int i = 0; i < l; i++) {
			if (visited[c - i] || (map[r][c] != map[r][c-i])) return;
			visited[c - i] = true;
		}
		f1(r, c + 1);
	}
}

void f2(int r, int c) {
	if (r == n) {
		res++;
		return;
	}

	//다음칸과 높이가 같을때
	if (map[r][c] == map[r+1][c ]) {
		f2(r+1, c);
	}
	//다음칸보다 높이가 높을때
	else if (map[r][c] - 1 == map[r+1][c]) {
		if (r + l > n) return;
		for (int i = 1; i <= l; i++) {
			if (map[r][c] - 1 != map[r + i][c]) return;
			visited[r + i] = true;
		}
		f2(r+1, c);
	}
	//다음칸보다 높이가 낮을때
	else if (map[r][c] + 1 == map[r+1][c]) {
		if (r - l + 1 < 1)return;
		for (int i = 0; i < l; i++) {
			if (visited[r - i] || (map[r][c] != map[r-i][c])) return;
			visited[r - i] = true;
		}
		f2(r+1, c);
	}
}

int main() {
	scanf("%d %d", &n, &l);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%d", &map[i][j]);
		}
	}

	for (int i = 1; i <= n; i++) {
		memset(visited, 0, sizeof(visited));
		f1(i, 1);
		memset(visited, 0, sizeof(visited));
		f2(1, i);
	}
	printf("%d\n",res);
}
