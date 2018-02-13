#include <stdio.h>
#include <vector>
#include <cmath>
#define INF 987987654321
using namespace std;
typedef long long ll;

ll min(ll a, ll b) {
	return (a < b) ? a : b;
}

ll make_Tree(vector<ll> &a, vector<ll> &tree, int node, int start, int end) {
	//리프 노드인 경우 
	if (start == end) return tree[node] = a[start];
	int mid = (start + end) >> 1;
	//리프 노드가 아닌 경우 자식중 최소값으로 저장
	return tree[node] = min(
		  make_Tree(a, tree, node << 1, start, mid)
		 ,make_Tree(a, tree, (node << 1) + 1, mid + 1, end));
}

//최소값 구하기
ll getMin(vector<ll> &tree, int node, int start, int end, int left, int right) {
	//범위에 벗어나는 경우 INF 리턴
	if (start > right || end < left) return INF;
	//범위에 완전히 포함되는경우 현재 node값 리턴
	if (left <= start && end <= right) {
		return tree[node];
	}
	// 리프노드, 범위에 완전히 포함되는 경우가 아닌경우
	// 자식노드로 호출하고 결과 값 리턴
	int mid = (start + end) >> 1;
	return min(getMin(tree, node << 1, start, mid, left, right)
		, getMin(tree, (node << 1) + 1, mid + 1, end, left, right));
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);

	int h = (int)ceil(log2(n));

	vector<ll> a(n);
	vector<ll> tree(1 << h + 1);

	for (int i = 0; i < n; i++) {
		scanf("%lld", &a[i]);
	}

	make_Tree(a, tree, 1, 0, n - 1);

	while (m--) {
		int x, y;
		scanf("%d %d", &x, &y);
		printf("%lld\n", getMin(tree, 1, 0, n - 1, x - 1, y - 1));
	}
}
