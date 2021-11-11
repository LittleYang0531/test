#include<bits/stdc++.h>
using namespace std;
typedef long long van;
template<typename T> inline
void read(T& x) {
	T f=1,b=0;char ch=getchar();
	while (!isdigit(ch)) {
		if (ch=='-') f=-x;
		ch=getchar();
	}
	while (isdigit(ch)) 
		b*=10,b+=ch-'0',ch=getchar();
	x=f*b;return;
}
template<typename T> inline
void print(T x) {
	if (x<0) putchar('-'),x=-x;
	if (x>9) print(x/10);putchar(x%10+'0');
}
const van MaxN=1e6+10;
van dfn[MaxN],cnt=0,low[MaxN];
van st[MaxN],top=0;bool inst[MaxN];
vector<van> g[MaxN];van num=0,siz[MaxN];
void tarjan(van now,van f=0) {
	low[now]=dfn[now]=++cnt;
	for (int i=0,v;i<g[now].size();i++) {
		if (!dfn[v=g[now][i]]) {
			st[++top]=v,inst[v]=1;tarjan(v,now),low[now]=min(low[now],low[v]);
			if (low[v]>=dfn[now]) {
				num++;while (st[top]!=v) siz[num]++,inst[st[top--]]=0;
				siz[num]+=2,inst[st[top--]]=0;
			}
		}
		else if (v!=f) low[now]=min(low[now],dfn[v]);
	} 
}
int main() {
//	freopen("graph.in","r",stdin);
	van n,m,ans=0;read(n),read(m);
	for (int i=1;i<=m;i++) {
		van u,v;read(u),read(v);
		g[u].push_back(v);
		g[v].push_back(u);
	} for (int i=1;i<=n;i++) if (!dfn[i]) st[top=1]=i,tarjan(i);
	for (int i=1;i<=num;i++) ans+=siz[i]*(siz[i]-1)/2;
	print(ans),putchar('\n');return 0;
}
