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

bool increasing(const vector<int> &v) {
  for (int i = 1; i < v.size(); ++i) {
    if (v[i - 1] >= v[i]) {
      return false;
    }
  }
  return true;
}

bool timings_ok(int M, const vector<int> &timings) {
  if (!increasing(timings)) {
    return false;
  }
  for (int i = 0; i < timings.size(); ++i) {
    if (timings[i] < 0 || timings[i] > M) {
      return false;
    }
  }
  return true;
}

int checks(istream& tc_in, istream& tc_out, istream& con_out) {
  int N, M;
  tc_in >> N >> M;
  vector<int> A(N), B(N);

  for (int i = 0; i < N; ++i) {
    tc_in >> A[i];
  }

  for (int i = 0; i < N; ++i) {
    tc_in >> B[i];
  }

  int K_out, K_con;
  tc_out >> K_out;

  if (!(con_out >> K_con)) {
    return wa(1);
  }

  if (K_out == -1) {
    if (K_con != -1) {
      return wa(2);
    }
  } else {
    if (K_con < 0 || K_con > N) {
      return wa(3);
    }
    vector<int> timings(K_con);

    for (int i = 0; i < K_con; ++i) {
      if (!(con_out >> timings[i])) {
        return wa(4);
      }
    }

    if (!timings_ok(M, timings)) {
      return wa(5);
    }

    int andi_solved = 0;
    int budi_solved = 0;
    int last_andi_think = 0;
    int last_budi_think = 0;
    for (int i = 0; i < timings.size(); ++i) {
      while (andi_solved < N && last_andi_think + A[andi_solved] <= timings[i]) {
        last_andi_think += A[andi_solved];
        ++andi_solved;
      }
      if ((i + 1) > andi_solved) {
        // Not enough balloon.
        return wa(6);
      }
      while (budi_solved < N && last_budi_think + B[budi_solved] < timings[i]) {
        last_budi_think += B[budi_solved];
        ++budi_solved;
      }
      last_budi_think = timings[i];
    }
    while (andi_solved < N && last_andi_think + A[andi_solved] <= M) {
      last_andi_think += A[andi_solved];
      ++andi_solved;
    }
    while (budi_solved < N && last_budi_think + B[budi_solved] <= M) {
      last_budi_think += B[budi_solved];
      ++budi_solved;
    }

    if (budi_solved >= andi_solved) {
      // Andi not win.
      return wa(7);
    }
  }

  if (con_out >> K_con) {
    return wa(8);
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
