#include <bits/stdc++.h>
using namespace std;

class DisjointSet{
    public:
        vector<int> rank, parent, size;
        DisjointSet(int n){
            rank.resize(n+1, 0);
            parent.resize(n+1);
            size.resize(n+1);
            for(int i=0; i<=n; i++){
                parent[i]=i;
                size[i]=1;
            }
        }
        int findUPar(int node){
            if(node==parent[node]){
                return node;
            } 
            return parent[node]=findUPar(parent[node]);
        }
        void unionByRank(int u, int v){
            int ultp_u=findUPar(u);
            int ultp_v=findUPar(v);
            if(ultp_u==ultp_v) return;
            if(rank[ultp_u]<rank[ultp_v]){
                parent[ultp_u]=ultp_v;
            }
            else if(rank[ultp_u]>rank[ultp_v]){
                parent[ultp_v]=ultp_u;
            }
            else{
                parent[ultp_v]=ultp_u;
                rank[ultp_u]++;
            }
        }
        void unionBySize(int u, int v){
            int ultp_u=findUPar(u);
            int ultp_v=findUPar(v);
            if(ultp_u==ultp_v) return;
            if(size[ultp_u]<size[ultp_v]){
                parent[ultp_u]=ultp_v;
                size[ultp_v]+=size[ultp_u];
            }
            else{
                parent[ultp_v]=ultp_u;
                size[ultp_u]+=size[ultp_v];
            }
        }
};
