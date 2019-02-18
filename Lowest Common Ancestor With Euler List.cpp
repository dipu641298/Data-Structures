#include<bits/stdc++.h>
using namespace std;
#define mxn 10005
#define pii pair<int, int>
vector<int> adj[mxn];
vector<pii> euler;
int first[mxn];
bool visited[mxn];

pii t[4*mxn];

void dfs(int s, int h)
{
    first[s] = euler.size();
    visited[s] = true;
    pii x;
    x.first = s;
    x.second = h;
    euler.push_back(x);
    for(int i=0; i<adj[s].size(); i++){
        if(!visited[adj[s][i]]){
            dfs(adj[s][i], h+1);
            x.first = s;
            x.second = h;
            euler.push_back(x);
        }
    }
}


void build(int in, int l, int r)
{
    if(l == r){
        t[in].first = euler[l].first;
        t[in].second = euler[l].second;
    }
    else{
        int m = (l + r)/2;
        build(in*2, l, m);
        build(in*2+1, m+1, r);

        if(t[in*2].second < t[in*2+1].second){t[in] = t[in*2];}
        else{t[in] = t[in*2+1];}
    }
}

pii query(int in, int pl, int pr, int l, int r)
{
    if(l > r){return make_pair(-1,-1);}
    else if(l == pl && r == pr){return t[in];}
    //cout << l << " " << r << endl;
    int m = (pl + pr)/2;
    pii left = query(in*2, pl, m, l, min(m,r));
    pii right = query(in*2+1, m+1, pr, max(l,m+1), r);

    if(left.first == -1){return right;}
    if(right.first == -1){return left;}

    if(left.second < right.second){return left;}
    else{return right;}
}

int main()
{
    //freopen("inp.txt","r",stdin);
    int n;
    cin >> n ;
    int u,v;
    for(int i=0; i<n-1; i++){
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    memset(visited,false,sizeof visited);

    dfs(1,0);
    build(1,0,euler.size()-1);

    for(int i=0; i<euler.size(); i++){
        cout << euler[i].first << " " ;   /// Euler List
    }
    cout << endl;
    for(int i=0; i<euler.size(); i++){
        cout << euler[i].second << " " ;  /// Height of each node in Euler List
    }
    cout << endl;
    for(int i=1; i<=n; i++){
        cout << first[i] << " ";            /// List of first appearance of any node in euler list
    }
    cout << endl;

    int q;
    cin >> q;
    for(int i=0; i<q; i++){
        cin >> u >> v;
        int x = min(first[u],first[v]);
        int y = max(first[u],first[v]);
        cout << x << " " << y << endl;
        pii res = query(1,0,euler.size()-1,x,y);
        cout <<u << " " << v << " " << res.first << endl;
    }

    return 0;
}


/* Sample Input :
13
1 2
1 3
2 4
2 5
4 6
4 7
4 8
3 9
9 10
9 11
10 12
10 13
6
13 3
4 11
6 8
4 9
5 1
11 12
*/
