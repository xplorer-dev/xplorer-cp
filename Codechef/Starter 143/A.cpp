#include <bits/stdc++.h>
#include <iostream>
#include <set>
#include <map>
using namespace std;

#define ll long long
#define ld long double
const unsigned int M = 998244353;
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vld = vector<ld>;
using vvld = vector<vld>;
using vvl = vector<vl>;
#define pb push_back
long long inf = 1e9 + 7;

const int MOD = 1000000007;
string yes = "YES";
string no = "NO";

// dsu class /////
class DSU
{
public:
    vl rank, par;

public:
    DSU(ll n)
    {
        rank.resize(n, 1);
        par.resize(n, 0);
        for (int i = 0; i < n; i++)
        {
            par[i] = i;
            rank[i] = 1;
        }
    }
    ll getpar(ll a)
    {
        if (par[a] == a)
            return a;
        return par[a] = getpar(par[a]);
    }
    void merge(ll a, ll b)
    {
        a = getpar(a);
        b = getpar(b);
        if (a == b)
            return;
        if (rank[a] < rank[b])
            swap(a, b);
        rank[a] += rank[b];
        par[b] = a;
    }
    ll getsize(ll a)
    {
        a = getpar(a);
        return rank[a];
    }
    bool checkpar(ll a, ll b)
    {
        a = getpar(a);
        b = getpar(b);
        if (a != b)
            return 1;
        return 0;
    }
};

// lca class /////

const ll maxnum = 3e5 + 1,
         lg = 19;
ll lanc[maxnum][19], depth[maxnum];
vector<ll> adj[maxnum];
void dfs(ll node, ll par)
{
    for (int i = 1; i < lg; i++)
    {
        lanc[node][i] = lanc[lanc[node][i - 1]][i - 1];
    }
    for (auto child : adj[node])
    {
        if (child != par)
        {
            lanc[child][0] = node;
            depth[child] = depth[node] + 1;
            dfs(child, node);
        }
    }
}
ll lca(ll a, ll b)
{
    if (depth[a] < depth[b])
        swap(a, b);

    for (int i = lg - 1; i >= 0; i--)
    {
        if (depth[a] - (1 << i) >= depth[b])
        {
            a = lanc[a][i];
        }
    }
    if (a == b)
    {
        return b;
    }
    for (int i = lg - 1; i >= 0; i--)
    {
        if (lanc[a][i] != lanc[b][i])
        {
            a = lanc[a][i];
            b = lanc[b][i];
        }
    }
    return lanc[a][0];
}

// segmented tree class /////
class SegmentTree
{
private:
    vl seg;
    vl lazy;

public:
    SegmentTree(ll n)
    {
        seg.resize(4 * n + 1);
        lazy.resize(4 * n + 1);
    }
    void build(ll idx, ll low, ll high, vl &arr)
    {
        if (low == high)
        {
            seg[idx] = arr[low];
            return;
        }
        ll mid = (low + high) >> 1;
        build(2 * idx + 1, low, mid, arr);
        build(2 * idx + 2, mid + 1, high, arr);
        seg[idx] = min(seg[2 * idx + 1], seg[2 * idx + 2]);
    }
    void print()
    {
        for (auto x : seg)
        {
            cout << x << " ";
        }
    }

    ll query(ll idx, ll low, ll high, ll l, ll r, vl &arr)
    {
        // no overlap;
        if (r < low || high < l)
        {
            return INT_MAX;
        }
        // complete overlap;
        if (low >= l && high <= r)
        {
            return seg[idx];
        }
        // partial overlap;
        ll mid = (low + high) >> 1;
        ll lmin = query(2 * idx + 1, low, mid, l, r, arr);
        ll rmin = query(2 * idx + 2, mid + 1, high, l, r, arr);
        return min(lmin, rmin);
    }

    void update(ll idx, ll low, ll high, ll i, ll val, vl &arr)
    {

        if (low == high)
        {
            seg[idx] = val;
            return;
        }
        ll mid = (low + high) >> 1;
        if (i <= mid)
        {
            update(2 * idx + 1, low, mid, i, val, arr);
        }
        else
        {
            update(2 * idx + 2, mid + 1, high, i, val, arr);
        }
        seg[idx] = min(seg[2 * idx + 1], seg[2 * idx + 2]);
    }
};

long long binpow(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}


vl arr(1e5 + 5, 0);
vl prim;
void sieve()
{
    for (int i = 2; i <= 1e5; i++)
    {
        if (arr[i] == 0)
        {
            prim.pb(i);
            for (int j = 2 * i; j <= 1e5; j += i)
            {
                arr[j] = 1;
            }
        }
    }
}

void solve()
{
    ll n,m;
    cin>>n>>m;
    ll rem = n-m;
    ll sum = 0,val =1;
    while(rem > 0){
        val=val*2;
         sum-=val;
         rem--;
    }
    while(m>0){
        val=val*2;
        sum+=val;
        m--;
    }
    cout<<sum<<endl;
}

int main()
{
#ifndef ONLINE_JUDGE

    // For getting input from input.txt file
    freopen("input.txt", "r", stdin);
    // Printing the Output to output.txt filex
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
}