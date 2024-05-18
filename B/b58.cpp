/*
https://atcoder.jp/contests/abc305/tasks/abc305_a
*/

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <set>
#include <tuple>
#include <map>
#include <math.h>
#include <string>
#include <cstdlib>
#include <iomanip> //出力桁数
#include <queue> // queue
#include <stack> // stack
#include <deque> // deque
#include <sstream> //基数変換
#include <bitset> //2進数に変換
#include <iterator> // set intersection
#include <numeric> // accumulate


using namespace std;

#define pi 3.14159265358979323846
#define yes "Yes"
#define no "No"
#define yesno(bool) if(bool){cout<<"Yes"<<endl;}else{cout<<"No"<<endl;}
#define alphabet "abcdefghijklmnopqrstuvwxyz"
#define Alpahbet "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define repp(i, l, r) for (int i = l; i < r; ++i)
#define rrep(i, r, l) for (int i = r; i >= l; --i)
#define tp() cout << "here~~" << endl
#define el '\n'
#define int long long


// int imax = 2147483647;
// int imin = -2147483648;
// unsigned int uimax = 4294967296LL;
// long long llmax = 9223372036854775807LL;
// long long llmin = -9223372036854775808LL;
// unsigned long long ullmax = 18446744073709551616uLL;



const int dx[4] = {1, 0, -1, 0};//グリッド上の探索
const int dy[4] = {0, 1, 0, -1};//上下左右移動方向
const int dxdi[4] = {1, 1, -1, -1};//グリッド上の探索
const int dydi[4] = {1, -1, 1, -1};//斜め移動方向


//型エイリアス vector<set<pair<tuple : bool<char<string<int<ll<ull
using vb = vector<bool>;
using vc = vector<char>;
using vs = vector<string>;
using vi = vector<int>;
using si = set<int>;
using msi = multiset<int>;
using mss = multiset<string>;
using pii = pair<int, int>;
using vvb = vector<vector<bool>>;
using vvc = vector<vector<char>>;
using vvs = vector<vector<string>>;
using vvi = vector<vector<int>>;
using vsi = vector<set<int>>;
using vpii = vector<pair<int, int>>;
using spii = set<pair<int, int>>;

using stst = stringstream;

// [ノード][(接続ノード, 重み)]
using Graph = vector<vector<int>>;//重みなしグラフ構造
using GraphWeight = vector<vector<pair<int,int>>>;//重みありグラフ構造
using GraphCh = vector<vector<char>>;//charGridの探索
using GraphIn = vector<vector<int>>;//charGridの探索
using GridPos = pair<int, int>;//グリッド上の位置・座標

//関数定義群
vector<pair<int, int> > prime_factorize(int); //素因数分解
bool contain_string(string, string); //部分文字列の一致判定
int gcd(int, int); //最大公約数
int lcm(int, int); //最小公倍数
int powll(int, int); //llの累乗
bool in_table(int, int); //添え字が１次元配列内か判定
bool in_table(int, int, int, int); //添え字が２次元配列内か判定
int modPow(int, int, int);
int modInv(int, int);
bool isPrime(int);


void put_vvc(bool bl, GraphCh &g) {
    if (!bl) return ;
    int h = g.size(), w = g[0].size();
    rep(i, h) {
        rep(j, w) {
            cout << g[i][j];
        }
        cout << el;
    }
}

void put_vvi(bool bl, vvi &need) {
    if (!bl) return ;
    rep(i, 10) cout << "=";
    cout << el;
    int h = need.size(), w = need[0].size();
    rep(i, h) {
        rep(j, w) {
            cout << need[i][j] << ' ';
        }
        cout << el;
    }
    rep(i, 10) cout << "=";
    cout << el;
}

void put_vi(vi v) {
    for (auto x: v) {
        cout << x << ' ';
    }
    cout << el;
}





class SegmentTree {
    public:
    vi data;
    int siz = 1;

    void init(int n) {
        siz = 1;
        while (siz < n) siz *= 2;
        data.assign(siz*2, 1e18);
    }
    //1 point
    void update(int pos, int x) {
        pos = pos + siz - 1;
        data[pos] = x;
        while (pos >= 2) {
            pos /= 2;
            data[pos] = min(data[pos * 2], data[pos * 2 + 1]);
        }
    }
    //range
    int aggregate(int l, int r, int a, int b, int u) {
        if (r <= a || b <= l) return 1e18;
        if (l <= a && b <= r) return data[u];
        int m = (a + b) / 2;
        int ans_l = aggregate(l, r, a, m, u * 2);
        int ans_r = aggregate(l, r, m, b, u * 2 + 1);
        return min(ans_l, ans_r);
    }
};

