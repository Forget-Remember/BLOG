#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>
#define mmin(a,b) (a < b ? a : b)
#define mmax(a,b) (a > b ? a : b)
#define lowbit(x) (x & (-x))
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


const int MAXN = 1e6 + 5;
int n;
int a[MAXN],c[MAXN],b[MAXN];
int m;
struct ASK{
    int l, r, index;
    int ans;
}k[MAXN];
void Inp(){
    n = read();
    for (int i = 1;i <= n;i++)
        a[i] = read();
    m = read();
    for (int i = 1;i <= m;i++){
        k[i].l = read();
        k[i].r = read();
        k[i].index = i;
    }
}

void add(int x,int data){
    for (; x <= n;x += lowbit(x)){
        c[x] += data;
    }
}

int ask(int x){
    int val = 0;
    for (; x; x -= lowbit(x)){
        val += c[x];
    }
    return val;
}

bool cmp1(ASK a,ASK b){
    return a.r < b.r;
}
bool cmp2(ASK a,ASK b){
    return a.index < b.index;
}

void Oper(){
    sort(k + 1, k + m + 1,cmp1);
    int last = 1;
    for (int i = 1;i <= m;i++){
        for (int j = last; j <= k[i].r; j++){
            if (b[a[j]])
                add(b[a[j]], -1);
            //之前打过标记，在之前的位置加上-1，保证无重复
            add(j,1);
            b[a[j]]=j;
        }
        //更新下一次查询的位置
        last = k[i].r + 1;
        //按询问编号存储每组询问的结果
        k[i].ans = ask(k[i].r) - ask(k[i].l - 1);
    }
    sort(k + 1, k + m + 1,cmp2);
    for (int i = 1;i <= m;i++){
        printf("%d\n",k[i].ans);
    }
}