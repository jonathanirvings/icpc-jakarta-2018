//start of jonathanirvings' template v3.0.3 (BETA)
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <set>
#include <vector>
#include <cmath>
#include <assert.h>
#include <queue>
#include <cstring>
#include <string>
using namespace std;

typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;
typedef pair<string,string> pss;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<pii> vii;
typedef vector<LL> vl;
typedef vector<vl> vvl;

double EPS = 1e-9;
int INF = 1000000005;
long long INFF = 1000000000000000005LL;
double PI = acos(-1);
int dirx[8] = {-1,0,0,1,-1,-1,1,1};
int diry[8] = {0,1,-1,0,-1,1,-1,1};

#ifdef TESTING
  #define DEBUG fprintf(stderr,"====TESTING====\n")
  #define VALUE(x) cerr << "The value of " << #x << " is " << x << endl
  #define debug(...) fprintf(stderr, __VA_ARGS__)
#else
  #define DEBUG 
  #define VALUE(x)
  #define debug(...)
#endif

#define FOR(a,b,c) for (int (a)=(b);(a)<(c);++(a))
#define FORN(a,b,c) for (int (a)=(b);(a)<=(c);++(a))
#define FORD(a,b,c) for (int (a)=(b);(a)>=(c);--(a))
#define FORSQ(a,b,c) for (int (a)=(b);(a)*(a)<=(c);++(a))
#define FORC(a,b,c) for (char (a)=(b);(a)<=(c);++(a))
#define FOREACH(a,b) for (auto &(a) : (b))
#define REP(i,n) FOR(i,0,n)
#define REPN(i,n) FORN(i,1,n)
#define MAX(a,b) a = max(a,b)
#define MIN(a,b) a = min(a,b)
#define SQR(x) ((LL)(x) * (x))
#define RESET(a,b) memset(a,b,sizeof(a))
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define ALL(v) v.begin(),v.end()
#define ALLA(arr,sz) arr,arr+sz
#define SIZE(v) (int)v.size()
#define SORT(v) sort(ALL(v))
#define REVERSE(v) reverse(ALL(v))
#define SORTA(arr,sz) sort(ALLA(arr,sz))
#define REVERSEA(arr,sz) reverse(ALLA(arr,sz))
#define PERMUTE next_permutation
#define TC(t) while(t--)

inline string IntToString(LL a){
  char x[100];
  sprintf(x,"%lld",a); string s = x;
  return s;
}

inline LL StringToInt(string a){
  char x[100]; LL res;
  strcpy(x,a.c_str()); sscanf(x,"%lld",&res);
  return res;
}

inline string GetString(void){
  char x[1000005];
  scanf("%s",x); string s = x;
  return s;
}

inline string uppercase(string s){
  int n = SIZE(s); 
  REP(i,n) if (s[i] >= 'a' && s[i] <= 'z') s[i] = s[i] - 'a' + 'A';
  return s;
}

inline string lowercase(string s){
  int n = SIZE(s); 
  REP(i,n) if (s[i] >= 'A' && s[i] <= 'Z') s[i] = s[i] - 'A' + 'a';
  return s;
}

inline void OPEN (string s) {
  #ifndef TESTING
  freopen ((s + ".in").c_str (), "r", stdin);
  freopen ((s + ".out").c_str (), "w", stdout);
  #endif
}

//end of jonathanirvings' template v3.0.3 (BETA)

int edit_distance(const string& s, const string& t) {
  vector<vector<int>> dp(s.size() + 1, vector<int>(t.size() + 1));
  for (int i = 0; i <= t.size(); ++i) {
    dp[s.size()][i] = t.size() - i;
  }
  for (int i = 0; i <= s.size(); ++i) {
    dp[i][t.size()] = s.size() - i;
  }
  for (int i = s.size() - 1; i >= 0; --i) {
    for (int j = t.size() - 1; j >= 0; --j) {
      if (s[i] == t[j]) {
        dp[i][j] = dp[i + 1][j + 1];
      } else {
        dp[i][j] = min(dp[i + 1][j + 1], min(dp[i + 1][j], dp[i][j + 1])) + 1;
      }
    }
  }
  return dp[0][0];
}


int dp[30][30][333];

int max3(int a, int b, int c) {
  return max(a, max(b,c));
}

int min3(int a, int b, int c) {
  return min(a, min(b,c));
}

string answer(string S)
{
  string ret = "";
  int N = S.length();
  int A = 0;
  int B = 0;
  for (char c:S)
    if (c == '0') A++; else B++;

  if (A > B) {
    for (int i = 0;i < N;i++)
      ret += '1';
  } else if (B > A) {
    for (int i = 0;i < N;i++)
      ret += '0';
  } else {
    if (S[0] == '1') ret += '0';
    else ret += '1';
    for (int i=1;i<N;i++)
      ret += S[0];
  }
  return ret;
}

int main()
{
  string S = GetString();
  printf("%s\n",answer(S).c_str());
  // int N = 16;
  
  // FORN(len,1,N)
  // {
  //   REP(i,1<<len)
  //   {
  //     string S = "";
  //     REP(j,len) S += (i & (1 << j)) ? '1' : '0';
  //     assert(edit_distance(S, answer(S)) > len / 2);
  //   }
  // }
}

