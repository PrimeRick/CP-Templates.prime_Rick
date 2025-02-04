#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    ll n; cin>>n;
    vector<ll> a(n);     // vector of values of nodes
    vector<vector<ll>> adj(n);
    vector<ll> parents(n+1);
    vector<bool> vis(n+1, false);
    vector<ll> level(n+1);
    queue<ll> qq;
    qq.emplace(1);
    vis[1]=true;
    while(!qq.empty()){
        ll curr=qq.front();
        qq.pop();
        for(auto child:adj[curr]){
            if(vis[child]) continue;
            parents[child]=curr;
            vis[child]=true;
            qq.emplace(child);
            level[child]=level[curr]+1;
        }
    }
    ll LOG=ceil(log2(n));
    vector<vector<ll>>  ancestor(n+1, vector<ll>(LOG+1));
    vector<vector<ll>> mx(n+1, vector<ll>(LOG+1));
    vector<vector<ll>> mn(n+1, vector<ll>(LOG+1, 1e15));
    for(ll i=2; i<=n; i++){
        ancestor[i][0]=parents[i];
        mx[i][0]=max(a[i], a[parents[i]]);
        mn[i][0]=min(a[i], a[parents[i]]);
    }
    // ancestor[u][k] -> 2^k-th ancestor of node u
    for(ll k=1; k<=LOG; k++){
        for(ll u=1; u<=n; u++){
            ll midAncestor=ancestor[u][k-1];
            if(!midAncestor) ancestor[u][k]=0;
            else{
                ll kth_ancestor=ancestor[midAncestor][k-1];
                ancestor[u][k]=kth_ancestor;
                mx[u][k]=max(mx[u][k-1], mx[midAncestor][k-1]);
                mn[u][k]=min(mn[u][k-1], mn[midAncestor][k-1]);
            }
        }
    }
    auto lift = [&](ll u, ll k, auto &&lift) -> ll{
        for(ll j=LOG; j>=0; j--){
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
    vector<ll> sum_from_root(n+1);
    ll total_sum=accumulate(a.begin(), a.end(), 0LL);
    fill(vis.begin(), vis.end(), false);
    auto dfs = [&](ll vertex, auto &&dfs) -> void{
        vis[vertex]=true;
        for(auto child:adj[vertex]){
            if(vis[child]) continue;
            sum_from_root[child]=sum_from_root[vertex]+a[child];
            dfs(child, dfs);
        }
    };
    sum_from_root[1]=a[1];
    dfs(1, dfs);
    auto sum_path = [&](ll u, ll v) -> ll{
        return sum_from_root[u]+sum_from_root[v]-(2*sum_from_root[lca(u, v, lca)])+a[lca(u, v, lca)];
    };
    // max value in a path
    auto get_max = [&](ll u, ll k) -> ll{
        ll mxx=0;
        for(ll j=LOG; j>=0; j--){
            if((1ll<<j)&k){
                mxx=max(mxx, mx[u][j]);
                u=ancestor[u][j];
            }
        }
        return mxx;
    };
    auto max_path = [&](ll u, ll v) -> ll{
        ll LCA=lca(u,v,lca);
        return max({get_max(u, level[u]-level[LCA]), get_max(v, level[v]-level[LCA]), a[LCA]});
    };
    // min value in a path
    auto get_min = [&](ll u, ll k) -> ll{
        ll mnn=1e18;
        for(ll j=LOG; j>=0; j--){
            if((1ll<<j)&k){
                mnn=min(mnn, mn[u][j]);
                u=ancestor[u][j];
            }
        }
        return mnn;
    };
    auto min_path = [&](ll u, ll v) -> ll{
        ll LCA=lca(u,v,lca);
        return min({get_min(u, level[u]-level[LCA]), get_min(v, level[v]-level[LCA]), a[LCA]});
    };
    ll q; cin>>q;
    while(q--){

    }
}