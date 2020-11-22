#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
#define mmin(a,b) (a < b ? a : b)
#define mmax(a,b) (a > b ? a : b)
using namespace std;

inline int read(){
    int x = 0, f = 1;
    char ch = getchar();
    while(!isdigit(ch)){
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(isdigit(ch)){
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}
void Work(),Inp(),Oper();
int main(){
    Work();
    return 0;
}
void Work(){
    Inp();
    Oper();
}


const int MAXN = 200;
const int MAXM = 6000;
struct EDGE{
    int to,next,dis,from;
}edge[MAXM << 1];
int head[MAXN],tot;
void add_edge(int from,int to,int dis){
    edge[++tot].next = head[from];
    head[from] = tot;
    edge[tot].to = to;
    edge[tot].dis = dis;
    edge[tot].from = from;
}
int n,m;

void Inp(){
    n = read();
    m = read();
    for(int i = 1;i <= m;i++){
        int a = read(),b = read(),d = read();
        add_edge(a,b,d);
        add_edge(b,a,d);
    }
}

// pre[p]用于存储到达 点p 的最短路中 到达 点p 的 边的编号
int dist[MAXN],pre[MAXN],cnt;
bool v[MAXN];
void dij(){
    memset(v,0,sizeof(v));
    for(int i = 1;i <= n;i++){
        dist[i] = 0x7fffffff;
    }
    dist[1] = 0;
    pre[1] = 0;
    priority_queue< pair<int,int> > que;
    que.push(make_pair(0,1));
    while(!que.empty()){
        int p = que.top().second;
        que.pop();
        if(v[p]) continue;
        v[p] = 1;
        for(int i = head[p];i;i = edge[i].next){
            int dd = edge[i].to;
            if(dist[dd] > dist[p] + edge[i].dis){
                dist[dd] = dist[p] + edge[i].dis;
                que.push(make_pair(-dist[dd],dd));
                pre[dd] = i;
            }
        }
    }
}

int ans = -2147483648;
// 从 点n 开始搜索，搜索到 点1 停止，当前所搜的点为 p，更改pre[p]
// 初始值dist[n]，更改后的最短路为dist2[n]，造成了 delta 的增加量
int dist2[MAXN];
void DIJ(){
    memset(v,0,sizeof(v));
    for(int i = 1;i <= n;i++){
        dist2[i] = 0x7fffffff;
    }
    dist2[1] = 0;
    priority_queue< pair<int,int> > que;
    que.push(make_pair(0,1));
    while(!que.empty()){
        int p = que.top().second;
        que.pop();
        if(v[p]) continue;
        v[p] = 1;
        for(int i = head[p];i;i = edge[i].next){
            int dd = edge[i].to;
            if(dist2[dd] > dist2[p] + edge[i].dis){
                dist2[dd] = dist2[p] + edge[i].dis;
                que.push(make_pair(-dist2[dd],dd));
            }
        }
    }
}

void DFS(int p = n){
    if(p == 1) return;
    edge[pre[p]].dis *= 2;
    DIJ();
    edge[pre[p]].dis /= 2;
    ans = mmax(ans,dist2[n]-dist[n]);
    DFS(edge[pre[p]].from);
}


void Oper(){
    dij();
    DFS();
    cout << ans << endl;
}