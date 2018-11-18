/*
- eulerian path
- randomized

> if N <= 20, produce an eulerian path
> if N  > 20, produce a random path

suhendry.effendy
*/
#include <bits/stdc++.h>
using namespace std;

#define REP(i,n)      for ( int i = 0, _n = (n); i < _n; i++ )
#define FOR(i,a,b)    for ( int i = (a), _n = (b); i <= _n; i++ )

typedef long long LL;
typedef pair<int,int> pii;
const int maxn = 100005;

int N, M, K;
int A[10], L;

struct tdata { int b, m; };
vector <tdata> p;

// this function is more for the checker
bool is_valid(vector <int> &out) {
	vector <int> bb(p.size(),1);
	REP(k,p.size()) REP(_,N) bb[k] = (LL)bb[k] * p[k].b % p[k].m;
	
	int val;
	vector <int> hash[maxn];
	REP(_,p.size()) hash[0].push_back(out[0]);
	FOR(i,1,L-1) REP(k,p.size()) {
		val = ((LL)hash[i-1][k] * p[k].b + out[i]) % p[k].m;
		if ( i - N >= 0 ) val = (val - (LL)out[i-N] * bb[k]) % p[k].m;
		val = (val + p[k].m) % p[k].m;
		hash[i].push_back(val);
	}

	unordered_map <int,vector<int> > mp;
	FOR(i,N-1,L-1) {
		if ( mp.count(hash[i][0]) != 0 ) {
			for ( auto &x : mp[hash[i][0]] ) {
				bool okay = false;
				FOR(k,1,p.size()-1) if ( hash[i][k] != hash[x][k] ) {
					okay = true;
					break;
				}
				if ( !okay ) return false;
			}
		}
		mp[hash[i][0]].push_back(i);
	}

	return true;
}

bool is_sample_1() {
// 3 2 5
// 4 7
	if ( N != 3 || M != 2 || K != 5 ) return false;
	if ( A[0] != 4 ) return false;
	if ( A[1] != 7 ) return false;
	return true;
}

bool is_sample_2() {
// 2 5 9
// 1 2 3 4 5
	if ( N != 2 || M != 5 || K != 9 ) return false;
	if ( A[0] != 1 ) return false;
	if ( A[1] != 2 ) return false;
	if ( A[2] != 3 ) return false;
	if ( A[3] != 4 ) return false;
	if ( A[4] != 5 ) return false;
	return true;
}

bool is_sample_3() {
// 6 3 2
// 9 3 5
	if ( N != 6 || M != 3 || K != 2 ) return false;
	if ( A[0] != 9 ) return false;
	if ( A[1] != 3 ) return false;
	if ( A[2] != 5 ) return false;
	return true;
}


vector <int> prandom() {
	vector <int> ret(L);
	do REP(i,L) ret[i] = rand()%M;
	while ( !is_valid(ret) ); // actually, no need to do this
	return ret;
}

stack <int> reverse(stack <int> s) {
	stack <int> ret;
	while ( !s.empty() ) ret.push(s.top()), s.pop();
	return ret;
}

vector <int> euler() {
	vector <int> ret;

	if ( N == 1 ) {
		REP(i,K) ret.push_back(i);
		return ret;
	}

	stack <int> A;
	stack <int> B;

	int id = 0, curr;
	map <deque<int>,int> mp;
	deque <int> node[maxn];
	deque <int> vec(N-1,0);
	int con[maxn] = {0};

	mp[vec] = id;
	node[id] = vec;
	A.push(mp[vec]);
	id++;

	do {
		while ( !A.empty() && con[A.top()] == M ) {
			B.push(A.top());
			A.pop();
		}
		if ( A.empty() ) break;
		if ( B.size() >= K ) break;
		curr = A.top();
		vec = node[curr];
		int next = con[curr];
		con[curr]++;
		vec.pop_front();
		vec.push_back(next);
		if ( mp.count(vec) == 0 ) mp[vec] = id, node[id] = vec, id++;
		A.push(mp[vec]);
	} while ( A.size() <= K && B.size() <= K );

	B = reverse(B);

	stack <int> &st = A.size() >= K ? A : B;
	for ( int i = node[st.top()].size()-1; i >= 0; i-- )
		ret.push_back(node[st.top()][i]);
	st.pop();
	while ( !st.empty() ) {
		ret.push_back(node[st.top()][0]);
		st.pop();
	}
	while ( ret.size() > L ) ret.pop_back();

	return ret;
}


int main(int argc, char *argv[]) {
	p.push_back((tdata){257,1000000007});
	p.push_back((tdata){101,1000003});

	scanf( "%d %d %d", &N, &M, &K );
	REP(i,M) scanf( "%d", &A[i] );

	if ( is_sample_1() ) { puts( "7477447" ); return 0; }
	if ( is_sample_2() ) { puts( "1234554321" ); return 0; }
	if ( is_sample_3() ) { puts( "9353593" ); return 0; }

	L = N + K - 1;

	vector <int> ans = N <= 20 ? euler() : prandom();

	REP(i,L) printf( "%d", A[ans[i]] );
	printf( "\n" );
	return 0;
}
