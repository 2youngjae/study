#include <stdio.h>
#include <vector>
#include <cmath>
using namespace std;
typedef long long ll;

ll make_Tree(vector<ll> &a, vector<ll> &tree, int node, int start, int end) {
	// 리프노드인경우
	if (start == end) return tree[node] = a[start];
	// 리프노드가 아닌경우 자식노드의 합으로 저장
	int mid = (start + end) >> 1;
	return tree[node] =
		  make_Tree(a, tree, node << 1, start, mid)
		+ make_Tree(a, tree, (node << 1) + 1, mid + 1, end);
}

void update(vector<ll> &tree, int node, int start, int end, int idx, ll val) {
	//범위를 벗어나는경우 리턴
	if (idx<start || idx > end) return;
	//리프노드인경우
	//범위를 벗어나지 않는 리프노드는 idx에 해당하는 노드 하나 뿐이다.
	//tree[idx] 에 업데이트시킬 value 저장
	if (start == end) {
		tree[node] = val;
		return;
	}
	//범위를 벗어나지않으면서 리프노드가 아닌경우
	//자식들을 업데이트 시켜주고 마지막에 자기자신 업데이트
	int mid = (start + end) >> 1;
	update(tree, node << 1, start, mid, idx, val);
	update(tree, (node << 1) + 1, mid + 1, end, idx, val);
	tree[node] = tree[node << 1] + tree[(node << 1) + 1];
}

ll sum(vector<ll> &tree, int node, int start, int end, int left, int right) {
	// 범위를 벗어나는경우 0 리턴
	if (start > right || end < left) return 0;
	// 범위가 완전히 포함되는 경우 현재 노드 반환
	if (left <= start && end <= right) {
		return tree[node];
	}
	// 그 이외의 경우는 계속 탐색한다.
	int mid = (start + end) >> 1;
	return
		  sum(tree, node << 1, start, mid, left, right)
		+ sum(tree, (node << 1) + 1, mid + 1, end, left, right);
}

int main() {
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);

	int h = (int)ceil(log2(n)); // 트리의 높이
	vector<ll> a(n);
	vector<ll> tree(1 << h + 1); // 빈 트리 선언

	for (int i = 0; i < n; i++) {
		scanf("%lld", &a[i]);
	}

	make_Tree(a, tree, 1, 0, n - 1); // 트리 만들기

	m += k;
	while (m--) {
		int x, y, z;
		scanf("%d %d %d", &x, &y, &z);
		if (x == 1) {
			update(tree, 1, 0, n - 1, y - 1, z);
		}
		else {
			printf("%lld\n", sum(tree, 1, 0, n - 1, y - 1, z - 1));
		}
	}
}
