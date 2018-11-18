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

const int N = 100000;
const int LOGN = 18;
const int MOD = 360;

// class SumSegtree
// {
// public:
//   vector<int> tree;
//   vector<int> prop;

//   SumSegtree()
//   {
//     tree.resize(4 * N + 10);
//     prop.resize(4 * N + 10);
//   }

//   void pushdown(int ix,int L,int R)
//   {
//     int M = (L + R) >> 1;
//     prop[ix*2+1] += prop[ix];
//     tree[ix*2+1] += prop[ix] * (M - L + 1);
//     prop[ix*2+2] += prop[ix];
//     tree[ix*2+2] += prop[ix] * (R - M);
//     prop[ix] = 0;
//   }

//   void update(int ix,int L,int R,int x,int y,int val)
//   {
//     if (x <= L && R <= y)
//     {
//       prop[ix] += val;
//       tree[ix] += val * (R - L + 1);
//       return;
//     }
//     if (y < L || R < x) return;
//     pushdown(ix,L,R);
//     int M = (L + R) >> 1;
//     update(ix*2+1,L,M,x,y,val);
//     update(ix*2+2,M+1,R,x,y,val);
//     tree[ix] = tree[ix*2+1] + tree[ix*2+2];
//   }

//   int query(int ix,int L,int R,int x,int y)
//   {
//     if (x <= L && R <= y) return tree[ix];
//     if (y < L || R < x) return 0;
//     pushdown(ix,L,R);
//     int M = (L + R) >> 1;
//     return query(ix*2+1,L,M,x,y) + query(ix*2+2,M+1,R,x,y);
//   }

//   void update(int x,int y,int val) {update(0,0,N,x,y,val);}

//   void update(int x,int val) {update(x,x,val);}

//   int query(int x,int y) {return query(0,0,N,x,y);}

//   int query(int x) {return query(x,x);}
// };

class SumSegtree
{
public:
  vector<int> bit;

  SumSegtree()
  {
    bit.resize(N + 10);
  }

  void bit_update(int x, int val)
  {
    ++x;
    for (int i = x; i <= N + 1; i += (i & -i)) bit[i] += val;
  }

  int bit_query(int x)
  {
    ++x;
    int res = 0;
    for (int i = x; i > 0; i -= (i & -i)) res += bit[i];
    return res;
  }

  void update(int x,int y,int val)
  {
    bit_update(x,val);
    bit_update(y+1,-val);
  }

  void update(int x,int val)
  {
    bit_update(x,val);
  }

  int query(int x)
  {
    return bit_query(x);
  }

  int query(int x,int y)
  {
    return bit_query(y) - bit_query(x-1);
  }
};

int n,m,q;
vi adj[N + 5];
int op,a,b;

int inorder[N + 5];
int now = 0;

int h[N + 5];
int parent[LOGN + 2][N + 5];
int lst[N + 5];
bool ada[N + 5];
int simpan[N + 5];

int gone[N + 5];

SumSegtree putarTree;  // update range
SumSegtree adaTree;  // update range
SumSegtree goneTree;  // query range

void dfs(int u, int pt)
{
  inorder[u] = ++now;
  lst[inorder[u]] = inorder[u];
  parent[0][inorder[u]] = inorder[pt];
  h[inorder[u]] = h[inorder[pt]] + 1;

  for (int v : adj[u])
  {
    if (v == pt) continue;
    dfs(v, u);
    MAX(lst[inorder[u]],lst[inorder[v]]);
  }
}

int bruteForceFindBelowLost(int a)
{
  int belowLost = a;
  while (ada[parent[0][belowLost]]) belowLost = parent[0][belowLost];
  return belowLost;
}

int findBelowLost(int a)
{
  // return bruteForceFindBelowLost(a);
  int now = a;
  FORD(i,LOGN,0)
  {
    int u = parent[i][now];
    if (adaTree.query(now) - (u == 0 ? 0 : adaTree.query(parent[0][u])) == h[now] - h[u] + 1)
      now = u;
  }
  return now;
}

LL ctr = 0;

