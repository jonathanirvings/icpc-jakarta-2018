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

const int MAXN = 100000;
const int MAXK = 100000;

int n,k;
int risan[MAXN + 5];
int pre[MAXN + 5];
pair<pii,int> data[MAXK + 5];
vii masuk[MAXN + 5];
priority_queue<pii> pq;

int main()
{
  scanf("%d %d",&n,&k);
  REPN(i,n)
  {
    scanf("%d",&risan[i]);
    if (risan[i] == -1) pre[i] = 1;
  }
  REPN(i,n) pre[i] += pre[i-1];
  REPN(i,k)
  {
    scanf("%d %d %d",&data[i].fi.fi,&data[i].fi.se,&data[i].se);
    int nyawa = (data[i].fi.se - data[i].fi.fi + 1 - data[i].se) / 2;
    nyawa -= pre[data[i].fi.se] - pre[data[i].fi.fi - 1];
    masuk[data[i].fi.fi].pb(mp(nyawa,i));
  }
  int minus = 0;
  REPN(i,n)
  {
    while (SIZE(pq) > 0 && data[pq.top().se].fi.se < i) pq.pop();
    for (pii x : masuk[i])
      pq.push(mp(-x.fi - minus,x.se));

    if (risan[i] != 0) continue;
    int x = SIZE(pq) == 0 ? INF : -pq.top().fi;
    if (x < minus)
    {
      puts("Impossible");
      return 0;
    } else if (x == minus)
    {
      risan[i] = 1;
    } else 
    {
      ++minus;
      risan[i] = -1;
    }
  }
  REPN(i,n)
  {
    printf("%d",risan[i]);
    if (i < n) printf(" ");
    else puts("");
  }
  return 0;
}
