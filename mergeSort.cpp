#include <bits/stdc++.h>
using namespace std;

// merge sort

void merge(vector<int> &arr, int low, int mid, int high){
    vector<int> temp;
    int left=low;       // low...mid
    int right=mid+1;    // mid+1..high
    while(left<=mid && right<=high){
        if(arr[left]>arr[right]){
            temp.emplace_back(arr[right]);
            right++;
        }
        else{
            temp.emplace_back(arr[left]);
            left++;
        }
    }
    while(right<=high){
        temp.emplace_back(arr[right]);
        right++;
    }
    while(left<=mid){
        temp.emplace_back(arr[left]);
        left++;
    }
    for(int i=low; i<=high; i++){
        arr[i]=temp[i-low];
    }
}

void mergeSort(vector<int> &arr, int low, int high){
    if(low>=high) return;
    int mid=(high+low)/2;
    mergeSort(arr, low, mid);
    mergeSort(arr, mid+1, high);
    merge(arr, low, mid, high);
}

void solve(){
    int n; cin>>n;
    vector<int> v(n);
    for(int i=0; i<n; i++) cin>>v[i];
    mergeSort(v, 0, n-1);
    cout<<"sorted array using merge sort --->"<<endl;
    for(auto j:v) cout<<j<<" ";
    cout<<endl;
}
int main(){
    solve();
}