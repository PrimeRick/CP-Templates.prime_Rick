#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    ll n; cin>>n;
    vector<vector<ll>> adj(n);
    vector<ll> parents(n+1);
    vector<bool> vis(n+1, false);
    vector<ll> level(n+1);
    function<void(ll)>dfs = [&](ll vertex) -> void{
        vis[vertex]=true;
        for(auto child:adj[vertex]){
            if(vis[child]) continue;
            level[child]=level[vertex]+1;
            dfs(child);
        }
    };
    dfs(1);
    ll LOG=ceil(log2(n));
    vector<vector<ll>>  ancestor(n+1, vector<ll>(LOG+1));
    for(ll i=2; i<=n; i++){
        ancestor[i][0]=parents[i];
    }
    // ancestor[u][k] -> 2^k-th ancestor of node u
    for(ll k=1; k<=LOG; k++){
        for(ll u=1; u<=n; u++){
            ll midAncestor=ancestor[u][k-1];
            ll kth_ancestor=ancestor[midAncestor][k-1];
            ancestor[u][k]=kth_ancestor;
        }
    }
    auto lift = [&](ll u, ll k, auto &&lift) -> ll{
        for(ll j=LOG+1; j>=0; j--){
            if((1ll<<j)&k){
                u=ancestor[u][j];
            }
        }
        return u;
    };
    auto lca = [&](ll u, ll v, auto &&lca) -> ll{
        if(level[u]<level[v]) swap(u,v);
        // lift node u to the same level as v
        if(level[u]>level[v]) v=lift(v, level[u]-level[v], lift);
        if(u==v) return u;
        // lift both u and v until their parents match
        for(int j=LOG; j>=0; j--){
            if(ancestor[u][j]!=ancestor[v][j]){
                u=ancestor[u][j];
                v=ancestor[v][j];
            }
        }
        return ancestor[u][0];
    };
    ll q; cin>>q;
    while(q--){

    }
}