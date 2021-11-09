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
const van MaxT=2e6+10;
const van mod=19260817;
van ty,t,h,a,b,H,A,B,res;
van mul[MaxT];double pai=acos(-1);
void Read() {
    van x=1ll*h*H,y=1ll*a*A,z=1ll*b*B;
    h=(H^(y+z))%1000+1;
    a=(A^(x+z))%1000+1;
    b=(B^(x+y))%100000+1;
}
double calc() {
	if (b==0) return h*a;
	double x=acos((double(-a*h)+sqrt(double(a*a*h*h+4.0*b*b)))/2.0/(double)b);
	return (double)(h*a)/sin(x)+(double)(b)*x;
}
int main() {
	freopen("fly.in","r",stdin);
	freopen("fly.out","w",stdout);
	read(ty),read(t);mul[0]=1;
	for (int i=1;i<=t;i++) mul[i]=mul[i-1]*11514,mul[i]%=mod;
	if (ty) read(h),read(a),read(b),read(H),read(A),read(B);
	for (int tt=1;tt<=t;tt++) {
		if (!ty) read(h),read(a),read(b);
		else Read();
		double ans=calc();
		if (!ty) cout<<fixed<<setprecision(4)<<ans<<endl;
		else res+=van(ans*1e4)*mul[tt]%mod,res%=mod;
	}
	if (ty) print(res),putchar('\n');
	return 0;
}