int bruteForceFindLost(int a)
{
  // int lost = a;
  // while (ada[parent[0][lost]]) lost = parent[0][lost];
  // return parent[0][lost];


  int lost = parent[0][a];
  while (ada[lost])
  {
    lost = parent[0][lost];
  }
  return lost;
}

int findLost(int a)
{
  // return bruteForceFindLost(a);
  int now = parent[0][a];
  if (!ada[now]) {
    return now;
  }
  FORD(i,LOGN,0)
  {
    int u = parent[i][now];
    if (adaTree.query(now) - (u == 0 ? 0 : adaTree.query(parent[0][u])) == h[now] - h[u] + 1)
      now = u;
  }
  return parent[0][now];
}

int bruteForceCount(int x)
{
  if (!ada[x]) return 0;
  int res = 1;
  int v = x + 1;
  while (v <= lst[x])
  {
    res += bruteForceCount(v);
    v = lst[v] + 1;
  }
  return res;
}

int count(int x)
{
  // return bruteForceCount(x);
  return lst[x] - x + 1 - goneTree.query(x,lst[x]);
}

int main()
{
  scanf("%d",&n);
  REP(i,n-1)
  {
    scanf("%d %d",&a,&b);
    adj[a].pb(b);
    adj[b].pb(a);
  }
  dfs(1, 0);
  REPN(i,n) debug("INORDER[%d]: %d\n", i, inorder[i]);
  REPN(i,n) debug("%d: parent = %d, h = %d, lst = %d\n",i,parent[0][i],h[i],lst[i]);
  
  REPN(i,n)
  {
    ada[i] = 1;
    adaTree.update(i,lst[i],1);
  }

  REPN(lv,LOGN) REPN(i,n) parent[lv][i] = parent[lv-1][parent[lv-1][i]];
  
  lst[0] = n;

  scanf("%d",&q);
  TC(q)
  {
    scanf("%d %d",&op,&a);
    debug("QUERY %d %d\n", op, a);
    a = inorder[a];
    int lost = findLost(a);
    if (op == 1)  // copot gear
    {
      simpan[a] = putarTree.query(a) + simpan[lost] - putarTree.query(lost);
      
      ada[a] = 0;
      adaTree.update(a,lst[a],-1);

      int inThisSubtree = lst[a] - a + 1 - goneTree.query(a,lst[a]);
      
      goneTree.update(lost, -inThisSubtree);
      gone[lost] -= inThisSubtree;

      gone[a] = inThisSubtree;
      goneTree.update(a, gone[a]);
    } else if (op == 2)  // taruh gear balik
    {
      int putar = (simpan[a] - putarTree.query(a)) - (simpan[lost] - putarTree.query(lost));
      simpan[a] = 0;
      putarTree.update(a, lst[a], putar);
      
      ada[a] = 1;
      adaTree.update(a,lst[a],1);

      goneTree.update(lost, gone[a]);
      gone[lost] += gone[a];

      goneTree.update(a, -gone[a]);
      gone[a] = 0;
    } else  // puter gear
    {
      int belowLost = findBelowLost(a);

      scanf("%d",&b);
      if (h[a] % 2 == 1) b *= -1;
      putarTree.update(belowLost, lst[belowLost], b);

      int cnt = count(belowLost);
      printf("%d\n", cnt * abs(b));
    }
    // REPN(i,n) debug("%d: ada = %d, adaTree = %d, putarTree = %d, simpan = %d\n", i, ada[i], adaTree.query(i), putarTree.query(i), simpan[i]);

  }
  REPN(i,n) if(!ada[i])
  {
    int a = i;

    int lost = findLost(a);
    int putar = (simpan[a] - putarTree.query(a)) - (simpan[lost] - putarTree.query(lost));
    simpan[a] = 0;
    putarTree.update(a, lst[a], putar);
    
    ada[a] = 1;
    adaTree.update(a,lst[a],1);
  }
  int risan = 0;
  REPN(i,n) debug("ROTATION[%d]: %d\n", i, putarTree.query(i));
  REPN(i,n) risan += ((putarTree.query(i) * (h[i] % 2 == 1 ? -1 : 1) % MOD) + MOD) % MOD;
  printf("%d\n", risan);

  // printf("%lld\n", ctr);
  return 0;
}
