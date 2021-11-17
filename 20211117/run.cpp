#include<bits/stdc++.h>
using namespace std;
typedef long long van;
template<typename T> inline
void read(T& x) {
	T f=1,b=0;char ch=getchar();
	while (!isdigit(ch)) {
		if (ch=='-') f=-1;
		ch=getchar();
	} while (isdigit(ch))
		b*=10,b+=ch^'0',ch=getchar();
	x=f*b;return;
}
template<typename T> inline
void print(T x) {
	if (x==0) {
		putchar('0');return;
	}
	van st[22]={0},top=0;
	while (x) st[++top]=x%10,x/=10;
	while (top) putchar(st[top--]^'0');
}
const van MaxN=1e3+10;
van dp[MaxN][MaxN],n,m,sq[MaxN][MaxN];
int main() {
	freopen("run.in","r",stdin);
	freopen("run.out","w",stdout);
	read(n),read(m);memset(dp,0x3f,sizeof dp);dp[1][0]=0;
	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) read(sq[i][j]);
	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) {
		if (sq[i][j]==1) dp[i][j]=min(sq[i][j-1]?dp[i][j-1]:dp[i][j-1]+1,
									  sq[i-1][j]?dp[i-1][j]:dp[i-1][j]+1);
		else dp[i][j]=min(dp[i-1][j],dp[i][j-1]);
	} print(dp[n][m]);
	return 0;
}
