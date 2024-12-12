#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    ll n; cin>>n;
    vector<vector<pair<ll,ll>>> adj(n);
    function<ll()>prims = [&]() -> ll{
        vector<ll> dist(n, std::numeric_limits<ll>().max());    // same as LLONG_MAX
        ll min_cost=0, added=0;
        set<pair<ll,ll>> q;
        q.emplace(0, 0);
        vector<bool> vis(n);
        while(added<n){
            if(q.empty()){
                return -1;
            }
            auto [curr_cost, v] = *q.begin();
            q.erase(q.begin());
            if(dist[v]<curr_cost) continue;
            added++; vis[v]=true;
            min_cost+=curr_cost;
            for(auto &[next, n_cost]:adj[v]){
                if(!vis[next] && n_cost<dist[next]){
                    dist[next]=n_cost;
                    q.emplace(n_cost, next);
                }
            }
        }
        return min_cost;
    };
}