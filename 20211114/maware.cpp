#include<bits/stdc++.h>
#pragma GCC optimize(2,"Ofast","inline")
using namespace std;
typedef long long van;
template<typename T> inline
void read(T& x) {
	T f=1,b=0;char ch=getchar();
	while (!isdigit(ch)) {
		if (ch=='-') f=-1;
		ch=getchar();
	} while (isdigit(ch)) 
		b*=10,b+=ch-'0',ch=getchar();
	x=f*b;return;
}
template<typename T> inline
void print(T x) {
	if (x<0) putchar('-'),x=-x;
	if (x>9) print(x/10);putchar(x%10+'0');
}
const van MaxN=210;
van n;van sum[MaxN][MaxN];
van ans[MaxN*MaxN];
int main() {
	freopen("maware.in","r",stdin);
	freopen("maware.out","w",stdout);
	van T;read(T);for (int tt=1;tt<=T;tt++) {
		memset(sum,0,sizeof sum);memset(ans,0,sizeof ans);
		read(n);for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) read(sum[i][j]);
		for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) 
			sum[i][j]+=sum[i][j-1]+sum[i-1][j]-sum[i-1][j-1];
		for (register int goal=0;goal<=sum[n][n];goal++) { 
			if (sum[n][n]==goal||goal%(sum[n][n]-goal)!=0) continue;van res=0;
			for (register int x1=1;x1<=n;x1++) for (register int x2=x1;x2<=n;x2++) {
				ans[0]=1;for (register int i=1;i<=n;i+=2) {
					van now=sum[x2][i]-sum[x1-1][i];
					if (now>=goal) res+=ans[now-goal];
					ans[now]++; if (i!=n) {
						now=sum[x2][i+1]-sum[x1-1][i+1];
						if (now>=goal) res+=ans[now-goal];
						ans[now]++;	
					}
				} for (register int i=1;i<=n;i+=2) {
					ans[sum[x2][i]-sum[x1-1][i]]--;
					if (i!=n) ans[sum[x2][i+1]-sum[x1-1][i+1]]--;
				}
			} if (res) print(goal/(sum[n][n]-goal)),putchar(' '),print(res),putchar('\n');
		}
	}
}
