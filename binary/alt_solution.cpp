/*
- greedy

> a) remove all S[i] s.t. S[i] == 1 and i > 0 (i.e. exclude the left-most bit)
     prioritize the left-most one
> b) then, remove all S[i] s.t. S[i] == 0
> do (a) and (b) but stop when len(S) == len(N)
> if S > N, increase the answer by 1

suhendry.effendy
*/
#include <bits/stdc++.h>
using namespace std;

#define REP(i,n)      for ( int i = 0, _n = (n); i < _n; i++ )
#define FOR(i,a,b)    for ( int i = (a), _n = (b); i <= _n; i++ )

typedef long long LL;

int length(LL n) { return n == 0 ? 0 : 1 + length(n>>1); }

int main(int argc, char *argv[]) {
	
	LL   N;
	char S[100];
	scanf( "%lld", &N );
	scanf( "%s", S );

	int len_n = length(N);
	int len_s = strlen(S);

	priority_queue <int,vector<int>,greater<int> > one;
	FOR(i,1,len_s-1) if ( S[i] == '1' ) one.push(i);

	int ans = len_s - len_n;
	if ( len_s >= len_n && (int)one.size() >= len_s - len_n ) {
		int n_zero = len_s - 1 - one.size();
		LL  M = 0;
		while ( n_zero + 1 + one.size() > len_n ) S[one.top()] = '-', one.pop();
		REP(i,len_s) if ( S[i] != '-' ) M = M * 2 + S[i] - '0';
		if ( M > N ) ans++;
	}

	printf( "%d\n", max(0,ans) );
	
	return 0;
}
