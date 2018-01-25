/*

N=10일때
M=2 : (1,9) / (2,8)/ (3,7)/ (4,6)/ (5,5)/ 의 경우가 가능한데 가장 큰 값은 중간값인 (5,5)인 경우이다.

이처럼 N/M을 통해 중간 값을 찾아주면 되는데
나머지가 생기는 경우 나머지 만큼의 경우에 대해서는 +1 해준 값을 곱해주면된다.
아마 가장 큰 값이 N=100, M=32인 경우 같은데 이경우 16자리가 나오고, 
이는 C++기준 long long형으로 연산시 연산이 가능하다.

P.S) long long 형 처음 출력해봤다. 굉장히 긴게 신기하다.

*/

#include <stdio.h>
using namespace std;

int n, m, x, y;
long long res;

int main() {

	int tc;
	scanf("%d", &tc);

	for (int t = 1; t <= tc; t++) {

		res = 1;
		scanf("%d %d", &n, &m);
		x = n / m;
		y = n % m;
		//res 에 n/m을 n%m번 곱해준다.
		for (int i = 0; i < m - y; i++) {
			res *= x;
		}
		x++;
		//나머지 n%m번은 (n/m)+1 을 곱해준다.
		for (int i = 0; i < y; i++) {
			res *= x;
		}

		printf("#%d %lld\n", t, res);
	}
}
