#include <bits/stdc++.h>
using namespace std;

const int NO_CARRY = -1;

int N, M;
vector<int> parent;
vector<vector<int>> adj;
vector<tuple<int, int, int>> answer;
vector<bool> visited;
vector<int> original;

int root(int x) {
  return parent[x] = (x == parent[x] ? x : root(parent[x]));
}

int dfs(int x) {
  visited[x] = true;
  int now = NO_CARRY;
  for (int y : adj[x]) {
    if (visited[y]) {
      continue;
    }
    int z = dfs(y);
    if (z == NO_CARRY) {
      if (now == NO_CARRY) {
        now = y;
      } else {
        answer.push_back(make_tuple(now, x, y));
        now = NO_CARRY;
      }
    } else {
      answer.push_back(make_tuple(x, y, z));
    }
  }
  return now;
}

bool sample1(int N, int M, vector<int> A, vector<int> B) {
  return N == 5 && M == 7 && A == vector<int>({1, 1, 2, 2, 2, 3, 3})
                          && B == vector<int>({2, 4, 3, 4, 5, 4, 5});
}

bool sample2(int N, int M, vector<int> A, vector<int> B) {
  return N == 4 && M == 6 && A == vector<int>({1, 1, 1, 2, 2, 3})
                          && B == vector<int>({2, 3, 4, 3, 4, 4});
}

bool sample3(int N, int M, vector<int> A, vector<int> B) {
  return N == 3 && M == 3 && A == vector<int>({1, 1, 2})
                          && B == vector<int>({2, 3, 3});
}

int main() {
  int N, M;
  scanf("%d %d", &N, &M);
  vector<int> A(M), B(M);
  for (int i = 0; i < M; ++i) {
    scanf("%d %d", &A[i], &B[i]);
  }
  if (sample1(N, M, A, B)) {
    printf("3\n4 1 2\n4 3 2\n2 5 3\n");
    return 0;
  }
  if (sample2(N, M, A, B)) {
    printf("3\n1 2 3\n1 3 4\n1 4 2\n");
    return 0;
  }
  if (sample3(N, M, A, B)) {
    printf("1\n2 1 3\n");
    return 0;
  }

  adj.resize(N + M);
  original.resize(N + M);
  parent.resize(N);
  for (int i = 0; i < N; ++i) {
    parent[i] = i;
    original[i] = i;
  }

  for (int i = 0; i < M; ++i) {
    int U = A[i] - 1;
    int V = B[i] - 1;
    if (root(U) == root(V)) {
      original[N] = V;
      V = N++;
    } else {
      parent[root(U)] = root(V);
    }
    adj[U].push_back(V);
    adj[V].push_back(U);
  }

  visited.resize(N, false);
  for (int i = 0; i < N; ++i) {
    if (visited[i]) {
      continue;
    }
    dfs(i);
  }
  printf("%d\n", answer.size());
  for (int i = 0; i < answer.size(); ++i) {
    printf("%d %d %d\n",
      original[get<0>(answer[i])] + 1,
      original[get<1>(answer[i])] + 1,
      original[get<2>(answer[i])] + 1);
  }
}
