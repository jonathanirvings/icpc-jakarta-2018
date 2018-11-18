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

struct DisjointSet {
  vi p, sz;
  DisjointSet(int n) : p(n), sz(n, 1) { iota(begin(p), end(p), 0); }
  int find(int x) { return p[x] == x ? x : (p[x] = find(p[x])); }
  void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) {
      return;
    }
    if (sz[x] < sz[y]) {
      sz[y] += sz[x];
      p[x] = y;
    } else {
      sz[x] += sz[y];
      p[y] = x;
    }
  }
};

bool solveTree(int u, int par, vi &visit, vector<vi> &g, vector<tuple<int, int, int>> &ans) {
  visit[u] = true;
  vi odds;
  for (int v : g[u]) {
    if (v != par) {
      assert(!visit[v]);
      if (solveTree(v, u, visit, g, ans)) {
        odds.push_back(v);
      }
    }
  }
  for (int i = 0; i + 1 < SZ(odds); i += 2) {
    ans.emplace_back(odds[i], u, odds[i + 1]);
  }
  if (SZ(odds) % 2 == 0) {
    return true;
  }
  if (par != -1) {
    ans.emplace_back(odds.back(), u, par);
  }
  return false;
}

vector<tuple<int, int, int>> solveTrees(int n, const vector<pii> &edges) {
  vector<vi> g(n);
  for (const auto &e : edges) {
    g[e.first].push_back(e.second);
    g[e.second].push_back(e.first);
  }
  vi visit(n);
  vector<tuple<int, int, int>> ans;
  for (int i = 0; i < n; i++) {
    if (visit[i]) {
      continue;
    }
    solveTree(i, -1, visit, g, ans);
  }
  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  DisjointSet ds(n + m);
  vector<pii> edges(m);
  vi id(n + m);
  iota(ALL(id), 0);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    u--; v--;
    if (ds.find(u) == ds.find(v)) {
      id[n] = v;
      edges[i] = {u, n};
      n++;
    } else {
      edges[i] = {u, v};
    }
    ds.merge(edges[i].first, edges[i].second);
  }
  auto ans = solveTrees(n, edges);
  cout << SZ(ans) << endl;
  for (const auto &b : ans) {
    int x, y, z;
    tie(x, y, z) = b;
    cout << id[x] + 1 << " " << id[y] + 1 << " " << id[z] + 1 << '\n';
  }
}
