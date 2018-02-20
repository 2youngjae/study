#include <stdio.h>
#include <vector>
using namespace std;
 
struct Node {
    int x;
    int y;
    int num;
    int dir;
};
 
int t, n, m, k, dir;
vector<int> map[101][101];
Node a[1001];
 
int main() {
    scanf("%d", &t);
    for (int tc = 1; tc <= t; tc++) {
        scanf("%d%d%d", &n, &m, &k);
 
        for (int i = 1; i <= k; i++) {
            scanf("%d%d%d%d", &a[i].x, &a[i].y, &a[i].num, &a[i].dir);
        }
 
        while (m--) {
            //미생물 이동
            for (int i = 1; i <= k; i++) {
                if (a[i].num == 0) continue;
                map[a[i].x][a[i].y].clear();
                if (a[i].dir == 1) {
                    a[i].x -= 1;
                }
                else if (a[i].dir == 2) {
                    a[i].x += 1;
                }
                else if (a[i].dir == 3) {
                    a[i].y -= 1;
                }
                else {
                    a[i].y += 1;
                }
            }
 
            //이동한 미생물 맵에 넣기
            for (int i = 1; i <= k; i++) {
                if (a[i].num == 0) continue;
                map[a[i].x][a[i].y].push_back(i);
            }
 
            for (int i = 1; i <= k; i++) {
                //군집이 없을경우 continue
                if (a[i].num == 0) continue;
 
                //칸에 미생물 한군집일 경우
                if (map[a[i].x][a[i].y].size() == 1) {
                    //가장자리에 걸렸을 경우
                    if (a[i].x == 0 || a[i].y == 0 || a[i].x == n - 1 || a[i].y == n - 1) {
                        a[i].num = a[i].num / 2;
                        //미생물이 소멸하였을 경우
                        if (a[i].num == 0) {
                            map[a[i].x][a[i].y].clear();
                        }
                        //소멸하지 않았을 경우
                        else {
                            //방향 바꿔줌
                            if (a[i].dir == 1) a[i].dir = 2;
                            else if (a[i].dir == 2) a[i].dir = 1;
                            else if (a[i].dir == 3) a[i].dir = 4;
                            else a[i].dir = 3;
                        }
                    }
                }
                //미생물이 여러 군집일 경우
                else {
                    int sum = 0;
                    int max_idx = 0; //군집수가 제일 많은 인덱스
                    int max_num = 0; //미생물수가 제일 많은 군집의 미생물수
                    int max_dir = 0; //미생물수가 제일 많은 군집의 방향
                    //미생물이 가장 많은 군집을 찾아 그군집에대한 정보로 업데이트
                    for (int x = 0; x < map[a[i].x][a[i].y].size(); x++) {
                        sum += a[map[a[i].x][a[i].y][x]].num;
                        if (max_num < a[map[a[i].x][a[i].y][x]].num) {
                            max_num = a[map[a[i].x][a[i].y][x]].num;
                            max_idx = map[a[i].x][a[i].y][x];
                            max_dir = a[map[a[i].x][a[i].y][x]].dir;
                        }
                        a[map[a[i].x][a[i].y][x]].num = 0;
                    }
                    a[max_idx].num = sum;
                    a[max_idx].dir = max_dir;
                    map[a[i].x][a[i].y].clear();
                    map[a[i].x][a[i].y].push_back(max_idx);
                }
            }
        }
        int res = 0;
        for (int i = 1; i <= k; i++) {
            res += a[i].num;
        }
        printf("#%d %d\n", tc, res);
 
        //맵 초기화
        for (int i = 1; i <= k; i++) {
            if (a[i].num == 0) continue;
            map[a[i].x][a[i].y].clear();
        }
    }
}
