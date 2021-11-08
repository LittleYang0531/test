#include<bits/stdc++.h>
#define van long long
using namespace std;
template<typename T> inline
void read(T& x) {
	T f=1,b=0;char ch=getchar();
	while (!isdigit(ch)) {
		if (ch=='-') f=-1;
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
const van mod=1e9+7;
van n,d[MaxN][2];bool used[MaxN];
vector<van> g[MaxN];
van sum[MaxN],mul[MaxN],ans;
void dfs(van now,van dep,van to) {
	used[now]=1;d[now][to]=dep;
	for (int i=0;i<g[now].size();i++) {
		if (!used[g[now][i]]) {
			dfs(g[now][i],dep+1,to);
		}
	}
}
van bfs(van st,van& step) {
	memset(used,0,sizeof used);
	queue<pair<van,van> > q;q.push(make_pair(st,0));
	van now=0;step=0;
	while (!q.empty()) {
		now=q.front().first,step=q.front().second;q.pop();
		for (int i=0;i<g[now].size();i++) {
			if (!used[g[now][i]]) {
				used[g[now][i]]=1;
				q.push(make_pair(g[now][i],step+1));
			}
		}
	}
	return now;
};
int main() {
	freopen("tree.in","r",stdin);
	read(n);van len=0;
	for (int i=1;i<n;i++) {
		van u,v;read(u),read(v);
		g[u].push_back(v);
		g[v].push_back(u);
	}van st1=bfs(1,len),st2=bfs(st1,len);
	memset(used,0,sizeof used);dfs(st1,0,0);
	memset(used,0,sizeof used);dfs(st2,0,1);
	mul[0]=1;for (int i=1;i<=n;i++) mul[i]=2*mul[i-1],mul[i]%=mod;
	van mind=0;
	for (int i=1;i<=n;i++) 
		if (i!=st1&&i!=st2)
			mind=max(mind,min(d[i][0],d[i][1])),
			sum[max(d[i][0],d[i][1])]++;
	for (int i=1;i<=n;i++) sum[i]+=sum[i-1];
	for (int i=mind;i<=len;i++) {
		if (i==mind) ans+=2*(mul[sum[i]]*i%mod)%mod;
		else ans+=2*((mul[sum[i]]-mul[sum[i-1]])%mod+mod)%mod*i%mod;
		ans%=mod;
	}
	freopen("tree.out","w",stdout);
	ans+=mul[n-1]*len%mod,ans%=mod;
	print(ans),putchar('\n');
	return 0;
}
