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
const van MaxN=1e5+10;
van n,m,k,an,max_;bool guai[MaxN];
//van check() {
//	van ans=0;
//	for (int i=1;i<=n;i++) {
//		for (int j=i;j<=n;j++) {
//			van sum=0;
//			for (int k=i;k<=j;k++) {
//				if (guai[k]) sum++;
//			}
//			if (sum%2==1) ans++;
//		}
//	}
//	return ans;
//}
//void DFS(van num,van now,bool& output) {
//	if (num>k) {
//		an=max(an,check());
//		if (output&&(check()==max_)) {
//			for (int i=1;i<=n;i++) cout<<guai[i]<<" ";cout<<endl;
//			output=0;
//		}
//		return;
//	}
//	for (int i=now+1;i<=n-k+num;i++) {
//		guai[i]=1;
//		DFS(num+1,i,output);
//		guai[i]=0;
//	}
//}
int main() {
//	read(n);read(k);
//	DFS(1,0,0);max_=an;
//	DFS(1,0,1);
//	cout<<an<<endl;
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	read(n);read(k);van now=0;
	if (k==0) {
		print(0);putchar('\n');
		for (int i=1;i<=n;i++) print(0),putchar(' ');
		return 0;
	}
	print(n%2?(n+1)*(n+1)/4:n*n/4+n/2),putchar('\n');
	for (int i=1;i<k;i++) print(1),putchar(' ');now+=k;
	for (int i=1;i<=(k%2==1?(n-k)/2:(n-k+1)/2);i++) print(0),putchar(' ');
	print(1),putchar(' ');now+=(k%2==1?(n-k)/2:(n-k+1)/2);
	for (int i=now+1;i<=n;i++) print(0),putchar(' ');
	return 0;
//	read(m);
//	for (int j=1;j<=m;j++) {
//		for (int i=j;i<=m;i++) {
//			cout<<"n="<<i<<" k="<<j<<endl;
//			n=i,k=j;max_=0,an=0;
//			bool x0=0,x1=1;
//			DFS(1,0,x0);max_=an;
//			DFS(1,0,x1);
//			cout<<an<<endl;
//		}
//	}
}
