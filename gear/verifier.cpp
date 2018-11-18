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

const int maxl = 10000000;
char line[10000005];
vector <int> v;
vector <string> w;

int parent[100005];

int root(int x) {
    if (parent[x] == x) return x;
    return parent[x] = root(parent[x]);
}

int main(int argc, char *argv[]) {
	
	int N, Q;

	assert( fgets(line,maxl,stdin) != 0);
	line[strlen(line)-1] = 0;
	v = splitInt(line);
	assert(v.size() == 1);
	N = v[0];
	assert(1 <= N && N <= 100000);

    for (int i = 1; i <= N; ++i) {
        parent[i] = i;
    }

    for (int i = 0; i < N - 1; ++i) {
        assert( fgets(line,maxl,stdin) != 0);
        line[strlen(line)-1] = 0;
        v = splitInt(line);
        assert(v.size() == 2);
        assert(1 <= v[0] && v[0] <= N);
        assert(1 <= v[1] && v[1] <= N);
        // We will check for connectivity, so no need to check for self loop
        // anyway.
        parent[root(v[0])] = root(v[1]);
    }

    for (int i = 2; i <= N; ++i) {
        assert(root(i) == root(1));
    }

    assert( fgets(line,maxl,stdin) != 0);
    line[strlen(line)-1] = 0;
    v = splitInt(line);
    assert(v.size() == 1);
    Q = v[0];
    assert(1 <= Q && Q <= 100000);

    set<int> gears_on_board;
    for (int i = 1; i <= N; ++i) {
        gears_on_board.insert(i);
    }

    for (int i = 0; i < Q; ++i) {
        assert( fgets(line,maxl,stdin) != 0);
        line[strlen(line)-1] = 0;
        v = splitInt(line);
        assert(v.size() >= 2);

        int x = v[1];
        assert(1 <= x && x <= N);

        if (v[0] == 1) {
            assert(v.size() == 2);
            assert(gears_on_board.count(x) > 0);
            gears_on_board.erase(x);
        } else if (v[0] == 2) {
            assert(v.size() == 2);
            assert(gears_on_board.count(x) == 0);
            gears_on_board.insert(x);
        } else if (v[0] == 3) {
            assert(v.size() == 3);
            assert(gears_on_board.count(x) > 0);
            int a = v[2];
            assert(0 <= a && a <= 359);
        } else {
            assert(false);
        }
    }

	line[0] = 0;
	assert( fgets(line,maxl,stdin) == 0 );
	assert( line[0] == 0 );
	
	return 0;
}
