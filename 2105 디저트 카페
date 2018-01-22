/*
나는 백트래킹을 이용하여 풀었다.

check 배열로는 방문한 숫자를 체크하였고, visited 배열로는 방문한 지점을 체크하였다.

또한 0~4 까지의 모드값을 주고, 이를 활용하였다.


<mode에 따른 이동가능 지역>

0 : 우하

1 : 우하, 좌하

2 : 좌하, 좌상

3 : 좌상, 우상

4 : 우상


조건을 조금 더 까다롭게 주면 굳이 방문하지 않아도 되는 지점들을 걸러 낼 수 있을텐데 n값이 크지 않아 그부분 까지는 코딩하지 않았다.
*/

#include <stdio.h>
#include <memory.h>
using namespace std;
 
int t, n, cnt, res,sx,sy;
int check[101];
int visited[21][21];
int map[22][22];
 
//현재 상태를 나타내줌
//mode = {0, 1, 2, 3, 4}
void solve(int x, int y,int mode) {
    cnt++;
    check[map[x][y]] += 1;
    visited[x][y] += 1;
 
    if (mode == 4 && visited[x][y]==2) {
        if (res < cnt-1) {
            res = cnt-1;
        }
    }
    else {
        if (mode == 0) {
            if (!check[map[x + 1][y + 1]] && map[x][y] != 0) {
                solve(x + 1, y + 1, 1);
            }
        }
        else if (mode == 1) {
            if (!check[map[x + 1][y + 1]] && map[x + 1][y + 1] != 0) {
                solve(x + 1, y + 1, 1);
            }
            if (!check[map[x + 1][y - 1]] && map[x + 1][y - 1] != 0) {
                solve(x + 1, y - 1, 2);
            }
        }
        else if (mode == 2) {
            if (!check[map[x + 1][y - 1]] && map[x + 1][y - 1] != 0) {
                solve(x + 1, y - 1, 2);
            }
            if (!check[map[x - 1][y - 1]] && map[x - 1][y - 1] != 0) {
                solve(x - 1, y - 1, 3);
            }
        }
        else if (mode == 3) {
            if (!check[map[x - 1][y - 1]] && map[x - 1][y - 1] != 0) {
                solve(x - 1, y - 1, 3);
            }
            if (sx == x - 1 && sy == y + 1) {
                solve(x - 1, y + 1, 4);
            }
            else {
                if (!check[map[x - 1][y + 1]] && map[x - 1][y + 1] != 0) {
                    solve(x - 1, y + 1, 4);
                }
            }
        }
        else {
            if (sx == x - 1 && sy == y + 1) {
                solve(x - 1, y + 1, 4);
            }
            else {
                if (!check[map[x - 1][y + 1]] && map[x - 1][y + 1] != 0) {
                    solve(x - 1, y + 1, 4);
                }
            }
        }
    }
 
    cnt--;
    check[map[x][y]] -= 1;
    visited[x][y] -= 1;
}
 
void init() {
    memset(map, 0, sizeof(map));
    res = -1;
}
 
int main() {
    scanf("%d", &t);
    for (int tc = 1; tc <= t; tc++) {
        scanf("%d", &n);
        init();
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                scanf("%d", &map[i][j]);
            }
        }
        
        for (int i = 1; i < n; i++) {
            for (int j = 2; j < n; j++) {
                sx = i;
                sy = j;
                solve(i, j, 0);
            }
        }
 
        printf("#%d %d\n", tc, res);
    }
}
