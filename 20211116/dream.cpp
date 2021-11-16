#include<bits/stdc++.h>
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
using namespace std;
typedef long long van;
char buf[1<<21],*p1=buf,*p2=buf;
template<typename T> inline
void read(T& x) {
	T f=1,b=0;char ch=getchar();
	while (!isdigit(ch)) {
		if (ch=='-') f=-1;
		ch=getchar();
	} while (isdigit(ch)) {
		b*=10;b+=ch-'0';ch=getchar();
	} x=f*b;return;
} 
van st[20],top=0;
template<typename T> inline
void print(T x) {
	while (x) {
		st[++top]=x%10;x/=10;
	} while (top) putchar(st[top--]+'0');
}
const van MaxN=3e6+10;
const van mod=998244353;
van n,q,a[MaxN],bs[MaxN],inv[MaxN],tmp[MaxN],ans;
int main() {
	freopen("dream.in","r",stdin);
	freopen("dream.out","w",stdout);
	read(n),read(q);
	inv[1]=1;for (int i=2;i<=n;i++) inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	for (int i=1;i<=n;i++) tmp[i]=tmp[i-1]+inv[i],tmp[i]%=mod;
	for (int i=1;i<=n;i++) read(a[i]);
	van sum=0;for (int i=1,j=n;i<=j;i++,j--) {
		sum+=tmp[j]+mod-tmp[i-1],sum%=mod;
		bs[i]=bs[j]=sum;
	}
	for (int i=1;i<=n;i++) ans+=a[i]*bs[i],ans%=mod;
	print(ans),putchar('\n');
	for (int qq=1;qq<=q;qq++) {
		van x,y;read(x),read(y);
		ans+=mod-a[x]*bs[x]%mod,ans%=mod,a[x]=y;
		ans+=a[x]*bs[x]%mod,ans%=mod;
		print(ans),putchar('\n');
	}
	return 0;
}
