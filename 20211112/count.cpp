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
const van MaxN=50+10;
const van mod=998244353;
van n,f[MaxN];
namespace Accepted {
	map<vector<van>,van> dp[2];van l[MaxN];
	void main() {
		for (int i=1;i<=n;i++) if (f[i]<f[i+1]) {print(0);return;}
		for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) if (f[j]>=i) l[i]++;
		dp[0][vector<van>(1,n)]=1;
		for (int i=1;i<n;i++) {
			dp[i%2].clear();map<vector<van>,van>::iterator it;
			for (it=dp[1-i%2].begin();it!=dp[1-i%2].end();it++) { 
				vector<van> a=(*it).first;van val=(*it).second;
				for (int j=0;j<a.size();j++) {
					for (int k=1;k<=a[j];k++) {
						vector<van> b=a;
						b.push_back(b[j]-k);b[j]=k-1;sort(b.begin(),b.end(),greater<van>());
						while (b.size()&&b.back()==0) b.pop_back();
						reverse(b.begin(),b.end());if (b.back()!=l[i+1]) continue;
						if (dp[i%2][b]==0) dp[i%2][b]=dp[1-i%2][b];
						dp[i%2][b]+=val,dp[i%2][b]%=mod;
					}
				}
			}
		}
		van ans=0;
		print(dp[1-n%2][{1}]);
		return;
	}
}
int main() {
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	read(n);for (int i=1;i<=n;i++) read(f[i]);
	bool A=true;for (int i=1;i<=n;i++) if (f[i]!=n-i+1) A=false;
	Accepted::main();
}
