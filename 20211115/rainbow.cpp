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
		b*=10,b+=ch-'0',ch=getchar();
	x=f*b;return;
}
template<typename T> inline
void print(T x) {
	if (x<0) putchar('-'),x=-x;
	if (x>9) print(x/10);putchar(x%10+'0');
}
const van MaxN=2e5+10;
const van MaxW=2e5+10;
const van mod=998244353;
van n,m,a[MaxN];vector<van> g[MaxN];
namespace solve1 {
	van col[MaxN],ans;
	bool check() {
		for (int i=1;i<=n;i++) {
			for (int j=0;j<g[i].size();j++) {
				if (col[i]==col[g[i][j]]) return false;
			}
		} return true;
	}
	void DFS(van now=1) {
		if (now>n) {
			ans+=check();ans%=mod;return;
		} for (int i=1;i<=a[now];i++) {
			col[now]=i;DFS(now+1);
		}
	}
	void main() {
		DFS();print(ans);putchar('\n');
	}
}
namespace solve2 {
	van line[MaxN],en[MaxN],cnt=0;
	bool used[MaxN];van ans=1,sum[MaxN];
	void DFS(van st) {
		line[++cnt]=st,used[st]=1;van id=cnt;
		van now=st;while (1) {
			if (g[now].size()==1&&used[g[now][0]]) break;
			now=!used[g[now][0]]?g[now][0]:g[now][1];
			line[++cnt]=now,used[now]=1;
		} en[id]=cnt;
	}
	void main() {
		for (int i=1;i<=n;i++) if (g[i].size()==1) DFS(i);
		for (int i=1;i<=n;i++) {
			van l=i,r=en[i];sum[l]=a[l];
			for (int j=l+1;j<=r;j++) {
				if (a[j-1]<=a[j]) sum[j]=sum[j-1]*a[j]-sum[j-1];
				else sum[j]=sum[j-1]*a[j]-sum[j-1];// This sentence is wrong.
			} ans*=sum[r];i=r+1;
		} print(ans);putchar('\n');return;
	}
}
namespace Accepted {
	struct SegmentTree {
		van dat[MaxN<<2];van lazytag1[MaxN<<2],lazytag2[MaxN<<2],clear[MaxN<<2];
		void BuildTree(van p=1,van l=1,van r=MaxW) {
			if (l==r) {
				dat[p]=0;lazytag1[p]=1,lazytag2[p]=0;
				clear[p]=0;return;
			}
			van mid=(l+r)>>1;
			BuildTree(p*2,l,mid);
			BuildTree(p*2+1,mid+1,r);
			dat[p]=dat[p*2]+dat[p*2+1],dat[p]%=mod;
			lazytag1[p]=1,lazytag2[p]=0;clear[p]=0;
		}
		void Spread(van p,van ls,van rs) {
			if (clear[p]) {
				dat[p*2]=0,dat[p*2+1]=0;
				lazytag1[p*2]=1,lazytag1[p*2+1]=1;
				lazytag2[p*2]=0,lazytag2[p*2+1]=0;
				clear[p*2]=1;clear[p*2+1]=1;clear[p]=0;
				return;
			}
			if (lazytag1[p]!=1) {
				dat[p*2]*=lazytag1[p],dat[p*2+1]*=lazytag1[p];
				dat[p*2]%=mod,dat[p*2]+=mod,dat[p*2]%=mod;
				dat[p*2+1]%=mod,dat[p*2+1]+=mod,dat[p*2+1]%=mod;
				lazytag1[p*2]*=lazytag1[p],lazytag1[p*2+1]*=lazytag1[p];
				lazytag1[p*2]%=mod,lazytag1[p*2]+=mod,lazytag1[p*2]%=mod;
				lazytag1[p*2+1]%=mod,lazytag1[p*2+1]+=mod,lazytag1[p*2+1]%=mod;
				lazytag2[p*2]*=lazytag1[p],lazytag2[p*2+1]*=lazytag1[p];
				lazytag2[p*2]%=mod,lazytag2[p*2]+=mod,lazytag2[p*2]%=mod;
				lazytag2[p*2+1]%=mod,lazytag2[p*2+1]+=mod,lazytag2[p*2+1]%=mod;
				lazytag1[p]=1;
			} if (lazytag2[p]) {
				dat[p*2]+=lazytag2[p]*ls,dat[p*2+1]+=lazytag2[p]*rs;
				dat[p*2]%=mod,dat[p*2]+=mod,dat[p*2]%=mod;
				dat[p*2+1]%=mod,dat[p*2+1]+=mod,dat[p*2+1]%=mod;
				lazytag2[p*2]+=lazytag2[p],lazytag2[p*2+1]+=lazytag2[p];
				lazytag2[p*2]%=mod,lazytag2[p*2]+=mod,lazytag2[p*2]%=mod;
				lazytag2[p*2+1]%=mod,lazytag2[p*2+1]+=mod,lazytag2[p*2+1]%=mod;
				lazytag2[p]=0;
			}
		}
		void Update(van L,van R,van p=1,van l=1,van r=MaxW) {
			if (L<=l&&r<=R) {
				dat[p]*=-1,lazytag1[p]*=-1,lazytag2[p]*=-1;
				dat[p]%=mod,dat[p]+=mod,dat[p]%=mod;
				lazytag1[p]%=mod,lazytag1[p]+=mod,lazytag1[p]%=mod;
				lazytag2[p]%=mod,lazytag2[p]+=mod,lazytag2[p]%=mod;
				return;
			}
			van mid=(l+r)>>1;Spread(p,mid-l+1,r-mid);
			if (L<=mid) Update(L,R,p*2,l,mid);
			if (R>mid) Update(L,R,p*2+1,mid+1,r);
			dat[p]=dat[p*2]+dat[p*2+1];dat[p]%=mod;
			return;
		}
		void UpdateTree(van L,van R,van num,van p=1,van l=1,van r=MaxW) {
			if (L<=l&&r<=R) {
				dat[p]+=num*(r-l+1);dat[p]%=mod;
				lazytag2[p]+=num;lazytag2[p]%=mod;
				return;
			}
			van mid=(l+r)>>1;Spread(p,mid-l+1,r-mid);
			if (L<=mid) UpdateTree(L,R,num,p*2,l,mid);
			if (R>mid) UpdateTree(L,R,num,p*2+1,mid+1,r);
			dat[p]=dat[p*2]+dat[p*2+1],dat[p]%=mod;
		}
		van QueryTree(van L,van R,van p=1,van l=1,van r=MaxW) {
			if (L<=l&&r<=R) return dat[p];
			van mid=(l+r)>>1,sum=0;Spread(p,mid-l+1,r-mid);
			if (L<=mid) sum+=QueryTree(L,R,p*2,l,mid);
			if (R>mid) sum+=QueryTree(L,R,p*2+1,mid+1,r);
			return sum%mod;
		}
		void Clear(van L,van R,van p=1,van l=1,van r=MaxW) {
			if (L>R) return;
			if (L<=l&&r<=R) {
				dat[p]=0,lazytag1[p]=1;
				lazytag2[p]=0;clear[p]=1;
//				cout<<l<<" "<<r<<endl;
				return;
			}
			van mid=(l+r)>>1;Spread(p,mid-l+1,r-mid);
			if (L<=mid) Clear(L,R,p*2,l,mid);
			if (R>mid) Clear(L,R,p*2+1,mid+1,r);
			dat[p]=dat[p*2]+dat[p*2+1],dat[p]%=mod;
			return;
		}
	}T;
	bool incircle[MaxN],used[MaxN];
	van en[MaxN],line[MaxN],cnt;
	bool DFS(van now,van f=0) {
		used[now]=1;bool incir=false;line[++cnt]=now;
		for (int i=0;i<g[now].size();i++) {
			if (g[now][i]==f) continue;
			if (used[g[now][i]]) return incircle[now]=true;
			incir|=DFS(g[now][i],now);
		} return incircle[now]=incir;
	}
	void Output(van l,van r) {
		for (int i=l;i<=r;i++) cout<<T.QueryTree(i,i)<<" ";cout<<endl;
	}
	void main() { van ll=1;
		for (int i=1;i<=n;i++) if (g[i].size()==1&&!used[i]) DFS(i),en[ll]=cnt,ll=cnt+1;
		for (int i=1;i<=n;i++) if (!used[i]) DFS(i),en[ll]=cnt,ll=cnt+1;
		van ans=1; for (int i=1;i<=n;i++) {
			van l=i,r=en[i];T.BuildTree();T.UpdateTree(1,a[line[l]],1);
			for (int j=l+1;j<=r;j++) {
				Output(1,a[line[j-1]]);
				van sum=T.QueryTree(1,a[line[j-1]]);// cout<<a[line[j-1]]<<" "<<sum<<endl;
				T.Update(1,a[line[j-1]]);T.Clear(a[line[j-1]]+1,a[line[j]]);
				T.UpdateTree(1,a[line[j]],sum);
			} ans*=T.QueryTree(1,a[line[r]]);Output(1,a[line[r]]);ans%=mod;i=r; 
		} print(ans);putchar('\n');
	}
}
int main() {
	freopen("rainbow.in","r",stdin);
//	freopen("rainbow.out","w",stdout);
	read(n),read(m);
	for (int i=1;i<=n;i++) read(a[i]);
	for (int i=1;i<=m;i++) {
		van u,v;read(u),read(v);
		g[u].push_back(v);
		g[v].push_back(u);
	} solve1::main();Accepted::main();
	return 0;
}
