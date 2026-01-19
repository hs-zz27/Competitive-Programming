#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define all(v) v.begin(),v.end()

template<typename Node, typename Update>
struct SegTree {
    vector<Node> tree;
    vector<ll> arr;
    int n;
    int s;

    SegTree(vector<ll> &a) {
        arr=a;
        n=a.size();
        s=1;
        while(s<2*n){
            s=s<<1;
        }
        tree.resize(s);
        fill(tree.begin(),tree.end(),Node());
        build(0,n-1,1);
    }

    void build(int start,int end,int index){
        if(start==end){
            tree[index]=Node(arr[start]);
            return;
        }
        int mid=(start+end)/2;
        build(start,mid,2*index);
        build(mid+1,end,2*index+1);
        tree[index].merge(tree[2*index],tree[2*index+1]);
    }

    void update(int start,int end,int index,int query_index,Update &u){
        if(start==end){
            u.apply(tree[index]);
            return;
        }
        int mid=(start+end)/2;
        if(mid>=query_index)
            update(start,mid,2*index,query_index,u);
        else
            update(mid+1,end,2*index+1,query_index,u);
        tree[index].merge(tree[2*index],tree[2*index+1]);
    }

    Node query(int start,int end,int index,int left,int right){
        if(start>right||end<left)
            return Node();
        if(start>=left&&end<=right)
            return tree[index];
        int mid=(start+end)/2;
        Node l,r,ans;
        l=query(start,mid,2*index,left,right);
        r=query(mid+1,end,2*index+1,left,right);
        ans.merge(l,r);
        return ans;
    }

    void make_update(int index,ll val){
        Update new_update=Update(val);
        update(0,n-1,1,index,new_update);
    }

    Node make_query(int left,int right){
        return query(0,n-1,1,left,right);
    }
};

struct Node1 {
    ll val;
    Node1(){val=0;}
    Node1(ll p1){val=p1;}
    void merge(Node1 &l,Node1 &r){
        val=l.val+r.val;
    }
};

struct Update1 {
    ll val;
    Update1(ll p1){val=p1;}
    void apply(Node1 &a){
        a.val=val;
    }
};

struct Query{
    int l,r,id;
};

int main(){
    int n,q;
    cin>>n>>q;

    vector<ll> b(n);
    for(int i=0;i<n;i++){
        cin>>b[i];
    }

    vector<Query> queries(q);
    for(int i=0;i<q;i++){
        cin>>queries[i].l>>queries[i].r;
        queries[i].l--;
        queries[i].r--;
        queries[i].id=i;
    }
    sort(queries.begin(),queries.end(),[](Query &a,Query &b){return a.r<b.r;});

    vector<ll> temp(n,0);
    SegTree<Node1,Update1> seg(temp);
    unordered_map<ll,int> last;
    vector<ll> ans(q);
    int ptr=0;
    for(int i=0;i<n;i++){
        if(last.count(b[i])){
            seg.make_update(last[b[i]],0);
        }
        seg.make_update(i,1);
        last[b[i]]=i;

        while(ptr<q&&queries[ptr].r==i){
            ans[queries[ptr].id]=seg.make_query(queries[ptr].l,queries[ptr].r).val;
            ptr++;
        }
    }

    for(int i=0;i<q;i++){
        cout<<ans[i]<<"\n";
    }
}
