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
	van st[22]={0},top=0;
	while (x) st[++top]=x%10,x/=10;
	while (top) putchar(st[top--]^'0');
} const van MaxN=1e5+10;
van T,n,a[MaxN],root;
bool used[MaxN];van dp[MaxN];
vector<van> g[MaxN];bool fail;
van siz[MaxN],asum[MaxN];
void clear() {
	for (int i=1;i<=n;i++) g[i].clear();
	memset(a,0,sizeof a);root=0;
	memset(used,0,sizeof used);
	memset(siz,0,sizeof siz);
	memset(asum,0,sizeof asum);
	memset(dp,0,sizeof dp);fail=false;
}
void DFS(van now=1) {
	van sum=0,max_=0;used[now]=1;
	if (g[now].size()==1) {
		dp[now]=a[now],asum[now]=a[now];
		return;
	}
	for (int i=0;i<g[now].size();i++) {
		if (used[g[now][i]]) continue;DFS(g[now][i]);
		sum+=dp[g[now][i]];max_=max(max_,dp[g[now][i]]);
		asum[now]+=asum[g[now][i]];
	} dp[now]=2*a[now]-sum;
	if (dp[now]>asum[now]) fail=true;
	if (2*(sum-max_)<(sum-dp[now])) fail=true;
	asum[now]+=a[now];
}
int main() {
	freopen("clean.in","r",stdin);
	freopen("clean.out","w",stdout);
	read(T);for (int tt=1;tt<=T;tt++) {
		clear();read(n); 
		for (int i=1;i<=n;i++) read(a[i]);
		for (int i=2;i<=n;i++) {
			van u,v;read(u),read(v);
			g[u].push_back(v);
			g[v].push_back(u);
		} 
		if (n==2) {
			puts(a[1]==a[2]?"YES":"NO");
			continue;
		} else if (n==1) {
			puts(a[1]?"NO":"YES");
			continue;
		}
		for (int i=1;i<=n;i++) if (g[i].size()!=1) root=i;
		DFS(root);puts(dp[root]||fail?"NO":"YES");
	} 
	return 0;
}

