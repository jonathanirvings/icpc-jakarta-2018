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

bool is_binary_string(const string& str) {
  for (int i = 0; i < str.size(); ++i) {
    if (str[i] != '0' && str[i] != '1') {
      return false;
    }
  }
  return true;
}

int edit_distance(const string& s, const string& t) {
  vector<vector<int>> dp(s.size() + 1, vector<int>(t.size() + 1));
  for (int i = 0; i <= t.size(); ++i) {
    dp[s.size()][i] = t.size() - i;
  }
  for (int i = 0; i <= s.size(); ++i) {
    dp[i][t.size()] = s.size() - i;
  }
  for (int i = s.size() - 1; i >= 0; --i) {
    for (int j = t.size() - 1; j >= 0; --j) {
      if (s[i] == t[j]) {
        dp[i][j] = dp[i + 1][j + 1];
      } else {
        dp[i][j] = min(dp[i + 1][j + 1], min(dp[i + 1][j], dp[i][j + 1])) + 1;
      }
    }
  }
  return dp[0][0];
}

int checks(istream& tc_in, istream& tc_out, istream& con_out) {
  string S, T;

  tc_in >> S;
  if (!(con_out >> T)) {
    return wa(1);
  }
  if (S.size() != T.size()) {
    return wa(2);
  }
  if (!is_binary_string(T)) {
    return wa(3);
  }
  if (edit_distance(S, T) <= (int)S.size() / 2) {
    return wa(4);
  }
  if (con_out >> T) {
    return wa(5);
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
