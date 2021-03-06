/*
나는 1일권,한달권 / 3달권 / 1년권 ---> 으로 3가지로 분할하여 풀었다.

dMonth배열에는 각각 달별로 min( 일수 x 1일이용권 ,  한달이용권 ) 을 저장하였고,
d[n] 에는 n번째날의 최소값을 갱신해나갔다.

예를들어 4일차 d[4]의 경우 가능한 값은
1. dMonth[1]+dMonth[2]+dMonth[3]+dMonth[4]
2. (1,2,3 3달이용권) + dMonth[4];
3. dMonth[1]+(2,3,4 3달 이용권)
3 가지 경우이다.

이를 토대로 점화식을 세워보면
d[n]=min( d[n-1] + dMonth[n] ,  d[n-3] + 3달이용권 ) 이 된다.
ex) n = 7 : d[6] + dMonth[7] : 6월 까지의 최소비용 + 7월 비용
          : d[4] + 3달이용권 : 4월까지의 최소비용 + 3달권 비용
d[n-3]이전의 경우들에 대해서는 d[n-3]에 이미 3달이용권에 대한 많은 경우들이 비교가 되면서 왔기 때문에 그전것까지 비교할 필요는 없다.

마지막으로 d[12]와 1년 이용권을 비교해주면 된다.
*/

#include <stdio.h>
using namespace std;

int price[4];
int month[13];
int dMonth[13];
int d[13];

int min(int a, int b) {
	return (a < b) ? a : b;
}

int main() {

	int tc;
	scanf("%d", &tc);

	for (int t = 1; t <= tc; t++) {
		for (int i = 0; i < 4; i++) {
			scanf("%d", &price[i]);
		}

		for (int i = 1; i <= 12; i++) {
			scanf("%d", &month[i]);
		}

		//min(하루x날, 한달)
		for (int i = 1; i <= 12; i++) {
			dMonth[i] = min(price[0] * month[i], price[1]);
		}

		for (int i = 1; i <= 12; i++) {
			d[i] = d[i - 1] + dMonth[i];
			if (i - 3 >= 0) {
				if (d[i] > d[i - 3] + price[2]) {
					d[i] = d[i - 3] + price[2];
				}
			}
		}

		if (d[12] > price[3]) {
			d[12] = price[3];
		}

		printf("#%d %d\n", t, d[12]);
	}
}
 
