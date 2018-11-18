#include <bits/stdc++.h>
using namespace std;
const int N = 1e5, K = 1e5;
typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back

int ar[N + 5];
int ans[N + 5];
int pref0[N + 5];
int prefsum[N + 5];


struct cond{
  int l;
  int r;
  int mins;
  int max_neg;

  bool operator<(const cond& a){
    if(l != a.l) return l < a.l;
    if(r != a.r) return r < a.r;
    return mins < a.mins;
  }

} br[K + 5];

const string IMPOSSIBLE = "Impossible";

priority_queue<pii, vector<pii>, greater<pii> > pq;
int n, k;
int main(){
  scanf("%d%d", &n, &k);
  for(int i = 1; i <= n; ++i){
    scanf("%d", &ar[i]);
    pref0[i] = pref0[i - 1] + (ar[i] == 0);
    prefsum[i] = prefsum[i - 1] + ar[i];
  }
  for(int i = 1;i <= k; ++i){
    scanf("%d%d%d", &br[i].l, &br[i].r, &br[i].mins);
    int r = br[i].r;
    int l = br[i].l;
    int cnt0 = pref0[r] - pref0[l - 1];
    int sums = prefsum[r] - prefsum[l - 1];
    int makssum = cnt0 + sums;
    if(makssum < br[i].mins){
      puts(IMPOSSIBLE.c_str());
      return 0;
    }
    br[i].max_neg = (makssum - br[i].mins) >> 1;
  }
  sort(br + 1, br + k + 1);
  int poi = 1;
  int cnt_neg = 0;
  for(int i = 1;i <= n; ++i){
    while(poi <= k && br[poi].l <= i){
      pq.push(mp(cnt_neg + br[poi].max_neg, br[poi].r));
      poi++;
    } 
    while(!pq.empty() && pq.top().se < i) pq.pop();
    if(ar[i] == 0){
      if(pq.empty()) ans[i] = -1, cnt_neg++;
      else if(pq.top().fi > cnt_neg){
        ans[i] = -1, cnt_neg++;
      }
      else{
        ans[i] = 1;
      }
    }
    else{
      ans[i] = ar[i];
    }
  }

  for(int i = 1;i <= n; ++i){
    printf("%d%c", ans[i], (i == n) ? '\n' : ' ');
  }
  return 0;
}

/*
3 1
0 0 0
1 2 2

5 1 
1 0 -1 0 1
1 4 3

5 1
1 0 -1 0 1
1 4 0

5 2
1 0 -1 0 1
1 4 0
2 5 1

5 2
1 0 -1 0 1
1 4 0
2 3 -1

*/
