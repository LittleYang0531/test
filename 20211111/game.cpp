#include<bits/stdc++.h>
using namespace std;
typedef long long van;
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
int main() {
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout); 
	van T;read(T);for (int t=1;t<=T;t++) {
		van a1,b1,a2,b2,n;read(a1),read(b1),read(a2),read(b2),read(n);
		if (b2>b1) swap(a1,a2),swap(b1,b2);
		van ans=0;for (int i=1;i<=n;i++) {
			van agoal=a1/i,bgoal=a1/i-b2+b1;
			van al=a1/(agoal+1),ar=agoal==0?n:a1/agoal,
				bl=a2/(bgoal+1),br=bgoal==0?n:a2/bgoal;
			ans+=max((van)0,min(br,min(ar,n))-max(al,bl));i=ar;
		}
		print(ans);putchar('\n');
	}
	return 0;
}
