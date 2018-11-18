#include <bits/stdc++.h>
using namespace std;

#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define ALL(a) begin(a), end(a)
#define SZ(a) ((int)(a).size())

#ifdef __DEBUG
#define debug if (true)
#else
#define debug if (false)
#endif

using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

template <typename T> using V = vector<T>;
template <typename T> using VV = vector<V<T>>;
template <typename T> using VVV = vector<VV<T>>;

const int N = 1e5 + 5;

int n;
int sign[N];
int sz[N];
int depth[N];
int par[N];
int heavyChild[N];
int head[N], idx[N];
int tin[N], tout[N];
ll lastVal[N], val[N];
set<pii> takenOuts[N];
vector<ll> bitVal(N);
vi bitCnt(N);
bool done[N];
bool isTakenOut[N];
vi g[N];

int dfs1(int u, int par) {
  sign[u] = depth[u] & 1;
  sz[u] = 1;
  for (int v : g[u]) {
    if (v != par) {
      depth[v] = depth[u] + 1;
      sz[u] += dfs1(v, u);
    }
  }
  return sz[u];
}

void dfs2(int u, int par) {
  static int timer = -1;
  tin[u] = ++timer;
  ::par[u] = par;
  int heavy = -1;
  for (int v : g[u]) {
    if (v != par && (heavy == -1 || sz[v] > sz[heavy])) {
      heavy = v;
    }
  }
  heavyChild[u] = heavy;
  if (heavy != -1) {
    head[heavy] = head[u]; idx[heavy] = idx[u] + 1;
    dfs2(heavy, u);
  }
  for (int v : g[u]) {
    if (v != par && v != heavy) {
      head[v] = v;
      idx[v] = 0;
      dfs2(v, u);
    }
  }
  tout[u] = timer;
}

bool isInSubtree(int x, int y) {
  return tin[x] <= tin[y] && tout[y] <= tout[x];
}

template <typename C>
void forPath(int x, int y, C &&callback) {
  if (depth[x] > depth[y]) {
    swap(x, y);
  }
  assert(isInSubtree(x, y));
  while (true) {
    if (head[x] == head[y]) {
      callback(x, y);
      break;
    }
    callback(head[y], y);
    y = par[head[y]];
  }
}

int getLastNotTakenOut(int x) {
  assert(!isTakenOut[x]);
  int ret = x;
  while (x >= 0) {
    auto it = takenOuts[head[x]].upper_bound(pii(depth[x], x));
    auto beg = begin(takenOuts[head[x]]);
    if (it == beg) {
      ret = head[x];
      x = par[head[x]];
    } else {
      it--;
      if (it->second != x) {
        assert(depth[it->second] < depth[x]);
        ret = heavyChild[it->second];
      }
      break;
    }
  }
  return ret;
}

template<typename T>
void update(vector<T> &bit, int x, int v) {
  for (int i = x; i < SZ(bit); i |= i + 1) {
    bit[i] += v;
  }
}

template<typename T>
void update(vector<T> &bit, int x, int y, int v) {
  update(bit, x, v);
  update(bit, y + 1, -v);
}

template<typename T>
T query(vector<T> &bit, int x) {
  int ret = 0;
  for (int i = x; i >= 0; i = (i & (i + 1)) - 1) {
    ret += bit[i];
  }
  return ret;
}

template<typename T>
void updateToRoot(vector<T> &bit, int x, int qty) {
  forPath(0, x, [&](int x, int y) {
    assert(tin[x] <= tin[y] && tin[y] <= tout[x]);
    assert(head[x] == head[y]);
    update(bit, tin[x], tin[y], qty);
  });
}

void takeOut(int x) {
  lastVal[x] = query(bitVal, tin[x]);
  int xx = getLastNotTakenOut(x);
  int pxx = par[xx];
  if (pxx >= 0) {
    lastVal[x] -= query(bitVal, tin[pxx]) - lastVal[pxx];
  }
  if (par[x] >= 0) {
    int val = sz[x] - query(bitCnt, tin[x]);
    updateToRoot(bitCnt, par[x], val);
    if (pxx >= 0 && par[pxx] >= 0) {
      updateToRoot(bitCnt, par[pxx], -val);
    }
  }
  takenOuts[head[x]].emplace(depth[x], x);
  isTakenOut[x] = true;
}

void putIn(int x) {
  assert(isTakenOut[x]);
  takenOuts[head[x]].erase(pii(depth[x], x));
  isTakenOut[x] = false;
  update(bitVal, tin[x], tout[x], -query(bitVal, tin[x]) + lastVal[x]);
  int xx = getLastNotTakenOut(x);
  int pxx = par[xx];
  if (pxx >= 0) {
    assert(isTakenOut[pxx]);
    update(bitVal, tin[x], tout[x], query(bitVal, tin[pxx]) - lastVal[pxx]);
  }
  if (par[x] >= 0) {
    int val = -sz[x] + query(bitCnt, tin[x]);
    updateToRoot(bitCnt, par[x], val);
    if (pxx >= 0 && par[pxx] >= 0) {
      updateToRoot(bitCnt, par[pxx], -val);
    }
  }
}

void update(int x, int y) {
  assert(!isTakenOut[x]);
  int xx = getLastNotTakenOut(x);
  if (sign[x] == sign[0]) {
    update(bitVal, tin[xx], tout[xx], y);
  } else {
    update(bitVal, tin[xx], tout[xx], -y);
  }
  debug {
    int resSz = query(bitCnt, tin[xx]);
    assert(resSz >= 0 && resSz <= sz[xx]);
  }
  cout << y * (sz[xx] - query(bitCnt, tin[xx])) << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n;
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--; v--;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  dfs1(0, -1);
  dfs2(0, -1);
  int q;
  cin >> q;
  while (q--) {
    int t, x;
    cin >> t >> x;
    x--;
    if (t == 1) {
      takeOut(x);
    } else if (t == 2) {
      putIn(x);
    } else {
      int y;
      cin >> y;
      update(x, y);
    }
  }
  for (int i = 0; i < n; i++) {
    if (isTakenOut[i]) {
      putIn(i);
    }
  }
  int sum = 0;
  for (int i = 0; i < n; i++) {
    int val = query(bitVal, tin[i]) % 360;
    if (val < 0) {
      val += 360;
    }
    if (sign[i] != sign[0]) {
      val = 360 - val;
      val %= 360;
    }
    sum += val;
  }
  cout << sum << endl;
}

/* TC

a -> b -> c -> d
1 d
1 a
2 a
2 d

a -> b
1 b
1 a

 */
