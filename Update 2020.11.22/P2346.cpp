#include<bits/stdc++.h>
#define mmin(a,b) (a < b ? a : b)
#define mmax(a,b) (a > b ? a : b)
using namespace std;
inline void Work(),Inp(),Oper();
bool DFS(int,int,int,int,int,int);

int main(){
	Work();
	return 0;
}

void Work(){
	Inp();
	Oper();
}

int a[5][5];
int st1x,st1y,st2x,st2y;
int ans = 2147483647;
inline void Inp(){
	for(int i = 1;i <= 4;i++){
		for(int j = 1;j <= 4;j++){
			char ch;
			cin >> ch;
			if(ch == 'B') a[i][j] = 1;
			if(ch == 'W') a[i][j] = 2;
			if(ch == 'O') {
				a[i][j] = 0;
				if(st1x == 0) st1x = i,st1y = j;
				else st2x = i,st2y = j;
			}
		}
	}
}

inline bool Check(){
	for(int i=1;i<=4;i++){
		if(a[i][1]==a[i][2]&&a[i][2]==a[i][3]&&a[i][3]==a[i][4]) return true;
		if(a[1][i]==a[2][i]&&a[2][i]==a[3][i]&&a[3][i]==a[4][i]) return true;
	}
	if(a[1][1]==a[2][2]&&a[2][2]==a[3][3]&&a[3][3]==a[4][4]) return true;
	if(a[1][4]==a[2][3]&&a[2][3]==a[3][2]&&a[3][2]==a[4][1]) return true;
	return false;
}

inline void Oper(){
    for(ans = 0;1;ans++){
        if(DFS(st1x,st1y,st2x,st2y,1,0)) break;
        if(DFS(st1x,st1y,st2x,st2y,2,0)) break;
    }
	printf("%d",ans);
}

inline bool Reachable(int x,int y,int color){
	if(x < 1 || x > 4) return false;
	if(y < 1 || y > 4) return false;
	if(color == a[x][y]) return false;
	return true;
}

int xx[] = {  0,  0,  1, -1};
int yy[] = {  1, -1,  0,  0};
bool DFS(int x1,int y1,int x2,int y2,int color,int step){
	if(Check()){
		return true;
	}
	if(step >= ans) return false;

	for(int i = 0;i <= 3;i++){
		// int dx1 = xx[i] + x1;
		// int dy1 = yy[i] + y1;
		// int dx2 = xx[i] + x2;
		// int dy2 = yy[i] + y2;
		if(Reachable(xx[i] + x1,yy[i] + y1,color)){
			swap(a[xx[i] + x1][yy[i] + y1],a[x1][y1]);
			if(DFS(xx[i] + x1,yy[i] + y1,x2,y2,(color == 1 ? 2 : 1),step + 1)) return true;
			swap(a[xx[i] + x1][yy[i] + y1],a[x1][y1]);
		}
		if(Reachable(xx[i] + x2,yy[i] + y2,color)){
			swap(a[xx[i] + x2][yy[i] + y2],a[x2][y2]);
			if(DFS(x1,y1,xx[i] + x2,yy[i] + y2,(color == 1 ? 2 : 1),step + 1)) return true;
			swap(a[xx[i] + x2][yy[i] + y2],a[x2][y2]);
		}
	}
    return false;
}
