#include<bits/stdc++.h>
using namespace std;
typedef long long van;
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
van n,ans;vector<van> g[MaxN];
van siz[MaxN],b[MaxN];bool used[MaxN],ok;
void DFS(van now) {
	used[now]=1,siz[now]=1;
	for (int i=0;i<g[now].size();i++) 
		if (!used[g[now][i]]) {
			DFS(g[now][i]);
			siz[now]+=siz[g[now][i]];
		}
}
int main() {
//	freopen("eat.in","r",stdin);
//	freopen("eat.out","w",stdout);
	read(n);for (int i=1;i<n;i++) {
		van u,v;read(u),read(v);
		g[u].push_back(v);
		g[v].push_back(u);
	}DFS(1);for (int i=1;i<=n;i++) b[siz[i]]++;
	for (int i=1;i<=n;i++) if (n%i==0) {
		van res=0;for (int j=1;j<=n/i;j++) res+=b[j*i];
		ans+=res==n/i;
	}
	print(ans),putchar('\n');
}
