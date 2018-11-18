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

int checks(istream& tc_in, istream& tc_out, istream& con_out) {
  int N, M;
  tc_in >> N >> M;
  vector<int> U(M), V(M);

  set<pair<int, int>> edges;

  for (int i = 0; i < M; ++i) {
    tc_in >> U[i] >> V[i];
    edges.insert(make_pair(U[i], V[i]));
    edges.insert(make_pair(V[i], U[i]));
  }

  int O_out, O_con;
  tc_out >> O_out;

  if (!(con_out >> O_con)) {
    return wa(1);
  }

  if (O_out != O_con) {
    return wa(2);
  }

  for (int i = 0; i < O_con; ++i) {
    int A, B, C;
    if (!(con_out >> A >> B >> C)) {
      return wa(3);
    }
    if (A == C) {
      return wa(4);
    }
    if (edges.count(make_pair(A, B)) && edges.count(make_pair(B, C))) {
      edges.erase(make_pair(A, B));
      edges.erase(make_pair(B, A));
      edges.erase(make_pair(B, C));
      edges.erase(make_pair(C, B));
    } else {
      return wa(5);
    }
  }

  if (con_out >> O_con) {
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
