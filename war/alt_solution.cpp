//start of jonathanirvings' template v3.0.3 (BETA)

#include <bits/stdc++.h>
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

typedef long double Double;

class Fraction {
public:
  LL num, den;
  int sign;

  Fraction(LL _num, LL _den)
  {
    sign = (_num * _den == 0 ? 0 : _num * _den / llabs(_num * _den));
    num = llabs(_num);
    den = llabs(_den);
  }

  Fraction(const Fraction& other)
  {
    num = other.num;
    den = other.den;
    sign = other.sign;
  }

  bool operator<(Fraction other) const
  {
    return num * other.den * sign < den * other.num * other.sign;
  }

  bool operator>(Fraction other) const
  {
    return num * other.den * sign > den * other.num * other.sign;
  }

  bool operator==(Fraction other) const
  {
    return num * other.den * sign == den * other.num * other.sign;
  }

  bool operator<=(Fraction other) const
  {
    return (*this) < other || (*this) == other;
  }

  bool operator>=(Fraction other) const
  {
    return (*this) > other || (*this) == other;
  }

  Double toDouble()
  {
    return (Double)num / den * sign;
  }
};

const long long BIG = 2000000000000LL;

int n,m,q;
pii atas[40005];
pair<pii,int> garis[10];
vector<Fraction> L[1 << 5], R[1 << 5];
int freebies[1<<5];
pii titik;

Fraction intersect(pii a,pii b)
{
  return Fraction((LL)a.fi * (LL)b.se - (LL)a.se * (LL)b.fi, (LL)b.se - (LL)a.se);
}

int main()
{
  scanf("%d %d %d",&n,&m,&q);
  REP(i,n) scanf("%d %d",&atas[i].fi,&atas[i].se);
  REP(i,m)
  {
    scanf("%d %d %d",&garis[i].fi.fi,&garis[i].fi.se,&garis[i].se);
  }
  FOR(mask,1,1<<m)
  {
    int y = 0;
    REP(j,m) if (mask & (1 << j))
    {
      MAX(y,garis[j].se);
    }
    REP(i,n)
    {
      if (atas[i].se <= y)
      {
        ++freebies[mask];
        continue;
      }
      Fraction l = Fraction(-BIG, 1);
      Fraction r = Fraction(BIG, 1);
      REP(j,m) if (mask & (1 << j))
      {
        MAX(l,intersect(atas[i],mp(garis[j].fi.fi,garis[j].se)));
        MIN(r,intersect(atas[i],mp(garis[j].fi.se,garis[j].se)));
      }
      if (l <= r)
      {
        L[mask].pb(l);
        R[mask].pb(r);
      }
      else ++freebies[mask];
    }
  }
  FOR(mask,1,1<<m)
  {
    // debug(">>>> %d +%d:\n", mask,freebies[mask]);
    assert(L[mask].size() == R[mask].size());
    // for (int i = 0; i < L[mask].size(); ++i) {
    //   debug("[%.9Lf, %.9Lf]\n", L[mask][i], R[mask][i]);
    // }
    sort(ALL(L[mask]));
    sort(ALL(R[mask]));
  }
  TC(q)
  {
    scanf("%d %d",&titik.fi,&titik.se);
    int risan = n;
    FOR(mask,1,1<<m)
    {
      int seen = freebies[mask];
      Fraction l = Fraction(-BIG, 1);
      Fraction r = Fraction(BIG, 1);
      REP(j,m) if (mask & (1 << j))
      {
        MAX(l,intersect(titik,mp(garis[j].fi.fi,garis[j].se)));
        MIN(r,intersect(titik,mp(garis[j].fi.se,garis[j].se)));
      }
      if (l <= r)
      {
        seen += L[mask].end() - upper_bound(ALL(L[mask]),l);
        seen += lower_bound(ALL(R[mask]),r) - R[mask].begin();
      } else seen = n;

      int block = n - seen;
      risan += block * (__builtin_popcount(mask) % 2 == 1 ? -1 : 1);
    }
    printf("%d\n",risan);
  }
  return 0;
}

