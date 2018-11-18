#include <bits/stdc++.h>
using namespace std;

#define REP(i,n)      for ( int i = 0, _n = (n); i < _n; i++ )
#define FOR(i,a,b)    for ( int i = (a), _n = (b); i <= _n; i++ )
#define FORD(i,a,b)   for ( int i = (a), _n = (b); i >= _n; i-- )
#define FORS(i,a,b,c) for ( int i = (a), _n = (b); i <= _n; i += c )
#define FOREACH(p,s)  for ( __typeof((s).begin()) p=(s).begin(); p!=(s).end(); p++)

vector<string> split( const string& s, const string& delim =" " ) {
    vector<string> res;
    string t;
    for ( int i = 0; i < s.size(); i++ ) {
        if ( delim.find(s[i]) == string::npos ) t += s[i];
        else if ( !t.empty() ) { res.push_back(t); t = ""; }
    }
    if ( !t.empty() ) res.push_back(t);
    return res;
}
vector<int> splitInt( const string& s, const string& delim =" " ) {
    vector<string> tok = split( s, delim );
    vector<int> res;
    for ( int i = 0 ; i != tok.size(); i++ )
        res.push_back( atoi( tok[i].c_str() ) );
    return res;
}
vector<long long> splitLongLong( const string& s, const string& delim =" " ) {
    vector<string> tok = split( s, delim );
    vector<long long> res;
    for ( int i = 0 ; i != tok.size(); i++ )
        res.push_back( atoll( tok[i].c_str() ) );
    return res;
}

const int maxl = 10000000;
char line[10000005];
vector <long long> v;
vector <string> w;

int main(int argc, char *argv[]) {
	
    int N;
	long long K;

	assert( fgets(line,maxl,stdin) != 0);
	line[strlen(line)-1] = 0;
	v = splitLongLong(line);
	assert(v.size() == 1);
	K = v[0];
	assert(1 <= K && K <= (1LL << 60));

    assert( fgets(line,maxl,stdin) != 0);
    line[strlen(line)-1] = 0;
    N = strlen(line);
    assert(1 <= N && N <= 60);
    for (int i = 0; i < N; ++i) {
        assert(line[i] == '0' || line[i] == '1');
    }


	line[0] = 0;
	assert( fgets(line,maxl,stdin) == 0 );
	assert( line[0] == 0 );
	
	return 0;
}
