#include <bits/stdc++.h>
using namespace std;
#define ll long long

class UnionFind{
    private: vector<ll> p, rank;
    public:
        UnionFind(ll n){
            rank.assign(n, 0); p.assign(n, 0);
            iota(p.begin(), p.end(), 0);
        }

        ll findSet(ll i){ return (p[i]==i)? i : p[i]=findSet(p[i]); }
        bool isSameSet(ll i, ll j){ return findSet(i)==findSet(j); }

        void unionSet(ll i, ll j){
            if(!isSameSet(i, j)){
                ll x=findSet(i), y=findSet(j);
                if(rank[x]>rank[y]){
                    p[y]=x;
                }
                else{
                    p[x]=y;
                    if(rank[x]==rank[y]) rank[y]++;
                }
            }
        }
};