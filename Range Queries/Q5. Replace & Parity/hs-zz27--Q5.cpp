#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    int t=1;
    cin>>t;
    while(t--){
        int n , q; cin>>n>>q;
        vector<ll> v(n) , pref(n+1);
        for(int i=0;i<n;i++){
            cin>>v[i];
        }
        for(int i=0;i<n;i++){
            pref[i+1] = pref[i]+v[i];
        }   
        while(q--){
            ll l , r , k; cin>>l>>r>>k;
            // sum = (range length)*k + sum(before l) + sum(after r)
            ll s = (r-l+1)*k+pref[l-1]+(pref[n]-pref[r]);
            if(s%2){
                cout<<"YES\n";
            }
            else cout<<"NO\n";
        }
    }
}
