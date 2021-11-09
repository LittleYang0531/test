#include<bits/stdc++.h>
#define int register int
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
const van MaxN=1e7+10;
const van MaxS=350;
const van mod=998244353;
van n,m,size;
struct SumC {
	van S[MaxS][MaxS];
	van inc[MaxN],mul[MaxN];
	van belong[MaxN];
	van C(van from,van to) {
		return mul[from]*inc[to]%mod*inc[from-to]%mod;
	}
	van inv(van x) {
		van t=mod-2,base=x,ans=1;
		while (t) {
			if (t&1) ans*=base,ans%=mod;
			base*=base,base%=mod,t>>=1;
		}
		return ans;
	}
	void initMul() {
		mul[0]=1;for (int i=1;i<=n;i++) mul[i]=mul[i-1]*i%mod;
		for (int i=0;i<=n;i++) inc[i]=inv(mul[i]);
	}
	void initSumC() {
		initMul();
//		for (int i=0;i<=n;i++) belong[i]=i/size+1;
//		for (int i=1;i<=n/size+1;i++) {
//			S[i][1]=1;van sum=1;
//			for (int j=1;j<=i*size-size;j++) {
//				sum+=C(i*size-size,j),sum%=mod;
//				if (j%size==0) S[i][j/size+1]=sum;
//			}
//		}
	}
//	van GetSumC(van num,van k) {
//		k=min(k,num);
//		van base=S[belong[num]][belong[k]];
//		for (int i=belong[num]*size-size+1;i<=num;i++) 
//			base*=2,base%=mod,base+=mod-C(i-1,belong[k]*size-size),base%=mod;
//		for (int i=belong[k]*size-size+1;i<=k;i++) base+=C(num,i),base%=mod;
//		return base;
//	}
}s;
van c[MaxN],bel[MaxN],id[MaxN];van times=0;
struct block {
	struct node {
		van pos,val;
		bool operator < (const node a) const {
			return val<a.val;
		}
	};
	node num[MaxS];van siz=0,tag=0,bid;
	void init(van l,van r) {
		for (int i=l;i<=r;i++) num[id[i]]=(node){i,c[i]};
		siz=r-l+1;sort(num+1,num+siz+1),bid=bel[l];
//		cout<<"bid:"<<bid<<endl;
//		for (int i=1;i<=siz;i++) cout<<num[i].pos<<" "<<num[i].val<<endl;
	}
	node a[MaxS],b[MaxS],ls,rs;
	void add(van x) {tag+=x;}
	void add(van l,van r,van x) {
		for (int i=1;i<=siz;i++) num[i].val+=tag;
		tag=0;van ls=0,rs=0;
		for (int i=1;i<=size;i++) {
			if (num[i].pos<l||num[i].pos>r) a[++ls]=num[i];
			else b[++rs]=num[i];
		}l=1,r=1;van now=0;
		for (int i=1;i<=rs;i++) b[i].val+=x;
		while (l<=ls&&r<=rs) {
			if (a[l].val<=b[r].val) num[++now]=a[l++];
			else num[++now]=b[r++];
		}
		while (l<=ls) num[++now]=a[l++];
		while (r<=rs) num[++now]=b[r++];
	}
	van query(van x) {return upper_bound(num+1,num+siz+1,(node){0,x-tag})-num-1;}
	van query(van l,van r,van x) {
		van lim=upper_bound(num+1,num+siz+1,(node){0,x-tag})-num-1;
		van ans=0;for (int i=1;i<=lim;i++) 
			if (l<=num[i].pos&&num[i].pos<=r) ans++;
		return ans;
	}
}B[MaxS];
void Update(van l,van r,van x) {
	if (bel[l]==bel[r]) B[bel[l]].add(l,r,x);
	else {
		B[bel[l]].add(l,bel[l]*size,x);
		B[bel[r]].add(bel[r]*size-size+1,r,x);
		for (int i=bel[l]+1;i<bel[r];i++) B[i].add(x);
	}
}
van Query(van l,van r,van x) {
	van sum=0;if (bel[l]==bel[r]) sum+=B[bel[l]].query(l,r,x);
	else {
		sum+=B[bel[l]].query(l,bel[l]*size,x)+B[bel[r]].query(bel[r]*size-size+1,r,x);
		for (int i=bel[l]+1;i<bel[r];i++) sum+=B[i].query(x);
	} // cout<<sum<<endl;
	return sum;
}
struct Q {
	van id,n,m;
}q[MaxN];
const van sizz=324;
bool cmp2(Q x,Q y) {
	if (x.n/sizz!=y.n/sizz) return x.n/sizz<y.n/sizz;
	else if((x.n/sizz)&1) return x.m>y.m;
	else return x.m<y.m;
}
van ans[MaxN];
signed main() {
	freopen("cook.in","r",stdin);
	freopen("cook.out","w",stdout);
	read(n),read(m);size=sqrt(n);s.initSumC();
	for (int i=1;i<=n;i++) read(c[i]);
	for (int i=1;i<=n;i++) {
		if (i%size==0) bel[i]=i/size,id[i]=size;
		else bel[i]=i/size+1,id[i]=i%size;
	}van now=0;
	for (int i=1;i<=n/size+2;i++) B[i].init(i*size-size+1,i*size);
	for (int mm=1;mm<=m;mm++) {
		van op,l,r,x,k;read(op),read(l),read(r),read(x);
		if (op==1) Update(l,r,x);
		else read(k),q[++now].n=Query(l,r,x),
			 q[now].m=k,q[now].id=now;
	}
	sort(q+1,q+now+1,cmp2);
	van x=1,y=1,cnt=2,res=s.inv(2);
	for (int i=1;i<=now;i++) {
		//cout<<q[i].id<<" "<<q[i].n<<" "<<q[i].m<<endl;
		while (x>q[i].n) cnt+=s.C(--x,y),cnt%=mod,cnt*=res,cnt%=mod;
		while (y<q[i].m) cnt+=s.C(x,++y),cnt%=mod;
		while (x<q[i].n) cnt*=2,cnt%=mod,cnt+=mod-s.C(x++,y),cnt%=mod;
		while (y>q[i].m) cnt+=mod-s.C(x,y--),cnt%=mod;
		ans[q[i].id]=cnt;//cout<<cnt<<" "<<x<<" "<<y<<" "<<s.C(x-1,y)<<endl;
	}
	for (int i=1;i<=now;i++) print(ans[i]),putchar('\n');
//	cout<<times<<endl;
}
