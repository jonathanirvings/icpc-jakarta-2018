/*
- binary search
- graph k-closure

suhendry.effendy
*/
#include <bits/stdc++.h>
using namespace std;

#define REP(i,n)      for ( int i = 0, _n = (n); i < _n; i++ )
#define FOR(i,a,b)    for ( int i = (a), _n = (b); i <= _n; i++ )

const int maxn = 505;

int N, M;
vector <int> con[maxn];

struct tdata { int a, b; };
tdata edge(int a, int b) { return (tdata){min(a,b),max(a,b)}; }

bool go(int k) {
	bool E[maxn][maxn] = {false};
	int  deg[maxn] = {0};
	FOR(i,1,N) REP(j,con[i].size()) E[i][con[i][j]] = true;
	FOR(i,1,N) deg[i] = con[i].size();

	queue <tdata> q;
	FOR(i,1,N) FOR(j,i+1,N) if ( !E[i][j] && deg[i] + deg[j] >= k )
		q.push((edge(i,j))), E[i][j] = E[j][i] = true;

	while ( !q.empty() ) {
		tdata p = q.front(); q.pop();
		deg[p.a]++;
		deg[p.b]++;
		FOR(i,1,N) if ( i != p.a && !E[p.a][i] && deg[p.a] + deg[i] >= k )
			q.push(edge(p.a,i)), E[p.a][i] = E[i][p.a] = true;
		FOR(i,1,N) if ( i != p.b && !E[p.b][i] && deg[p.b] + deg[i] >= k )
			q.push(edge(p.b,i)), E[p.b][i] = E[i][p.b] = true;
	}

	FOR(i,1,N) if ( deg[i] != N - 1 ) return false;
	return true;
}

int main(int argc, char *argv[]) {
	
	scanf( "%d %d", &N, &M );
	REP(_,M) {
		int a, b;
		scanf( "%d %d", &a, &b );
		con[a].push_back(b);
		con[b].push_back(a);
	}

	int ans = 0;
	int L = 0, R = 2*N;
	while ( L <= R ) {
		int k = (L + R) >> 1;
		if ( go(k) ) ans = k, L = k + 1;
		else R = k - 1;
	}
	
	printf( "%d\n", ans );

	return 0;
}
