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
const van MaxN=5e5+10;
van n,m;vector<pair<van,pair<van,van> > > g[MaxN];
van uu[MaxN],vv[MaxN],dd[MaxN],ww[MaxN],id1[MaxN],id2[MaxN];
namespace solve1 {
    van dis[MaxN];bool used[MaxN];
    van Dijkstra(van st,van en) {
        memset(dis,(1<<6),sizeof dis);
        memset(used,0,sizeof used);dis[1]=0;
        priority_queue<pair<van,van> > q;
        q.push(make_pair(0,st));
        while (!q.empty()) {
            van now=q.top().second;q.pop();
            if (used[now]) continue;used[now]=1;
            for (int i=0;i<(van)g[now].size();i++) {
                van nxt=g[now][i].first,w=g[now][i].second.first;
                if (dis[nxt]>dis[now]+w) {
                    dis[nxt]=dis[now]+w;
                    q.push(make_pair(-dis[nxt],nxt));
                }
            }
        } return dis[en];
    }
    void main() {
        van ans=0;
        srand(time(0));// van x=m*(log(m)/log(2));
        for (int i=1;i<=m;i++) {
            van wh=i;
            g[uu[wh]][id1[wh]].second.first+=dd[wh];
            g[vv[wh]][id2[wh]].second.first+=dd[wh];
            van res=Dijkstra(1,n);ans=max(ans,res);
            g[uu[wh]][id1[wh]].second.first-=dd[wh];
            g[vv[wh]][id2[wh]].second.first-=dd[wh];
        }print(ans),putchar('\n');return;
    }
}
namespace solve2 {
    bool used[MaxN];van up[MaxN],dep[MaxN],val[MaxN],der[MaxN];
    void DFS(van now=1) {
        used[now]=1;
        for (int i=0,v;i<(van)g[now].size();i++) if (!used[v=g[now][i].first]) 
            up[v]=now,dep[v]=dep[now]+1,DFS(v);
    }
    void LCA(van a,van b,van& res) {
        van ans=0;res=0;if (dep[a]<dep[b]) swap(a,b);
        while (dep[a]>dep[b]) res=max(res,der[a]),ans+=val[a],a=up[a];
        if (a==b) {res+=ans;return;}
        while (up[a]!=up[b]) res=max(res,max(der[a],der[b])),
            ans+=val[a]+val[b],a=up[a],b=up[b];
        res=max(res,max(der[a],der[b])),ans+=val[a]+val[b],res+=ans;return;
    }
    void main() {
        dep[1]=1;DFS();
        for (int i=1;i<=n;i++) {
            for (int j=0;j<(van)g[i].size();j++) {
                van u=i,v=g[i][j].first;
                val[dep[u]>dep[v]?u:v]=g[i][j].second.first;
                der[dep[u]>dep[v]?u:v]=g[i][j].second.second;
            }
        }van res;LCA(1,n,res);
        print(res),putchar('\n');return;
    }
}
namespace solve3 {
    bool used[MaxN];bool incir[MaxN];
    van DFS(van now=1,van f=0){
        used[now]=1;for (int i=0,v;i<(van)g[now].size();i++) {
            if (!used[v=g[now][i].first]) {
                van res=DFS(v,now);
                if (res&&res!=now) {incir[now]=1;return res;}
            } else if (v!=f) {incir[now]=incir[v]=1;return v;}
        }
        return 0;
    }
    van st[MaxN],top=0,ressum,resmax_;
    bool DFS2(van now=1,van sum=0,van max_=0) {
        if (now==n) {
            ressum=sum,resmax_=max_;
            return true;
        }
        used[now]=1;st[++top]=now;
        for (int i=0;i<(van)g[now].size();i++) {
            if (!used[g[now][i].first]) {
                bool res=DFS2(g[now][i].first,
                    sum+g[now][i].second.first,max(max_,g[now][i].second.second));
                if (res) return true;
            }
        }top--;
        return false;
    } van res=0;
    void main() {
        DFS();memset(used,0,sizeof used);DFS2();
        van stcir=0,encir=0;memset(used,0,sizeof used);
        for (int i=1;i<=top;i++) {
            if (incir[st[i]]&&!stcir) stcir=st[i];
            if (!incir[st[i]]&&incir[st[i-1]]) encir=st[i-1];
            if (incir[st[i]]) used[st[i]]=1;
        } van res1=ressum,res2=resmax_;ressum=resmax_=0;
        used[stcir]=0;used[encir]=0;
        if (stcir) {
            top=0,DFS2();
            if (ressum<res1) res=min(ressum+resmax_,res1);
            else res=min(res1+res2,ressum);
        }
        print(res),putchar('\n');return;
    }
}
namespace solve4 {
    van randx() {
        return rand()*1e4+rand();
    }
    van dis[MaxN];bool used[MaxN];
    van Dijkstra(van st,van en) {
        memset(dis,(1<<6),sizeof dis);
        memset(used,0,sizeof used);dis[1]=0;
        priority_queue<pair<van,van> > q;
        q.push(make_pair(0,st));
        while (!q.empty()) {
            van now=q.top().second;q.pop();
            if (used[now]) continue;used[now]=1;
            for (int i=0;i<(van)g[now].size();i++) {
                van nxt=g[now][i].first,w=g[now][i].second.first;
                if (dis[nxt]>dis[now]+w) {
                    dis[nxt]=dis[now]+w;
                    q.push(make_pair(-dis[nxt],nxt));
                }
            }
        } return dis[en];
    }
    void main() {
        van ans=0;
        srand(time(0));van x=m*(log(m)/log(2));
        for (int i=1;i<=5e7/x;i++) {
            van wh=randx()%m+1;
            g[uu[wh]][id1[wh]].second.first+=dd[wh];
            g[vv[wh]][id2[wh]].second.first+=dd[wh];
            van res=Dijkstra(1,n);ans=max(ans,res);
            g[uu[wh]][id1[wh]].second.first-=dd[wh];
            g[vv[wh]][id2[wh]].second.first-=dd[wh];
        }print(ans),putchar('\n');return;
    }
}
van mx;
namespace Accepted {
    van dis[2][MaxN];
    bool used[MaxN],access[MaxN],abl[MaxN];
    void Dijkstra(van id,van st) {
        memset(used,0,sizeof used);
        for (int i=1;i<=n;i++) dis[id][i]=1e18;
        priority_queue<pair<van,van> > q;
        q.push(make_pair(0,st));dis[id][st]=0;
        while (!q.empty()) {
            van now=q.top().second;q.pop();
            if (used[now]) continue;used[now]=1;
            for (int i=0;i<(van)g[now].size();i++) {
                van nxt=g[now][i].first,w=g[now][i].second.first;
                if (dis[id][nxt]>dis[id][now]+w) {
                    dis[id][nxt]=dis[id][now]+w;
                    q.push(make_pair(-dis[id][nxt],nxt));
                }
            }
        }
    }
    van u[MaxN*2],v[MaxN*2],w[MaxN*2],d[MaxN*2],id[MaxN*2];
    vector<van> f[MaxN];van cnt=0;
    van low[MaxN],dfn[MaxN],cnt2=0;
    void clear() {
        cnt=0;memset(used,0,sizeof used);
        memset(access,0,sizeof access);
        access[n]=true;memset(abl,0,sizeof abl);
        memset(dfn,0,sizeof dfn);
        memset(low,0,sizeof low);cnt2=0;
        for (int i=1;i<=n;i++) f[i].clear();
        return;
    }
    void tarjan(van now=1,van fa=0) {
        used[now]=1;low[now]=dfn[now]=++cnt2;
        for (int i=0;i<(van)f[now].size();i++) {
            van lid=f[now][i],to=v[lid];
            if (!used[to]) {
                tarjan(to,now),low[now]=min(low[now],low[to]),access[now]|=access[to];
//                cout<<low[to]<<" "<<dfn[now]<<" "<<low[now]<<endl;
                if (access[to]&&low[to]>dfn[now]) abl[id[lid]]=true;
            }
            else if (to!=fa) low[now]=min(low[now],dfn[to]);
        } 
    }
    bool calc(van l) {
        clear();
		for (int i=1;i<=m;i++) {
            if (dis[0][uu[i]]+ww[i]+dis[1][vv[i]]<=l||dis[0][vv[i]]+ww[i]+dis[1][uu[i]]<=l) {
                u[++cnt]=uu[i],v[cnt]=vv[i],w[cnt]=ww[i],d[cnt]=dd[i],id[cnt]=i;
				f[uu[i]].push_back(cnt);
                u[++cnt]=vv[i],v[cnt]=uu[i],w[cnt]=ww[i],d[cnt]=dd[i],id[cnt]=i;
                f[vv[i]].push_back(cnt);
            }
        } tarjan(); 
//        for (int i=1;i<=m;i++) cout<<abl[i]<<endl;
		for (int i=1;i<=m;i++) 
            if (abl[i]&&dis[0][uu[i]]+ww[i]+dd[i]+dis[1][vv[i]]>l
				&&dis[0][vv[i]]+ww[i]+dd[i]+dis[1][uu[i]]>l) return true; 
        return false;
    }
    void main() {
        Dijkstra(0,1);Dijkstra(1,n);
        van l=dis[0][n],r=dis[0][n]+mx,ans=dis[0][n]-1;
        while (l<=r) {
            van mid=(l+r)>>1;
            if (calc(mid)) ans=mid,l=mid+1;
            else r=mid-1;
        }
		cout<<ans+1<<endl;
		return;
    }
}
signed main() {
    freopen("road.in","r",stdin);
    freopen("road.out","w",stdout);
    read(n),read(m);
    for (int i=1;i<=m;i++) {
        van u,v,w,d;read(u),read(v),read(w),read(d);
        g[u].push_back(make_pair(v,make_pair(w,d)));
        g[v].push_back(make_pair(u,make_pair(w,d)));
        uu[i]=u,vv[i]=v,ww[i]=w,dd[i]=d,id1[i]=g[u].size()-1,id2[i]=g[v].size()-1;
        mx=max(mx,d);
    } 
//	if (n<=2000) solve1::main();
//    else if (m==n-1) solve2::main();
    Accepted::main();
    // else if (m==n) solve3::main();
    // else solve4::main();
    return 0;
}
