#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct edge {
	int u, v, w;
	edge(int u, int v, int w) :u(u), v(v), w(w){}
};

int V, E;
vector<edge> edges;
int group[10001];

int Find(int x) {
	if (x == group[x])return x;
	return group[x] = Find(group[x]);
}

void Union(int a, int b) {
	a = Find(a);
	b = Find(b);
	if (a == b)return;
	group[b] = a;
}

int compared_edge(const edge &e1, const edge &e2) {
	return e1.w < e2.w;
}

int kruskal() {
	sort(edges.begin(), edges.end(), compared_edge);
	for (int i = 1; i <= V; i++) {
		group[i] = i;
	}

	int ans = 0;
	for (int i = 0; i < edges.size(); i++) {
		if (Find(edges[i].u) == Find(edges[i].v))continue;
		Union(edges[i].u, edges[i].v);
		ans += edges[i].w;
	}
	return ans;
}

int main() {
	ios_base::sync_with_stdio(false);

	cin >> V >> E;

	int u, v, w;
	while (E--) {
		cin >> u >> v >> w;
		edges.push_back(edge(u, v, w));
	}
	
	cout << kruskal() << endl;
}
