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


signed main() {
    int n;
    cin >> n;
    vi a(n), b(n);
    rep(i, n) cin >> a[i] >> b[i];
    
    //1:+ 2:-
    //x:表, y:裏
    auto solve = [&](int x, int y) -> int {
        int sum = 0;
        rep(i, n) {
            int c1 = a[i];
            if (x == 2) c1 = -a[i];
            int c2 = b[i];
            if (y == 2) c2 = -b[i];
            sum += max(0LL, c1 + c2);
        }
        return sum;
    };
    int ans1 = solve(1, 1);
    int ans2 = solve(1, 2);
    int ans3 = solve(2, 1);
    int ans4 = solve(2, 2);
    cout << max({ans1, ans2, ans3, ans4}) << el;
    
}




/*


*/

