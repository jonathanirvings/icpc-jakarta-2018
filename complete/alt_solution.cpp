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

const int N = 501;

list<pii> byTot[N + N];
vi remEdges[N];
list<pii>::iterator its[N][N];
int status[N][N];
int deg[N];
int totDeg[N][N];  // sanity check
int rem;
vector<pii> workList;

void update(int threshold, int u) {
  for (int i = 0; i < SZ(remEdges[u]); i++) {
    int v = remEdges[u][i];
    if (status[u][v]) {
      swap(remEdges[u][i], remEdges[u].back());
      remEdges[u].pop_back();
      i--;
      continue;
    }
    byTot[totDeg[u][v]].erase(its[u][v]);
    totDeg[u][v] = totDeg[v][u] = deg[u] + deg[v];
    byTot[totDeg[u][v]].emplace_back(u, v);
    auto neit = byTot[totDeg[u][v]].end();
    neit--;
    its[u][v] = its[v][u] = neit;
    if (totDeg[u][v] >= threshold) {
      status[u][v] = status[v][u] = true;
      workList.emplace_back(u, v);
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  rem = n * (n - 1) / 2 - m;
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    u--; v--;
    status[u][v] = true;
    status[v][u] = true;
    deg[u]++;
    deg[v]++;
  }
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (status[i][j]) {
  continue;
      }
      totDeg[i][j] = totDeg[j][i] = deg[i] + deg[j];
      byTot[totDeg[i][j]].emplace_back(i, j);
      auto it = byTot[totDeg[i][j]].end();
      it--;
      its[i][j] = its[j][i] = it;
      remEdges[i].push_back(j);
      remEdges[j].push_back(i);
    }
  }
  workList.reserve(n * (n - 1) / 2);
  for (int i = 2 * N - 1; i >= 0; i--) {
    for (auto &it : byTot[i]) {
      assert(!status[it.fi][it.se]);
      status[it.fi][it.se] = status[it.se][it.fi] = true;
      workList.emplace_back(it.fi, it.se);
    }
    while (!workList.empty()) {
      int u = workList.back().fi;
      int v = workList.back().se;
      workList.pop_back();
      rem--;
      if (u > v) {
  swap(u, v);
      }
      assert(totDeg[u][v] >= i);
      deg[u]++;
      deg[v]++;
      update(i, u);
      update(i, v);
    }
    if (rem == 0) {
      cout << i << endl;
      return 0;
    }
  }
  assert(false);
  return 0;
}
