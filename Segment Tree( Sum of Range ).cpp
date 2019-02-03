#include<bits/stdc++.h>
using namespace std;
#define mx 100005
int ar[mx];
int t[4*mx];

void build(int in, int l, int r)
{
    if(l == r){
        t[in] = ar[l];
    }
    else{
        int m = (l + r)/2;
        build(in*2, l, m);
        build(in*2+1, m+1, r);

        t[in] = t[in*2] + t[in*2+1];
    }
}

int query(int in, int pl, int pr, int l, int r)
{
    if(l > r){return 0;}
    else if(l == pl && r == pr){return t[in];}

    int m = (pl + pr)/2;
    return query(in*2, pl, m, l, min(m,r)) + query(in*2+1, m+1, pr, max(l,m+1), r);
}

void update(int in, int l, int r, int up_in, int val)
{
    if(l==r){t[in] = val;}
    else{
        int m = (l + r)/2;
        if(up_in <= m){ update(in*2, l, m, up_in, val); }
        else{ update(in*2+1, m+1, r, up_in, val);}

        t[in] = t[2*in] + t[2*in+1];
    }
}


int main()
{
    //freopen("inp.txt","r",stdin);
    int n;
    cin >> n;
    for(int i=0; i<n; i++){
        cin >> ar[i];
    }
    build(1,0,n-1);

    int q,l,r,opt,in,val;
    cin >> q;
    while(q--){
        cin >> opt;
        if(opt==1){
            cin >> l >> r;
            int res = query(1,0,n-1,l,r);
            cout << res << endl;
        }
        else{
            cin >> in >> val;
            update(1,0,n-1,in,val);
        }
    }

    return 0;
}
