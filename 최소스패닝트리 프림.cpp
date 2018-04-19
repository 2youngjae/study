#include <iostream>
#include <queue>
#include <functional>
#define P pair<int,int>
using namespace std;

int V, E;
vector<P> edges;
int group[10001];

int prim(vector<P> edges[]) {
	priority_queue<P, vector<P>, greater<P>> pq;
	vector<bool> visited(V + 1, false);
	int ans = 0;

	pq.push(P(0, 1));
	
	while (!pq.empty()) {
		P cur = pq.top();
		pq.pop();

		if (visited[cur.second]) continue;
		visited[cur.second] = true;
		ans += cur.first;

		for (int i = 0; i < edges[cur.second].size(); i++) {
			if (visited[edges[cur.second][i].second]) continue;
			pq.push(edges[cur.second][i]);
		}
	}

	return ans;
}

int main() {
	ios_base::sync_with_stdio(false);

	cin >> V >> E;

	vector<P> edges[10001];
	int u, v, w;
	while (E--) {
		cin >> u >> v >> w;
		edges[u].push_back(P(w, v));
		edges[v].push_back(P(w, u));
		//edges.push_back(edge(u, v, w));
	}
	
	//cout << kruskal() << endl;
	cout << prim(edges) << endl;
}
