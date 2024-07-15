// template code

class SGTree{
    // queries of sum in a range and range update
    public:
        vector<ll> seg, lazy;
        SGTree(ll n){
            seg.resize((4*n)+1);
            lazy.resize((4*n)+1);
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
            seg[ind]=seg[p1]+seg[p2];
        }

        void update(ll ind, ll low, ll high, ll l, ll r, ll val) {
            // update the previous remaining updates 
            // and propogate downwards 
            if(lazy[ind] != 0) {
                seg[ind] += (high - low + 1) * lazy[ind]; 
                // propogate the lazy update downwards
                // for the remaining nodes to get updated 
                if(low != high) {
                    lazy[2*ind+1] += lazy[ind]; 
                    lazy[2*ind+2] += lazy[ind]; 
                }
                lazy[ind] = 0; 
            }
            // no overlap 
            // we don't do anything and return 
            // low high l r or l r low high 
            if(high < l or r < low) {
                return; 
            }
            // complete overlap 
            // l low high r 
            if(low>=l && high <= r) {
                seg[ind] += (high - low + 1) * val; 
                // if a leaf node, it will have childrens
                if(low != high) {
                    lazy[2*ind+1] += val; 
                    lazy[2*ind+2] += val; 
                }
                return; 
            }
            // last case has to be no overlap case
            ll mid = (low + high) >> 1; 
            update(2*ind+1, low, mid, l, r, val);
            update(2*ind+2, mid+1, high, l, r, val); 
            seg[ind] = seg[2*ind+1] + seg[2*ind+2]; 
        }

        ll query(ll ind, ll low, ll high, ll l, ll r) {
            // update if any updates are remaining 
            // as the node will stay fresh and updated 
            if(lazy[ind] != 0) {
                seg[ind] += (high - low + 1) * lazy[ind]; 
                // propogate the lazy update downwards
                // for the remaining nodes to get updated 
                if(low != high) {
                    lazy[2*ind+1] += lazy[ind]; 
                    lazy[2*ind+2] += lazy[ind]; 
                }
                lazy[ind] = 0; 
            }
            // no overlap return 0; 
            if(high < l or r < low) {
                return 0; 
            }
            // complete overlap 
            if(low>=l && high <= r) return seg[ind]; 
    
            ll mid = (low + high) >> 1; 
            ll left = query(2*ind+1, low, mid, l, r);
            ll right = query(2*ind+2, mid+1, high, l, r);
            return left + right; 
        }
};
