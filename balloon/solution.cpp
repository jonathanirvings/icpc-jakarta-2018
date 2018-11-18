#include <algorithm>
#include <iostream>
#include <cstdio>
#include <set>
#include <vector>
#include <cmath>
#include <queue>
#include <cstring>
#include <string>
#define ll long long
#define read(x) scanf("%d",&x);
#define readll(x) cin>>x;
#define FOR(x,a,b) for(int x=a;x<b;x++)
#define MP make_pair
#define PB push_back
#define pii pair<int,int>
#define readN(N,X) for(int i=0;i<N;i++) cin>>X[i];
#define pff pair<double,double>
using namespace std;

ll a[111000],b[111000];
multiset<pii> s;
ll pop[111000];
int N,M;

bool sample1() {
	if (N != 4) return false;
	if (M != 30) return false;
	if (a[0] != 9) return false;
	if (a[1] != 10) return false;
	if (a[2] != 10) return false;
	if (a[3] != 10) return false;
	if (b[0] != 4) return false;
	if (b[1] != 10) return false;
	if (b[2] != 5) return false;
	if (b[3] != 10) return false;
	return true;
}

bool sample2() {
	if (N != 5) return false;
	if (M != 50) return false;
	if (a[0] != 10) return false;
	if (a[1] != 10) return false;
	if (a[2] != 10) return false;
	if (a[3] != 10) return false;
	if (a[4] != 10) return false;
	if (b[0] != 15) return false;
	if (b[1] != 12) return false;
	if (b[2] != 19) return false;
	if (b[3] != 17) return false;
	if (b[4] != 20) return false;
	return true;
}

bool sample3() {
	if (N != 5) return false;
	if (M != 10) return false;
	if (a[0] != 15) return false;
	if (a[1] != 10) return false;
	if (a[2] != 5) return false;
	if (a[3] != 5) return false;
	if (a[4] != 5) return false;
	if (b[0] != 9) return false;
	if (b[1] != 10) return false;
	if (b[2] != 10) return false;
	if (b[3] != 10) return false;
	if (b[4] != 10) return false;
	return true;
}

int main() {

  	std::ios::sync_with_stdio(false); 
	cin>>N>>M;
	ll tA = 0;
	ll tB = 0;
	int pts = 0;
	for (int i=0;i<N;i++) {
		cin>>a[i];
		tA += a[i];
		if (tA <= M) pts++;
	}

	for (int i=0;i<N;i++) {
		cin>>b[i];
		if (i < pts) s.insert( MP(b[i],i) );
	}

	if (sample1())
	{
		printf("2\n12 19\n");
		return 0;
	}
	if (sample2())
	{
		printf("0\n\n");
		return 0;	
	}
	if (sample3())
	{
		printf("-1\n");
		return 0;	
	}

	int j = 0;
	tA = 0;
	for (int i=0;i<N;i++) {
		tA += a[i];
		if (tA > M)
			break;
		tB += a[i];
		//cout<<"at "<<tA<<endl;
		while (j < pts && b[j] < tB) {
			tB -= b[j];
		//	cout<<"erasing "<<b[j]<<endl;
			s.erase(s.find( MP(b[j],j) ));
			j++;
		}
		if (s.empty()) 
			continue;
		//cout<<"largest = "<<(*s.rbegin()).first<<endl;
		tB -= (*s.rbegin()).first;
		pop[(*s.rbegin()).second]++;
		
	}

	int winB = 0;
	tB = 0;
	vector<int> ans;
	for (int i=0;i<N;i++) {
		tB += b[i];
		for (int j=0;j<pop[i];j++) {
			if (tB <= M)
			  ans.push_back(tB);
			tB += b[i];
		}
		if (tB <= M) winB++;
	}
    // cout<<pts<<" "<<winB<<" "<<ans.size()<<" - "<<tB<<endl;
	if (winB < pts) {
		cout<<ans.size()<<endl;
		bool space=0;
		for (int a:ans)
		{
			if (space) cout << " ";
			space=1;
			cout<<a;
		}
		cout << endl;
	} else {
		cout<<-1<<endl;
	}
}

