/*

1. dfs로 모든 경우에 대해 탐색

2. 탐색할때 k만큼 깍는 작업을 했는지 안했는지에 따라 분류

3. k만큼 깍는 작업을 하고 넘어 왔을경우, 이전 상태를 알려주는 pre 매개변수를 통해 넘어온 지점이 얼마로 깍여 왔는지에 대해 알 수 있고 pre 변수로 다음 지점과 비교하여 탐색.

4. 최대값 찾는다.

*/

#include <stdio.h>
 
int n, k, ax, ay, res;
int map[9][9];
unsigned short visited[9];
int dx[] = { 1,-1,0,0 };
int dy[] = { 0,0,1,-1 };
 
void dfs(int x, int y, int k, bool flag, int pre, int cnt) {
    visited[x] = visited[x] | (1 << y);
 
    if (res < cnt) {
        res = cnt;
    }
 
    for (int i = 0; i < 4; i++) {
        ax = x + dx[i];
        ay = y + dy[i];
        if (ax > 0 && ay > 0 && ax <= n && ay <= n) {
            if (!flag) {
                //깍지 않았을때
                if (map[x][y] > map[ax][ay] && !(visited[ax]&(1<<ay))) {
                    dfs(ax, ay, k, flag, map[x][y], cnt + 1);
                }
                else {
                    if (map[x][y] > map[ax][ay] - k && !(visited[ax] & (1 << ay))) {
                        dfs(ax, ay, k, true, map[x][y] - 1, cnt + 1);
                    }
                }
            }
            else {
                //깍기 했을때
                if (pre > map[ax][ay] && !(visited[ax] & (1 << ay))) {
                    dfs(ax, ay, k, flag, map[ax][ay], cnt + 1);
                }
            }
        }
    }
    visited[x] = visited[x] & ~(1 << y);
}
 
int main() {
    int t;
    scanf("%d", &t);
    for (int tc = 1; tc <= t; tc++) {
        scanf("%d %d", &n, &k);
 
        res = 0;
        int start = 0;
 
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                scanf("%d", &map[i][j]);
                if (start < map[i][j]) start = map[i][j];
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (map[i][j] == start) {
                    dfs(i, j, k, false, 20, 1);
                }
            }
        }
 
        printf("#%d %d\n", tc, res);
    }
}

