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
const van MaxN=30+10;
van n,a[MaxN];
namespace SpecialSolution {
	void main() {
		if (n==1) cout<<fixed<<setprecision(10)<<0<<endl;
		else cout<<fixed<<setprecision(10)<<min(a[1],a[2])/2.0<<endl;
	}
}
namespace FakeRrute {
	double res;
	void DFS(van tea,van stu,van dep,van sum,double perc) {
		if ((stu|tea)==(1<<n)-1) { // cout<<sum<<" "<<perc<<endl;
			res+=(double)sum*perc;
			return;
		}
		for (int i=1;i<=n;i++) {
			if (!(stu&(1<<(i-1)))&&!(tea&(1<<(i-1)))) {
				stu|=(1<<(i-1));// out<<i<<endl;
				for (int j=1;j<=n;j++) {
					if (!(tea&(1<<(j-1)))) { van tmp=sum;
						if (!(stu&(1<<(j-1)))) tmp+=a[j];
						DFS(tea|(1<<(j-1)),stu,dep+1,tmp,perc*1.0/(double)(n-dep)*1.0/(double)(n-dep));
					}
				}
				stu^=(1<<(i-1));
			}
		}
	}
	void main() {
		DFS(0,0,0,0,1);cout<<fixed<<setprecision(10)<<res<<endl;
	}
}
namespace Accepted {
	void main() {
		double l=0,r=40; 
		for (int i=1;i<=100;i++) {
			double mid=(l+r)/2.0,sum=0;int num=0;
			for (int i=1;i<=n;i++) if (a[i]>mid) sum+=mid/a[i],num++;
			if (sum<num-1) l=mid;else r=mid;
		} cout<<fixed<<setprecision(10)<<l<<endl;
		return;
	}
}
int main() {
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	read(n);for (int i=1;i<=n;i++) read(a[i]);
	Accepted::main();
//	if (n<=2) SpecialSolution::main();
//	else FakeRrute::main();
}