signed main() {
    int n, l, r;
    cin >> n >> l >> r;
    vi x(n);
    rep(i, n) cin >> x[i];

    
    SegmentTree z;
    z.init(n);

    //dp[i] = 足場iに到達できる最小のジャンプ数
    vi dp(n, 1e18);
    dp[0] = 0;
    z.update(1, 0);

    for (int i=1; i<n; ++i) {
        int pos_l = distance(x.begin(), lower_bound(x.begin(), x.end(), x[i]-r));
        int pos_r = distance(x.begin(), upper_bound(x.begin(), x.end(), x[i]-l))-1;
        /*
        なんでrightはupper-1にしないといけないのか？lowerじゃダメなのか？
        x[pos_l] + r >= x[i]なるpos_lが到達可能な最も左の足場
        x[pos_r] + l > x[i]なるpos_rが到達可能な最も木の足場

        解説 by chat gpt
        7 3 5
        0 2 5 8 10 13 15
        の10の時バグるよ

        lower_boundだと
        10-3=7だから7以上の最小の要素のインデックスということで
        8のインデックス3が返されるけど，3->4(8->10)は2なので行けない

        upper_bound-1だと
        10-3=7だから7より大きい最小の要素のインデックス-1ということで
        5のインデックス2が返される
        2->4(5->10)はl以上ではあるからいける可能性がある

        x[pos_l] + r >= x[i]
        x[pos_r] + l >= x[i]
        l <= x[i] - x[pos] <= r
        (i)左の不等式
        l <= x[i] - x[pos]
        x[pos] <= x[i] - l

        */
        
        // cout << "i = " << i << el;
        // if (pos_l > pos_r) continue;
        // cout << pos_l << ' ' << pos_r << el;
        // cout << "dp  ";
        // repp(j, pos_l, pos_r+1) cout << dp[j] << ' ';
        // cout << el;
        // cout << "seg ";
        // repp(j, pos_l, pos_r+1) cout << z.data[j+1] << ' ';
        // cout << el;
        
        
        ++pos_l, ++pos_r;
        dp[i] = z.aggregate(pos_l, pos_r+1, 1, z.siz + 1, 1) + 1;
        
        // cout << "dp[i] = " << dp[i] << el;
        z.update(i+1, dp[i]);
    }

    cout << dp[n-1] << el;
}





/*
7 3 5
0 2 5 8 10 13 15



*/














//関数群---------------------------------------------------

 
// 素因数分解
// 460 = 2^2 x 5 x 23 の場合
// 返り値は {{2, 2}, {5, 1}, {23, 1}}
vpii prime_factorize(int N) {
    // 答えを表す可変長配列
    vpii res;

    // √N まで試し割っていく
    for (int p = 2; p * p <= N; ++p) {
        // N が p で割り切れないならばスキップ
        if (N % p != 0) {
            continue;
        }

        // N の素因数 p に対する指数を求める
        int e = 0;
        while (N % p == 0) {
            // 指数を 1 増やす
            ++e;

            // N を p で割る
            N /= p;
        }

        // 答えに追加
        res.emplace_back(p, e);
    }

    // 素数が最後に残ることがありうる
    if (N != 1) {
        res.emplace_back(N, 1);
    }
    return res;
}

//文字列sにtが含まれているかを判定する
// s.size() >= t.size()に注意
bool contain_string(string s, string t) {
    if ((int)s.size() < (int)t.size()) {
        return false;
    }
    int cnt;
    for (int i=0;i<(int)s.size(); i++) {
        cnt = 0;
        for (int j = 0; j<(int)t.size(); j++) {
            if (i+j <(int)s.size() && s[i+j] == t[j]) {
                cnt ++;
            }
        }
        if (cnt == (int)t.size()) {
            return true;
        }
    }
    return false;
}

int gcd(int a, int b) {
    if (a < b) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    while(b) {
        int aa = b;
        int bb = a%b;
        a = aa;
        b = bb;
    }
    return a;
}
int lcm(int a, int b) {
    return a*b/gcd(a, b);
}
int powll(int a, int b) {
    int k = 1;
    rep(i, b) {
        k *= a;
    }
    return k;
}
bool in_table(int i, int h) {
    if (i<0 || i>=h) {
        return false;
    } else {
        return true;
    }
}
bool in_table(int i, int j, int h, int w) {
    if (i<0 || i>=h || j<0 || j>=w) {
        return false;
    }
    return true;
}


int modPow(int a, int n, int mod) {
    int res = 1;
    while(n > 0) {
        if (n & 1) res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}
int modInv(int a, int mod) {
    return modPow(a, mod-2, mod);
}
bool isPrime(int n) {
    if (n < 2) return false;
    for (int i=2; i<=sqrt(n); ++i) if (n % i == 0) return false;
    return true;
}

/*
-----
---------------
-------------------------
---------------
-----
*/

//Union Find
// struct UnionFind {//頂点数N, クエリ数Q -> O(Q log N)
//     vi p; //自分の親を管理
//     vi r;
//     UnionFind(int n) { //コンストラクタ インスタンス生成時に初期化
//         p.resize(n);
//         rep(i, n) {
//             p[i] = i;
//         }
//         r.resize(n, 1);
//     }
//     int find(int x) { // 均し計算量O(log N)
//         if (p[x] == x) return x;
//         else return p[x] = find(p[x]);//パス圧縮　自分の親を代表元に張りなおす
//     }
//     void unite(int x, int y) {
//         x = find(x);
//         y = find(y);
//         if (x == y) return;
//         if (r[x] > r[y]) {// Union by rank
//             swap(x, y);
//         }
//         if (r[x] == r[y]) {
//             ++r[y];
//         }
//         p[x] = y;
//     }
// };




// vb seen;
// void dfs (const Graph &G, int v) {
//     seen[v] = true;
//     //cout << "v = " << v+1 << el;
//     for (auto nextv : G[v]) {
//         if (seen[nextv] == true) {
//             continue;
//         }
//         dfs(G, nextv);
//     }
// }

// vi dist;
// int bfs (const Graph &G, int v) {
//     queue<int> que;
//     dist[v] = 0;
//     que.push(v);
//     while(!que.empty()) {
//         v = que.front();
//         que.pop();
//         // cout << "v = " << v+1 << el;
//         for(int nv: G[v]) {
//             if (dist[nv] == -1) {
//                 dist[nv] = dist[v] + 1;
//                 que.push(nv);
//             } else {
//                 //tuiki
//                 continue;
//             }
//         }
//     }
//     return 0;
// }