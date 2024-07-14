// template code
#include <bits/stdc++.h>
using namespace std;
#define ll long long

class SGTree{
    // queries of min and updates
    public:
        vector<ll> seg;
        SGTree(ll n){
            seg.resize((4*n)+1);
        }
        void build(ll ind, ll low, ll high, vector<ll> &arr){
            if(low==high){
                seg[ind]=arr[low];
                return;
            }
            ll mid=(low+high)/2;
            ll p1=(2*ind)+1, p2=(2*ind)+2;
            build(p1, low, mid, arr);
            build(p2, mid+1, high, arr);
            seg[ind]=min(seg[p1], seg[p2]);
        }

        ll query(ll ind, ll low, ll high, ll l, ll r){
            // no overlap
            if(r<low || l>high){
                return INT_MAX;
            }
            // complete overlap
            if(low>=l && high<=r){
                return seg[ind];
            }
            // partial overlap
            ll mid=(low+high)>>1;
            ll left=query(2*ind+1, low, mid, l, r);
            ll right=query(2*ind+2, mid+1, high, l, r);
            return min(left, right);
        }

        void update(ll ind, ll low, ll high, ll i, ll val){
            if(low==high){
                seg[ind]=val;
                return;
            }
            ll mid=(low+high)>>1;
            if(i<=mid){
                update(2*ind+1, low, mid, i, val);
            }
            else{
                update(2*ind+2, mid+1, high, i, val);
            }
            seg[ind]=min(seg[(ind*2)+1], seg[(ind*2)+2]);
        }
};

void solve(){
    ll n; cin>>n;
    vector<ll> arr(n);
    for(ll i=0; i<n; i++) cin>>arr[i];
    SGTree sg(n);
    sg.build(0,0,n-1,arr);
    ll q; cin>>q;
    while(q--){
        ll type,l,r; cin>>type>>l>>r;  
        // type --> 1     update
        // type --> 2     query from [l,r]
        if(type==1){
            l--;
            sg.update(0, 0, n-1, l, r);
        }
        else{
            l--, r--;
            cout<<sg.query(0, 0, n-1, l, r)<<endl;
        }
    }
}

signed main(){
    solve();
}