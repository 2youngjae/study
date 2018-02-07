#include <stdio.h>
#include <memory.h>
 
int n, l, res;
int map[100][100];
bool visited[100];
 
void isVertical(int r, int c) {
    if (r == n - 1) {
        res++;
        return;
    }
 
    if (map[r][c] == map[r+1][c]) {
        isVertical(r+1, c);
    }
    else if (map[r][c] == map[r+1][c] - 1) {
        if (r - l + 1 < 0) {
            return;
        }
        for (int i = 0; i < l; i++) {
            if (!visited[r - i]) {
                visited[r - i] = true;
            }
            else return;
        }
        isVertical(r+1, c);
    }
    else if (map[r][c] == map[r+1][c] + 1) {
        if (r + l > n - 1) {
            return;
        }
        for (int i = 1; i <= l; i++) {
            if (!visited[r + i] && map[r][c]==map[r + i][c] + 1) {
                visited[r + i] = true;
            }
            else return;
        }
        isVertical(r+l, c);
    }
}
 
void isHorizontal(int r,int c) {
    if (c == n - 1) {
        res++;
        return;
    }
    
    if (map[r][c] == map[r][c + 1]) {
        isHorizontal(r, c + 1);
    }
    else if (map[r][c] == map[r][c + 1] - 1) {
        if (c - l + 1 < 0) {
            return;
        }
        for (int i = 0; i < l; i++) {
            if (!visited[c-i]) {
                visited[c-i] = true;
            }
            else return;
        }
        isHorizontal(r, c + 1);
    }
    else if (map[r][c] == map[r][c + 1] + 1) {
        if (c + l > n - 1) {
            return;
        }
        for (int i = 1; i <= l; i++) {
            if (!visited[c + i] && map[r][c] == map[r][c + i] + 1) {
                visited[c + i] = true;
            }
            else return;
        }
        isHorizontal(r, c + l);
    }
}
 
int main() {
    scanf("%d %d", &n, &l);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &map[i][j]);
        }
    }
 
    for (int i = 0; i < n; i++) {
        memset(visited, 0, sizeof(visited));
        isVertical(0, i);
        memset(visited, 0, sizeof(visited));
        isHorizontal(i, 0);
    }
 
    printf("%d\n", res);
}
