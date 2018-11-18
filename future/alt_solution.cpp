/*
- dynamic programming
- binary search

time-complexity: O(N.2^M.M^2)

suhendry.effendy
*/
#include <bits/stdc++.h>
using namespace std;

#define REP(i,n)      for ( int i = 0, _n = (n); i < _n; i++ )
#define FOR(i,a,b)    for ( int i = (a), _n = (b); i <= _n; i++ )

typedef pair<string,int> psi;

const int maxn = 20;

int  N;
char S[maxn][20];
int  len[maxn];

int is_on(int bit, int x)   { return bit & (1 << x); }
int all(int x) { return (1 << len[x]) - 1; }

int dp[maxn][1<<15];
psi arr[maxn][1<<15];

string get_string(int x, int bit) {
	string ret;
	REP(i,len[x]) if ( is_on(bit,i) ) ret += S[x][i];
	return ret;
}

int main(int argc, char *argv[]) {
	
	scanf( "%d", &N );
	REP(i,N) scanf( "%s", S[i] );	
	REP(i,N) len[i] = strlen(S[i]);
	
	REP(i,N) {
		FOR(bit,1,all(i)) {
			string s = get_string(i,bit);
			int pcnt = __builtin_popcount(bit);
			if ( i == 0 ) {
				dp[i][bit] = pcnt;
			}
			else {
				dp[i][bit] = 0;
				int L = 0, R = all(i-1) - 1;
				while ( L <= R ) {
					int m = (L + R) >> 1;
					if ( arr[i-1][m].first < s ) {
						if ( arr[i-1][m].second != 0 )
							dp[i][bit] = max(dp[i][bit],pcnt+arr[i-1][m].second);
						L = m + 1;
					}
					else
						R = m - 1;
				}
			}
			arr[i][bit-1] = psi(s,dp[i][bit]);
		}
		sort(arr[i],arr[i]+all(i));
		FOR(bit,1,all(i)-1)
			arr[i][bit].second = max(arr[i][bit].second,arr[i][bit-1].second);
	}

	int ans = 0;
	FOR(bit,1,all(N-1))
		if ( dp[N-1][bit] ) ans = max(ans,dp[N-1][bit]);

	printf( "%d\n", ans == 0 ? -1 : ans );

	return 0;
}
