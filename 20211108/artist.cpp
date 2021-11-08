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
const van MaxN=5e5+10;
struct node {
	van l,r,id;
}query[MaxN];
van n,m,q,c[MaxN];
vector<van> g[MaxN];
set<van> wh[MaxN];
van x[MaxN],y[MaxN];
van bef[MaxN],aft[MaxN];
van fa[MaxN],bel[MaxN],ans[MaxN];
bool used[MaxN],used2[MaxN];
struct S {
	van f[MaxN]={0};
	void init() {for (int i=1;i<=n;i++) f[i]=i;}
	van getfa(van x) {return f[x]==x?x:f[x]=getfa(f[x]);}
	void merge(van a,van b) {f[getfa(a)]=getfa(b);}
	bool check(van a,van b) {return getfa(a)==getfa(b);}
}Set;
bool cmp(node a,node b) {
	if (a.l==b.l) return a.r>b.r;
	else return a.l<b.l;
}
void BuildGraph() {
	stack<int> st;st.push(0);
	sort(query+1,query+m+1,cmp);
	for (int i=1;i<=m;i++) {
		while (query[st.top()].r<query[i].l) st.pop();
		g[st.top()].push_back(i);
		g[i].push_back(st.top());
		st.push(i);
	}
}
void DFS(van now=0) {
	used[now]=1;
	for (int i=0;i<g[now].size();i++) {
		if (!used[g[now][i]]) {
			fa[g[now][i]]=now;
//			cout<<now<<" "<<g[now][i]<<endl;
			DFS(g[now][i]);
		}
	}
}
struct SegmentTree {
	van dat[MaxN*4]={0};
	void BuildTree(van p=1,van l=1,van r=n) {
		if (l==r) {dat[p]=bef[l];return;}
		van mid=(l+r)>>1;
		BuildTree(p*2,l,mid);
		BuildTree(p*2+1,mid+1,r);
		dat[p]=max(dat[p*2],dat[p*2+1]);
	}
	void UpdateTree(van wh,van num,van p=1,van l=1,van r=n) {
		if (l==r) {if (l==wh) dat[p]=num;return;}
		van mid=(l+r)>>1;
		if (wh<=mid) UpdateTree(wh,num,p*2,l,mid);
		else UpdateTree(wh,num,p*2+1,mid+1,r);
		dat[p]=max(dat[p*2],dat[p*2+1]);
	}
	van QueryTree(van L,van R,van p=1,van l=1,van r=n) {
		if (L<=l&&r<=R) return dat[p];
		van mid=(l+r)>>1,res=0;
		if (L<=mid) res=max(res,QueryTree(L,R,p*2,l,mid));
		if (R>mid) res=max(res,QueryTree(L,R,p*2+1,mid+1,r));
		return res;
	}
}T;
void Full(van now=0) {
	used[now]=1;van lst=query[now].l;
	for (int i=0;i<g[now].size();i++) 
		if (!used[g[now][i]]) {
			for (int j=lst;j<query[g[now][i]].l;j++) 
				bel[j]=now;
			Full(g[now][i]);lst=query[g[now][i]].r+1;
		}
	for (int i=lst;i<=query[now].r;i++) bel[i]=now;
	return;
}
void Debug() {
	cout<<"/* Debug Info */"<<endl;
	cout<<"place: "<<endl;
	for (int i=1;i<=n;i++) {
		cout<<i<<": ";
		for (set<van>::iterator it=wh[i].begin();it!=wh[i].end();it++) 
			cout<<(*it)<<" ";cout<<endl;
	}
	cout<<"belong: "<<endl;
	for (int i=1;i<=n;i++) cout<<Set.getfa(bel[i])<<" ";cout<<endl;
	cout<<"before: "<<endl;
	for (int i=1;i<=n;i++) cout<<T.QueryTree(i,i)<<" ";cout<<endl;
	cout<<"/* End of Debug Info */"<<endl;
}
void solve() {
	T.BuildTree();van res=0;Set.init();
	memset(used,0,sizeof used);Full();
	for (int i=1;i<=n;i++) {
		van fath=Set.getfa(bel[i]);
		while (T.QueryTree(query[fath].l,query[fath].r)<query[fath].l) {
			Set.merge(fath,fa[fath]);
			ans[query[fath].id]=0;used2[fath]=1;
			fath=Set.getfa(fath);
		}
	}
	for (int i=1;i<=q;i++) {
//		Debug();
		T.UpdateTree(aft[x[i]],bef[x[i]]);
		if (aft[x[i]]!=n+1) bef[aft[x[i]]]=bef[x[i]];
		aft[bef[x[i]]]=aft[x[i]];
		wh[c[x[i]]].erase(wh[c[x[i]]].find(x[i]));van nxt=n+1;
		set<van>::iterator it=wh[y[i]].lower_bound(x[i]);
		if (it!=wh[y[i]].end()) nxt=*it;
		van before=(*--it);
		aft[before]=x[i],bef[x[i]]=before;
		bef[nxt]=x[i],aft[x[i]]=nxt;
		T.UpdateTree(x[i],before);
		T.UpdateTree(nxt,x[i]);
		van fath=Set.getfa(bel[x[i]]);
		while (T.QueryTree(query[fath].l,query[fath].r)<query[fath].l) {
			Set.merge(fath,fa[fath]);
			ans[query[fath].id]=i;res^=i;used2[fath]=1;
			fath=Set.getfa(fath);
		}c[x[i]]=y[i];wh[c[x[i]]].insert(x[i]);
	}
	for (int i=1;i<=m;i++) if (!used2[i]) res^=(m+query[i].id),ans[query[i].id]=m+query[i].id;
//	for (int i=1;i<=m;i++) cout<<ans[i]<<endl;
	print(res);putchar('\n');
}
int main() {
	freopen("artist.in","r",stdin);
	freopen("artist.out","w",stdout);
	read(n),read(m),read(q);
	for (int i=1;i<=n;i++) read(c[i]);query[0].r=n+1;
	for (int i=1;i<=m;i++) 
		read(query[i].l),read(query[i].r),query[i].id=i;
	for (int i=1;i<=q;i++) read(x[i]),read(y[i]);
	for (int i=1;i<=n;i++) wh[i].insert(0);
	for (int i=1;i<=n;i++) wh[c[i]].insert(i);
	for (int i=1;i<=n;i++) {
		if (wh[i].size()==1) continue;
		set<van>::iterator it=wh[i].begin();
		for ( ;it!=wh[i].end();it++) {
			van now=*it;
			if (it!=wh[i].begin()) bef[now]=*(--it),it++;
			if (it!=--wh[i].end()) aft[now]=*(++it),it--;
		}
	}BuildGraph();DFS();
	solve();return 0;
}
