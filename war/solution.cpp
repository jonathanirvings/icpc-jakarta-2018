/*
- analytic geometry: point projection (projection to y = 0)
- inclusion/exclusion principle

time complexity:
- preprocess: O(N * 2^M * M)
- per query : O(2^M * M * lg(N))

suhendry.effendy
*/
#include <bits/stdc++.h>
using namespace std;

#define REP(i,n)      for ( int i = 0, _n = (n); i < _n; i++ )
#define FOR(i,a,b)    for ( int i = (a), _n = (b); i <= _n; i++ )

const double EPS = 1E-9;
const int maxn = 40005;
const int maxm = 6;

struct tpoint { double x, y; };
struct twall  { double x1, x2, y; };
typedef pair <double,double> pdd;

int N, M, Q;
tpoint p[maxn];
twall  w[maxm];
int    sign[1<<maxm];
vector <twall>  wall[1<<maxm];
vector <double> L[1<<maxm];
vector <double> R[1<<maxm];

bool is_on(int bit, int x) { return bit & (1 << x); }
int  all(int n) { return (1 << n) - 1; }

pdd project(tpoint a, twall b) {
	pdd ret;
	ret.first  = a.x - (a.x - b.x1) / (a.y - b.y) * a.y;
	ret.second = a.x - (a.x - b.x2) / (a.y - b.y) * a.y;
	return ret;
}

pdd multi_project(tpoint a, vector <twall> &B) {
	pdd ret = pdd(-1E20,1E20);
	REP(i,B.size()) {
		pdd one = project(a,B[i]);
		ret.first  = max(ret.first,one.first);
		ret.second = min(ret.second,one.second);
	}
	return ret;
}

bool is_above(tpoint a, vector <twall> &B) {
	REP(i,B.size()) if ( a.y <= B[i].y + EPS ) return false;
	return true;
}

int count_blocked(tpoint q, int bit) {
	pdd cut = multi_project(q,wall[bit]);
	if ( cut.first <= cut.second + EPS ) {
		int a = upper_bound(L[bit].begin(),L[bit].end(),cut.first+EPS) - L[bit].begin();
		int b = lower_bound(R[bit].begin(),R[bit].end(),cut.second-EPS) - R[bit].begin();
		return a - b;
	}
	return 0;
}


int main(int argc, char *argv[]) {
	
	scanf( "%d %d %d", &N, &M, &Q );
	REP(i,N) scanf( "%lf %lf", &p[i].x, &p[i].y );
	REP(j,M) scanf( "%lf %lf %lf", &w[j].x1, &w[j].x2, &w[j].y );

	FOR(bit,1,all(M)) {
		sign[bit] = __builtin_popcount(bit) % 2 == 0 ? 1 : -1;
		REP(j,M) if ( is_on(bit,j) ) wall[bit].push_back(w[j]);
	}

	FOR(bit,1,all(M)) {
		REP(i,N) if ( is_above(p[i],wall[bit]) ) {
			pdd cut = multi_project(p[i],wall[bit]);
			if ( cut.first <= cut.second + EPS ) {
				L[bit].push_back(cut.first);
				R[bit].push_back(cut.second);
			}
		}
		sort(L[bit].begin(),L[bit].end());
		sort(R[bit].begin(),R[bit].end());
	}

	while ( Q-- ) {
		tpoint q;
		scanf( "%lf %lf", &q.x, &q.y );
		int ans = N;
		FOR(bit,1,all(M)) ans += sign[bit] * count_blocked(q,bit);
		printf( "%d\n", ans );
	}

	return 0;
}
