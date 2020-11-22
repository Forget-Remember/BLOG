#include<bits/stdc++.h>
#define mmin(a,b) (a < b ? a : b)
#define mmax(a,b) (a > b ? a : b)
using namespace std;
const int MAXM = 1e2 + 5;
inline int read(){
    int x = 0,f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9'){
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9'){
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}

int m,n,ans = 0x7fffffff;
int mp[MAXM][MAXM];
bool used[MAXM][MAXM];
int mem[MAXM][MAXM];
// 右 下 上 左
int xx[] = {  0,  1, -1,  0};
int yy[] = {  1,  0,  0, -1};

bool reachable(int px,int py){
    if(px < 1 || py > m) return false;
    if(py < 1 || py > m) return false;
    if(used[px][py]) return false;
    return true;
}

bool op;

void dfs(int x,int y,int cost,bool mag){
    // 此时已经到达终点，故直接更新答案返回即可
    if(x == m && y == m){
        // cout << endl;
        ans = mmin(ans,cost);
        op = true;
        return;
    }
    // 在之前搜索到的路径中已有到达此处的更优解，故不需要继续运算 
    if(cost >= mem[x][y]) return ;
    mem[x][y] = cost;

    for(int i = 0;i <= 3;i++){
        int dx = xx[i] + x;
        int dy = yy[i] + y;
        if(reachable(dx,dy)){
            used[dx][dy] = true;
            // 计算成本并前往下一步
            if(mp[dx][dy] == 0 || mp[dx][dy] == 1){
                if(mp[dx][dy] == mp[x][y]){
                    dfs(dx,dy,cost,false);
                }
                else{
                    dfs(dx,dy,cost + 1,false);
                }
            }
            else{
                if(!mag){
                    mp[dx][dy] = mp[x][y];
                    dfs(dx,dy,cost + 2,true);
                    mp[dx][dy] = -1;
                }
            }
            used[dx][dy] = false;
        }
    }
}

void Oper(){
    dfs(1,1,0,false);
    if(!op){
        printf("%d",-1);
    }
    else{
        printf("%d",ans);
    }
}

void Inp(){
    memset(mp,-1,sizeof(mp));
    memset(mem,0x7f,sizeof(mem));
    m = read(),n = read();
    for(int i = 1;i <= n;i++){
        int x = read(),y = read();
        mp[x][y] = read();
    }
}

void work(){
    Inp();
    Oper();
}

int main(){
    work();
    return 0;
}