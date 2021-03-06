/*

주어진 점들을 1:1매칭하여 생기는 벡터의 최소값을 구하는 문제.

점의 갯수가 짝수개로 주어지기 때문에 나는 n/2개 선택 할 수 있는 모든 경우에 대하여

벡터들의 합을 구한뒤 최소값을 찾았다.

*/

#include <stdio.h>
#include <memory.h>
#include <vector>
using namespace std;
#define INF 987987654321

//입력값을 저장시킬 구조체
struct Point {
	int x;
	int y;
};

int t, n,cnt;
bool visited[21];
Point p[21];
long long res;

//벡터값 계산하기
//n개중 n/2개를 골라 고른것과 고르지 않는 벡터를 연결시키고
//크기를 계산했다.
//고른지 안고른지 여부는 dfs()함수에서 visited배열에 기록
void calcVector() {
	vector<Point> selected; // 고른 정점을 저장
	vector<Point> unSelected;//고르지 않은  저장
	for (int i = 0; i < n; i++) {
		if (visited[i]) {
			selected.push_back(p[i]);
		}
		else {
			unSelected.push_back(p[i]);
		}
	}

	long long x=0, y=0;
	for (int i = 0; i < n / 2; i++) {
		x += (selected.at(i).x - unSelected.at(i).x);
		y += (selected.at(i).y - unSelected.at(i).y);
	}
	if (res > y*y + x * x) {
		res = y * y + x * x;
	}
}

//백트래킹 하여 n/2개를 고를 수 있는 모든 경우를 탐색.
void dfs(int v)
{
	cnt++;
	visited[v] = true;
	if (cnt == n / 2) {
		calcVector();
	}
	else {
		for (int i = v + 1; i < n; i++) {
			if (!visited[i]) {
				dfs(i);
			}
		}
	}
	visited[v] = false;
	cnt--;
}

//초기화 시켜주기
void init() {
	memset(visited, 0, sizeof(visited));
	memset(p, 0, sizeof(p));
	res = INF;
	cnt = 0;
}

int main() {

	scanf("%d", &t);
	for (int tc = 1; tc <= t; tc++) {
		init();
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &p[i].x, &p[i].y);
		}
		dfs(0);
		printf("#%d %lld\n", tc, res);
	}
}
