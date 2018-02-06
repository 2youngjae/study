#include <stdio.h>
#include <queue>
using namespace std;

//접수창구, 정비창구의 상태를 저장
struct Node {
	bool flag; //사용중인지
	int time; //몇초 남았는지 
	int num; //몇번째 손님이 들어와 있는지
};

int n, m, k, A, B;
int a[10], b[10], t[1001];
bool check[1001], statT[1001];
Node usingA[10], usingB[10];

int main() {
	int tt;
	scanf("%d", &tt);
	for (int tc = 1; tc <= tt; tc++) {
		scanf("%d %d %d %d %d", &n, &m, &k, &A, &B);
		int res = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
			usingA[i].time = a[i];
			usingA[i].flag = false;
		}
		for (int i = 1; i <= m; i++) {
			scanf("%d", &b[i]);
			usingB[i].time = b[i];
			usingB[i].flag = false;
		}
		for (int i = 1; i <= k; i++) {
			scanf("%d", &t[i]);
			statT[i] = 0;
			check[i] = 0;
		}

		queue<int> qa;
		queue<int> qb;
		int cnt = 0;
		while (true) {
			if (cnt == k) break;
			//접수 창구에 줄세우기
			for (int i = 1; i <= k; i++) {
				if (t[i] == 0) {
					qa.push(i);
					t[i]--;
				}
				else if (t[i] > 0) break;
			}

			//접수 창구 배정하기
			for (int i = 1; i <= n; i++) {
				if (qa.empty()) break;
				if (!usingA[i].flag) {
					if (i == A) check[qa.front()]=true;
					usingA[i].flag = true;
					usingA[i].num = qa.front();
					qa.pop();
				}
			}

			//정비 창구 배정하기
			for (int i = 1; i <= m; i++) {
				if (qb.empty()) break;
				if (!usingB[i].flag) {
					if (i == B) {
						if (check[qb.front()]) res += qb.front();
					}
					usingB[i].flag = true;
					usingB[i].num = qb.front();
					cnt++;
					qb.pop();
				}
			}

			//1초 경과시키기
			for (int i = 1; i <= n; i++) {
				if (usingA[i].flag) {
					usingA[i].time--;
					if (usingA[i].time == 0) {
						usingA[i].time = a[i];
						usingA[i].flag = false;
						qb.push(usingA[i].num);
					}
				}
			}

			for (int i = 1; i <= m; i++) {
				if (usingB[i].flag) {
					usingB[i].time--;
					if (usingB[i].time == 0) {
						usingB[i].time = b[i];
						usingB[i].flag = false;
					}
				}
			}

			for (int i = 1; i <= k; i++) {
				if (t[i] > 0) t[i]--;
			}
		}

		if (res == 0) res = -1;
		printf("#%d %d\n", tc, res);
	}
}
