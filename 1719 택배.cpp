#include <stdio.h>
#include <queue>
#include <functional>
#include <vector>
#define INF 987654321
#define P pair<int,int>
using namespace std;
 
struct Node {
    int pre; //이전노드
    int dist; //거리
    bool visited; //방문여부
    Node() {
        pre = 0;
        dist = INF;
        visited = false;
    }
};
 
void dijkstra(vector<P> edges[],vector<Node> nodes[], int n, int v) {
    nodes[v].resize(n + 1);
    priority_queue<P, vector<P>, greater<P>> pq;
    //v -> v 로가는 비용 0
    nodes[v][v].dist = 0;
    pq.push(P(0, v));
 
    while (!pq.empty()) {
        // cur = 현재위치
        int cur = pq.top().second;
        pq.pop();
        if (nodes[v][cur].visited) continue; //방문한 점이면 continue
        //방문한적 없으면 방문체크
        nodes[v][cur].visited = true;
 
        for (int i = 0; i < edges[cur].size(); i++) {
            if (nodes[v][edges[cur][i].second].visited) continue;
            //방문한적 없는 노드들에 대해서 최단경로 비교
            int next = edges[cur][i].second;
            int next_cost = edges[cur][i].first;
            if (nodes[v][next].dist > nodes[v][cur].dist + next_cost) {
                nodes[v][next].dist = nodes[v][cur].dist + next_cost;
                nodes[v][next].pre = cur;
                pq.push(P(nodes[v][next].dist, next));
            }
        }
    }
}
 
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    vector<P> edges[201]; //간선정보 저장
    vector<Node> nodes[201]; //노드정보 저장
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        edges[u].push_back(P(w, v));
        edges[v].push_back(P(w, u));
    }
 
    for (int i = 1; i <= n; i++) {
        dijkstra(edges, nodes, n, i);
    }
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j)printf("- ");
            else printf("%d ", nodes[j][i].pre);
        }
        printf("\n");
    }
}
