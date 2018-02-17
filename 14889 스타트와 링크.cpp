#include <iostream>
#include <vector>
#define INF 987654321
using namespace std;

int n, res;
int map[20][20];
bool check[20];

int abs(int a) {
	return (a > 0) ? a : -a;
}

// v팀의 점수를 구한다.
int getScore(vector<int> &v) {
	int sz = v.size();
	int res = 0;
	for (int i = 0; i < sz; i++) {
		for (int j = 0; j < sz; j++) {
			if (i == j) continue;
			res += map[v[i]][v[j]];
		}
	}
	return res;
}

//선택된팀과 선택되지 않은팀의 점수차를 비교
void comp() {
	vector<int> a; //선택된 팀
	vector<int> b; //선택안된 팀
	for (int i = 0; i < n; i++) {
		if (check[i]) a.push_back(i);
		else b.push_back(i);
	}
	
	int ans = abs(getScore(a)-getScore(b));
	if (res > ans) res = ans;
}

//백트래킹을 통해 모든경우에 대해 차이를 구함
void dfs(int v, int cnt) {
	check[v] = true;
	if (cnt == n / 2) {
		comp();
	}
	else {
		for (int i = v + 1; i < n; i++) {
			dfs(i, cnt + 1);
		}
	}
	check[v] = false;
}

int main() {
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &map[i][j]);
		}
	}

	res = INF;
	dfs(0, 1);
	printf("%d\n", res);
}
