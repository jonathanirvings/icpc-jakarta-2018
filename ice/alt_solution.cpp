#include <bits/stdc++.h>
using namespace std;

#define REP(i,n)      for ( int i = 0, _n = (n); i < _n; i++ )
#define FOR(i,a,b)    for ( int i = (a), _n = (b); i <= _n; i++ )
#define FORD(i,a,b)   for ( int i = (a), _n = (b); i >= _n; i-- )
#define FORS(i,a,b,c) for ( int i = (a), _n = (b); i <= _n; i += c )
#define FOREACH(p,s)  for ( __typeof((s).begin()) p=(s).begin(); p!=(s).end(); p++)

const int maxn = 505;

int  R, C;
char m[maxn][maxn];

int main(int argc, char *argv[]) {
	
	scanf( "%d %d", &R, &C );
	FOR(r,1,R) scanf( "%s", m[r]+1 );

	int ans = 0;

	if ( R > 2 && C > 2 ) {
		FOR(r,2,R-1) FOR(c,2,C-1)
			if ( m[r][c] == '.' ) ans++;
		bool okay = false;
		FOR(r,2,R-1) if( m[r][1] == '#' ) okay = true;
		FOR(r,2,R-1) if( m[r][C] == '#' ) okay = true;
		FOR(c,2,C-1) if( m[1][c] == '#' ) okay = true;
		FOR(c,2,C-1) if( m[R][c] == '#' ) okay = true;
		if ( !okay ) ans++;
	}
	else if ( R <= 2 ) {
		FOR(c,2,C-1) {
			bool okay = false;
			FOR(r,1,R) if ( m[r][c] == '#' ) okay = true;
			if ( !okay ) ans++;
		}
	}
	else if ( C <= 2 ) {
		FOR(r,2,R-1) {
			bool okay = false;
			FOR(c,1,C) if ( m[r][c] == '#' ) okay = true;
			if ( !okay ) ans++;
		}
	}

	printf( "%d\n", ans );
	
	return 0;
}
