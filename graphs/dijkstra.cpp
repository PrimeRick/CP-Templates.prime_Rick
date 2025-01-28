#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define INF 1e18

// time complexity -> O(E*log(V))
int main(){
    ll n,m; cin>>n>>m;
    vector<vector<pair<ll,ll>>> adj(n+7);
    for(ll i=0; i<m; i++){
        ll u,v,wt; cin>>u>>v>>wt;
        adj[u].emplace_back(v, wt);   // directed graph
    }
    vector<ll> dist(n, INF);
    vector<bool> vis(n);
    auto dijkstra = [&](ll source, auto &&dijkstra) -> void{
        set<pair<ll,ll>> st;
        st.emplace(0, source);
        while(!st.empty()){
            auto [curr_wt, curr]=*st.begin();
            st.erase(st.begin());
            if(vis[curr]) continue;
            vis[curr]=true;
            for(auto [child, wt]:adj[curr]){
                if(dist[child]>(wt+curr_wt)){
                    dist[child]=wt+curr_wt;
                    st.emplace(dist[child], child);
                }
            }
        }
    };
    dijkstra(0, dijkstra); 
}