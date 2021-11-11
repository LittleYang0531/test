#include<bits/stdc++.h>
using namespace std;
typedef __int128 van;
template<typename T> inline
void read(T& x) {
	T f=1,b=0;char ch=getchar();
	while (!isdigit(ch)) {if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)) b*=10,b+=ch-'0',ch=getchar();
	x=f*b;return;
}
template<typename T> inline
void print(T x) {
	if (x<0) putchar('-'),x=-x;
	if (x>9) print(x/10);putchar(x%10+'0');
}
const van MaxN=1e5+10;
van a[MaxN],rx[MaxN],ry[MaxN];
van exgcd(van a,van b,van& x,van& y) {
    if (b==0) {x=1,y=0;return a;}
    van gcd=exgcd(b,a%b,x,y);
    van t=x;x=y,y=t-a/b*y;
    return gcd;
}
van ceil(van a,van b) {
    if (a%b==0) return a/b;
    else return a/b+1;
}
int main() {
	freopen("rand.in","r",stdin);
	freopen("rand.out","w",stdout); 
    a[1]=1,a[2]=1;int now=3;while(a[now-1]+a[now-2]<=1e18) a[now]=a[now-1]+a[now-2],now++;
    now--;for (int i=1;i<now;i+=2) exgcd(a[i],a[i+1],rx[i],ry[i]);
	van t;read(t);for (int tt=1;tt<=t;tt++) {
        van x,n,m,ans=0;read(x),read(n),read(m);
        if (x==0) {
        	print(1);putchar('\n');
        	continue;
		}
//        if (x<=n) ans++;
        for (int i=1;i<now;i+=2) {
            van resx=rx[i],resy=ry[i];
            resx*=x,resy*=x;van tims=0,anses=0;
            van ls=max(ceil(resy-m,a[i]),ceil(0-resx,a[i+1])),rs=min((resy-0)/a[i],(n-resx)/a[i+1]);
			ans+=max((van)0,rs-ls+1);
        }print(ans),putchar('\n');
    }
}
