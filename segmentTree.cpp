// template code

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
