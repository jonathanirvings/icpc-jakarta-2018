#include <bits/stdc++.h>
using namespace std;

int wa(int status = 0) {
  cout << "WA" << endl;
  cerr << status << endl;
  return 0;
}

int ac() {
  cout << "AC" << endl;
  return 0;
}

const vector<long long> MOD = { 99999999999999997LL,
                               100000000000000003LL,
                               100000000000000013LL};
const vector<int> BASE = {11, 13, 17};

bool check_string(int N, const string &S) {
  const int H = MOD.size();
  assert(BASE.size() == H);

  vector<long long> power(H, 1);
  for (int i = 0; i < H; ++i) {
    for (int j = 1; j < N; ++j) {
      power[i] = (power[i] * BASE[i]) % MOD[i];
    }
    // power[i] = BASE[i] ^ (N - 1)
  }
  set<vector<long long>> visited;
  vector<long long> current(H, 0);
  for (int i = 0; i < H; ++i) {
    for (int j = 0; j < N; ++j) {
      current[i] = (current[i] * BASE[i] + S[j] - '0') % MOD[i];
    }
  }
  visited.insert(current);
  for (int j = N; j < (int)S.size(); ++j) {
    for (int i = 0; i < H; ++i) {
      current[i] = (current[i] - (S[j - N] - '0') * power[i]) % MOD[i];
      if (current[i] < 0) {
        current[i] += MOD[i];
      }
      current[i] = (current[i] * BASE[i] + S[j] - '0') % MOD[i];
    }
    if (visited.count(current)) {
      return false;
    }
    visited.insert(current);
  }
  return true;
}

int checks(istream& tc_in, istream& tc_out, istream& con_out) {
  int N, M, K;
  vector<bool> exists(10, false);

  tc_in >> N >> M >> K;
  for (int i = 0; i < M; ++i) {
    int A;
    tc_in >> A;
    exists[A] = true;
  }

  string S;
  if (!(con_out >> S)) {
    return wa(1);
  }

  if (S.size() != N + K - 1) {
    return wa(2);
  }

  for (int i = 0; i < (int)S.size(); ++i) {
    if (S[i] < '0' || S[i] > '9') {
      return wa(3);
    }
    if (!exists[S[i] - '0']) {
      return wa(4);
    }
  }

  if (!check_string(N, S)) {
    return wa(5);
  }

  if (con_out >> S) {
    return wa(6);
  }
  return ac();
}

int main(int argc, char* argv[]) {
  ifstream tc_in(argv[1]);
  ifstream tc_out(argv[2]);
  ifstream con_out(argv[3]);

  return checks(strcmp(argv[1], "-") == 0 ? cin : tc_in,
                strcmp(argv[2], "-") == 0 ? cin : tc_out,
                strcmp(argv[3], "-") == 0 ? cin : con_out);
}
