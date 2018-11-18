#include <bits/stdc++.h>
using namespace std;

const int maxn = 100005;

int  N;
bool truth[maxn];
char str[105];

int main(int argc, char *argv[]) {
	
	scanf( "%d", &N );
	for ( int i = 1; i <= N; i++ ) {
		scanf( "%s", str );
		truth[i] = str[0] == 'T';
	}

	for ( int i = N-1; i >= 1; i-- )
		if ( !truth[i+1] ) truth[i] = !truth[i];
	
	printf( "%s\n", truth[1] ? "TRUTH" : "LIE" );

	return 0;
}
