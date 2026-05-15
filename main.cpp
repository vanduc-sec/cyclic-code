#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define el '\n'
#define fi first
#define se second
#define pb push_back
#define all(a) a.begin(), a.end()
#define boost                     \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0);

const int mod = 1e9 + 7;
const int inf = 1e9;
const ll linf = 4e18;

struct bit{
    int v;
    bit(int x = 0){
        v = x & 1;
    }
    bit operator+(const bit &o) const{
        return bit(v ^ o.v);
    }
    bit operator*(const bit &o) const{
        return bit(v & o.v);
    }
};

struct binvec{
    vector<bit> a;
    binvec(){}
    binvec(int n){
        a.assign(n, bit(0));
    }
    int size() const{
        return (int)a.size();
    }
    int weight() const{
        int s = 0;
        for(auto x : a) s += x.v;
        return s;
    }
    string str() const{
        string s;
        for(int i = size() - 1; i >= 0; i--) s += char('0' + a[i].v);
        if(s.empty()) s = "0";
        return s;
    }
};

struct poly{
    vector<int> a;

    poly(){
        a = {0};
    }

    poly(vector<int> v){
        a = v;
        norm();
    }

    void norm(){
        while(a.size() > 1 && a.back() == 0) a.pop_back();
        if(a.empty()) a.pb(0);
    }

    bool zero() const{
        return a.size() == 1 && a[0] == 0;
    }

    int deg() const{
        if(zero()) return -1;
        return (int)a.size() - 1;
    }

    int coef(int i) const{
        if(i < 0 || i >= (int)a.size()) return 0;
        return a[i];
    }

    int weight() const{
        int s = 0;
        for(int x : a) s += x;
        return s;
    }

    static poly frombin(string s){
        vector<int> v;
        for(int i = (int)s.size() - 1; i >= 0; i--){
            if(s[i] == '0' || s[i] == '1') v.pb(s[i] - '0');
        }
        if(v.empty()) v.pb(0);
        return poly(v);
    }

    static poly frommask(unsigned long long m, int k){
        vector<int> v(max(1, k), 0);
        for(int i = 0; i < k; i++) v[i] = (m >> i) & 1;
        return poly(v);
    }

    static poly xn1(int n){
        vector<int> v(n + 1, 0);
        v[0] = 1;
        v[n] = 1;
        return poly(v);
    }

    string bin(int len = -1) const{
        int d = deg();
        if(len != -1) d = len - 1;
        if(d < 0) return "0";
        string s;
        for(int i = d; i >= 0; i--) s += char('0' + coef(i));
        return s;
    }

    string str() const{
        if(zero()) return "0";
        string s;
        for(int i = deg(); i >= 0; i--){
            if(!coef(i)) continue;
            if(!s.empty()) s += "+";
            if(i == 0) s += "1";
            else if(i == 1) s += "x";
            else s += "x^" + to_string(i);
        }
        return s;
    }
};

poly operator+(poly x, poly y){
    int n = max(x.a.size(), y.a.size());
    vector<int> v(n, 0);
    for(int i = 0; i < n; i++) v[i] = x.coef(i) ^ y.coef(i);
    return poly(v);
}

poly operator*(poly x, poly y){
    if(x.zero() || y.zero()) return poly();
    vector<int> v(x.deg() + y.deg() + 1, 0);
    for(int i = 0; i <= x.deg(); i++){
        if(!x.coef(i)) continue;
        for(int j = 0; j <= y.deg(); j++){
            if(y.coef(j)) v[i + j] ^= 1;
        }
    }
    return poly(v);
}

pair<poly, poly> divmod(poly f, poly g){
    if(g.zero()) return {poly(), f};
    vector<int> q(max(1, f.deg() - g.deg() + 1), 0);
    poly r = f;
    while(!r.zero() && r.deg() >= g.deg()){
        int sh = r.deg() - g.deg();
        q[sh] ^= 1;
        if((int)r.a.size() < sh + (int)g.a.size()) r.a.resize(sh + g.a.size(), 0);
        for(int i = 0; i < (int)g.a.size(); i++) r.a[i + sh] ^= g.a[i];
        r.norm();
    }
    return {poly(q), r};
}

string word(poly p, int n){
    return p.bin(n);
}

int main(){
    boost;

    int n, k;
    string hs;
    if(!(cin >> n >> k)) return 0;
    cin >> hs;

    poly h = poly::frombin(hs);
    poly xn = poly::xn1(n);
    auto qr = divmod(xn, h);
    poly g = qr.fi;
    poly rem = qr.se;

    cout << "n = " << n << el;
    cout << "k = " << k << el;
    cout << "h(x) = " << h.str() << el;

    if(!rem.zero()){
        cout << "invalid" << el;
        cout << "reason = h(x) does not divide x^n + 1" << el;
        return 0;
    }

    cout << "g(x) = " << g.str() << el;

    if(h.deg() != k){
        cout << "warning = deg(h) != k" << el;
    }
    if(g.deg() != n - k){
        cout << "warning = deg(g) != n - k" << el;
    }

    if(k < 0 || k >= 63){
        cout << "invalid" << el;
        cout << "reason = k is too large for exhaustive search" << el;
        return 0;
    }

    if(k > 25){
        cout << "invalid" << el;
        cout << "reason = k is too large for this exhaustive implementation" << el;
        return 0;
    }

    int dmin = inf;
    poly best;
    unsigned long long lim = 1ULL << k;

    for(unsigned long long mask = 1; mask < lim; mask++){
        poly m = poly::frommask(mask, k);
        poly c = m * g;
        int w = c.weight();
        if(w < dmin){
            dmin = w;
            best = c;
        }
    }

    cout << "d_min = " << dmin << el;
    cout << "detectable_errors = " << dmin - 1 << el;
    cout << "correctable_errors = " << (dmin - 1) / 2 << el;
    cout << "minimum_codeword = " << word(best, n) << el;

    return 0;
}
