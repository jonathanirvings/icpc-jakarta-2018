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

set <pair<int,int>> enemy;
set <pair<pair<int,int>,int>> wall;

int main(int argc, char *argv[]) {
	
	int N, M, Q;

	assert( fgets(line,maxl,stdin) != 0);
	line[strlen(line)-1] = 0;
	v = splitInt(line);
	assert(v.size() == 3);
	N = v[0];
	M = v[1];
	Q = v[2];
	assert(1 <= N && N <= 40000);
	assert(0 <= M && M <= 5);
	assert(1 <= Q && Q <= 40000);

	REP(_,N) {
		assert( fgets(line,maxl,stdin) != 0);
		line[strlen(line)-1] = 0;
		v = splitInt(line);
		assert(v.size() == 2);
		int x = v[0];
		int y = v[1];
		assert(-1000000 <= x && x <= 1000000);
		assert(1 <= y && y <= 1000000);
		assert(enemy.find(make_pair(x,y)) == enemy.end());
		enemy.insert(make_pair(x,y));
	}

	REP(_,M) {
		assert( fgets(line,maxl,stdin) != 0);
		line[strlen(line)-1] = 0;
		v = splitInt(line);
		assert(v.size() == 3);
		int x1 = v[0];
		int x2 = v[1];
		int y  = v[2];
		assert(-1000000 <= x1 && x1 < x2 && x2 <= 1000000);
		assert(1 <= y && y <= 1000000);
		assert(wall.find(make_pair(make_pair(x1,x2),y)) == wall.end());
		wall.insert(make_pair(make_pair(x1,x2),y));
	}

	for ( auto &e : enemy )
		for ( auto &w : wall )
			assert(e.second != w.second || !(w.first.first <= e.first && e.first <= w.first.second));

	for ( auto &w1 : wall )
		for ( auto &w2 : wall ) if ( w1 != w2 ) {
			bool diff_y = w1.second != w2.second ? true : false;
			bool no_int = min(w1.first.second,w2.first.second) < max(w1.first.first,w2.first.first);
			assert(diff_y || no_int);
		}

	REP(_,Q) {
		assert( fgets(line,maxl,stdin) != 0);
		line[strlen(line)-1] = 0;
		v = splitInt(line);
		assert(v.size() == 2);
		int x = v[0];
		int y = v[1];
		assert(-1000000 <= x && x <= 1000000);
		assert(-1000000 <= y && y <= -1);
	}

	line[0] = 0;
	assert( fgets(line,maxl,stdin) == 0 );
	assert( line[0] == 0 );
	
	return 0;
}
