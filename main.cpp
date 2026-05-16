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

struct bitnhiphan{
    int gia_tri;

    bitnhiphan(int x = 0){
        gia_tri = x & 1;
    }

    bitnhiphan operator+(const bitnhiphan &khac) const{
        return bitnhiphan(gia_tri ^ khac.gia_tri);
    }

    bitnhiphan operator*(const bitnhiphan &khac) const{
        return bitnhiphan(gia_tri & khac.gia_tri);
    }
};

struct vectonhiphan{
    vector<bitnhiphan> a;

    vectonhiphan(){}

    vectonhiphan(int n){
        a.assign(n, bitnhiphan(0));
    }

    int kich_thuoc() const{
        return (int)a.size();
    }

    int trong_so() const{
        int tong = 0;
        for(auto x : a) tong += x.gia_tri;
        return tong;
    }

    string dang_chuoi() const{
        string s;
        for(int i = kich_thuoc() - 1; i >= 0; i--){
            s += char('0' + a[i].gia_tri);
        }
        if(s.empty()) s = "0";
        return s;
    }
};

struct dathuc{
    vector<int> he_so;

    dathuc(){
        he_so = {0};
    }

    dathuc(vector<int> v){
        he_so = v;
        chuan_hoa();
    }

    void chuan_hoa(){
        while(he_so.size() > 1 && he_so.back() == 0){
            he_so.pop_back();
        }
        if(he_so.empty()) he_so.pb(0);
    }

    bool la_khong() const{
        return he_so.size() == 1 && he_so[0] == 0;
    }

    int bac() const{
        if(la_khong()) return -1;
        return (int)he_so.size() - 1;
    }

    int lay_he_so(int i) const{
        if(i < 0 || i >= (int)he_so.size()) return 0;
        return he_so[i];
    }

    int trong_so() const{
        int tong = 0;
        for(int x : he_so) tong += x;
        return tong;
    }

    static dathuc tu_chuoi_nhi_phan(string s){
        vector<int> v;
        for(int i = (int)s.size() - 1; i >= 0; i--){
            if(s[i] == '0' || s[i] == '1'){
                v.pb(s[i] - '0');
            }
        }
        if(v.empty()) v.pb(0);
        return dathuc(v);
    }

    static dathuc tu_mat_na(unsigned long long mat_na, int k){
        vector<int> v(max(1, k), 0);
        for(int i = 0; i < k; i++){
            v[i] = (mat_na >> i) & 1;
        }
        return dathuc(v);
    }

    static dathuc x_mu_n_cong_1(int n){
        vector<int> v(n + 1, 0);
        v[0] = 1;
        v[n] = 1;
        return dathuc(v);
    }

    string dang_nhi_phan(int do_dai = -1) const{
        int d = bac();
        if(do_dai != -1) d = do_dai - 1;
        if(d < 0) return "0";

        string s;
        for(int i = d; i >= 0; i--){
            s += char('0' + lay_he_so(i));
        }
        return s;
    }

    string dang_da_thuc() const{
        if(la_khong()) return "0";

        string s;
        for(int i = bac(); i >= 0; i--){
            if(!lay_he_so(i)) continue;

            if(!s.empty()) s += "+";

            if(i == 0) s += "1";
            else if(i == 1) s += "x";
            else s += "x^" + to_string(i);
        }

        return s;
    }
};

dathuc operator+(dathuc a, dathuc b){
    int n = max(a.he_so.size(), b.he_so.size());
    vector<int> v(n, 0);

    for(int i = 0; i < n; i++){
        v[i] = a.lay_he_so(i) ^ b.lay_he_so(i);
    }

    return dathuc(v);
}

dathuc operator*(dathuc a, dathuc b){
    if(a.la_khong() || b.la_khong()) return dathuc();

    vector<int> v(a.bac() + b.bac() + 1, 0);

    for(int i = 0; i <= a.bac(); i++){
        if(!a.lay_he_so(i)) continue;

        for(int j = 0; j <= b.bac(); j++){
            if(b.lay_he_so(j)){
                v[i + j] ^= 1;
            }
        }
    }

    return dathuc(v);
}

pair<dathuc, dathuc> chia_lay_du(dathuc f, dathuc g){
    if(g.la_khong()) return {dathuc(), f};

    vector<int> thuong(max(1, f.bac() - g.bac() + 1), 0);
    dathuc du = f;

    while(!du.la_khong() && du.bac() >= g.bac()){
        int dich = du.bac() - g.bac();
        thuong[dich] ^= 1;

        if((int)du.he_so.size() < dich + (int)g.he_so.size()){
            du.he_so.resize(dich + g.he_so.size(), 0);
        }

        for(int i = 0; i < (int)g.he_so.size(); i++){
            du.he_so[i + dich] ^= g.he_so[i];
        }

        du.chuan_hoa();
    }

    return {dathuc(thuong), du};
}

string tu_ma(dathuc p, int n){
    return p.dang_nhi_phan(n);
}

int main(){
    boost;

    int n, k;
    string chuoi_h;

    if(!(cin >> n >> k)) return 0;
    cin >> chuoi_h;

    dathuc h = dathuc::tu_chuoi_nhi_phan(chuoi_h);
    dathuc x_n_cong_1 = dathuc::x_mu_n_cong_1(n);

    auto ket_qua_chia = chia_lay_du(x_n_cong_1, h);
    dathuc g = ket_qua_chia.fi;
    dathuc du = ket_qua_chia.se;

    cout << "do_dai_ma = " << n << el;
    cout << "so_bit_thong_tin = " << k << el;
    cout << "h(x) = " << h.dang_da_thuc() << el;

    if(!du.la_khong()){
        cout << "khong_hop_le" << el;
        cout << "ly_do = h(x) khong chia het x^n + 1" << el;
        return 0;
    }

    cout << "g(x) = " << g.dang_da_thuc() << el;

    if(h.bac() != k){
        cout << "canh_bao = bac cua h(x) khac k" << el;
    }

    if(g.bac() != n - k){
        cout << "canh_bao = bac cua g(x) khac n - k" << el;
    }

    if(k < 0 || k >= 63){
        cout << "khong_hop_le" << el;
        cout << "ly_do = k qua lon" << el;
        return 0;
    }

    if(k > 25){
        cout << "khong_hop_le" << el;
        cout << "ly_do = k qua lon cho cach duyet toan bo tu ma" << el;
        return 0;
    }

    int khoang_cach_nho_nhat = inf;
    dathuc tu_ma_nho_nhat;

    unsigned long long gioi_han = 1ULL << k;

    for(unsigned long long mat_na = 1; mat_na < gioi_han; mat_na++){
        dathuc thong_diep = dathuc::tu_mat_na(mat_na, k);
        dathuc ma = thong_diep * g;

        int w = ma.trong_so();

        if(w < khoang_cach_nho_nhat){
            khoang_cach_nho_nhat = w;
            tu_ma_nho_nhat = ma;
        }
    }

    cout << "khoang_cach_ma_toi_thieu = " << khoang_cach_nho_nhat << el;
    cout << "so_loi_phat_hien_duoc = " << khoang_cach_nho_nhat - 1 << el;
    cout << "so_loi_sua_duoc = " << (khoang_cach_nho_nhat - 1) / 2 << el;
    cout << "tu_ma_co_trong_so_nho_nhat = " << tu_ma(tu_ma_nho_nhat, n) << el;

    return 0;
}
