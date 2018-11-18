#include <bits/stdc++.h>
using namespace std;

#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define ALL(a) begin(a), end(a)
#define SZ(a) ((int)(a).size())
#define DEFUN(typ, name, ...) auto name = [&](__VA_ARGS__) -> typ

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

const ll TEN14 = 100LL * 1000 * 1000 * 1000 * 1000;

int n, m, k;
ll mod;
int digits[100];
list<ll> tour;
map<ll, vi> adj__;
map<ll, list<ll>::iterator> available;

bool init() {
  mod = 1;
  for (int i = 0; i < n - 1; i++) {
    mod *= m;
    if (mod > TEN14) {
      return false;
    }
  }
  return true;
}

vi &getAdj(ll x) {
  if (adj__.count(x) == 0) {
    vi tmp(m);
    iota(ALL(tmp), 0);
    adj__.emplace(x, move(tmp));
  }
  return adj__[x];
}

void outputOne() {
  for (int i = 0; i < n - 1; i++) {
    printf("%d", digits[0]);
  }
}

void output(const list<ll> &tour) {
  assert(SZ(tour) > 1);
  auto it = begin(tour);
  outputOne();
  assert(it != end(tour));
  it++;
  for (int i = 0; i < k; i++) {
    assert(it != end(tour));
    int idx = *it % m;
    assert(idx >= 0 && idx < m);
    printf("%d", digits[idx]);
    it++;
  }
  puts("");
}

int insert(list<ll> &mainList, list<ll>::iterator toInsert, ll src) {
  list<ll> cur;
  cur.push_back(src);
  ll last = src;
  assert(last < mod);
  assert(available.find(src) != end(available));
  do {
    vi &adj = getAdj(last);
    assert(!adj.empty());
    int x = adj.back();
    adj.pop_back();
    if (adj.empty()) {
      auto it = available.find(last);
      assert(it != end(available));
      available.erase(it);
      debug assert(available.find(last) == end(available));
    }
    ll nxt = (last * m + x) % mod;
    assert(nxt < mod);
    cur.push_back(nxt);
    auto it = prev(end(cur));
    if (!available.count(nxt)) {
      available[nxt] = it;
    }
    if (SZ(cur) >= k + 1) {
      output(cur);
      exit(0);
    }
    last = nxt;
  } while (last != src);
  int ret = SZ(cur) - 1;
  cur.pop_front();
  mainList.splice(toInsert, cur);
  return ret;
}

void solve1() {
    tour.push_back(0);
    available[0] = begin(tour);
    int rem = k;
    while (rem > 0) {
        assert(!available.empty());
        auto start = begin(available)->second;
        rem -= insert(tour, next(start), *start);
    }
    output(tour);
}

void solve2() {
  list<ll> curTour;
  vi tmp(m);
  iota(ALL(tmp), 0);
  ll mod = TEN14 + 31;  // prime
  for (int attempt = 0; attempt < 10; attempt++) {
    ll cur = 0;
    curTour.push_back(cur);
    set<ll> seen;
    seen.insert(cur);
    for (int i = 0; i < k; i++) {
      ll found = -1;
      for (int j : tmp) {
        ll nxt = (cur * m + j) % mod;
        if (!seen.count(nxt)) {
          found = nxt;
          break;
        }
      }
      if (found < 0) {
        break;
      }
      curTour.push_back(found);
      cur = found;
    }
    if (SZ(curTour) == k + 1) {
      output(curTour);
      return;
    }
  }
  assert(false);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n >> m >> k;
  for (int i = 0; i < m; i++) {
    cin >> digits[i];
  }
  if (n == 1) {
    for (int i = 0 ; i < k; i++) {
      printf("%d", digits[i]);
    }
    puts("");
    return 0;
  }
  if (init()) {
    solve1();
  } else {
    solve2();
  }
}
