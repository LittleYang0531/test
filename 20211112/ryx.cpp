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
char res[41][41];van num;
void solve1() {
	print(40),putchar(' '),print(40),putchar('\n');
	van block=num/4,single=num%4; 
	for (int i=1;i<=37&&block;i+=3) {
		for (int j=1;j<=37&&block;j+=3) {
			res[i][j]='r',res[i][j+1]='x',res[i][j+2]='x',
			res[i+1][j]='r',res[i+1][j+1]='y',res[i+1][j+2]='x',
			res[i+2][j]='r',res[i+2][j+1]='r',res[i+2][j+2]='x',block--;
		}
	}
	for (int i=1;i<=37&&single;i+=3) res[i][40]='r',res[i+1][40]='y',res[i+2][40]='x',single--;
	for (int i=1;i<=40;i++) {
		for (int j=1;j<=40;j++) {
			if (res[i][j]==0) res[i][j]='r';
		}
	}
	for (int i=1;i<=40;i++) {
		for (int j=1;j<=40;j++) putchar(res[i][j]);putchar('\n');
	}
}
void solve2() {
	print(40),putchar(' '),print(40),putchar('\n');
	van X=num/116,lst=num%116,i,k;
	for (int j=1;j<=40;j++) res[1][j]='x';
	for (i=1,k=1;i<=37&&X;i+=2,k^=1) {
		for (int j=1;j<=40;j++) res[i+1][j]='y';
		for (int j=1;j<=40;j++) res[i+2][j]=k?'r':'x';
		X--;
	}van lim=1;
	for (int j=1;j<=40&&i!=39&&lst>=lim;j++) {
		res[i+1][j]='y',res[i+2][j]=k?'r':'x',lst-=lim;
		if (j==1) lim=k?2:3;if (j==2) lim=3;
	} res[40][1]='x';
	for (i=1,k=1;i<=37&&lst;i+=2,k^=1) {
		res[40][i+1]='y',res[40][i+2]=k?'r':'x',lst--;
	}
	for (i=1;i<=40;i++) {
		for (int j=1;j<=40;j++) {
			if (res[i][j]==0) res[i][j]='x';
		}
	}
	for (i=1;i<=40;i++) {
		for (int j=1;j<=40;j++) putchar(res[i][j]);putchar('\n');
	}
}
int main() {
	freopen("ryx.in","r",stdin);
	freopen("ryx.out","w",stdout);
	read(num);
	if (num<=640) solve1();
	else solve2();
}
