#include <bits/stdc++.h>
#define REP(i,n) for (int i = 0; i < n; i++)
#define REPD(i,n) for (int i = n-1; i >= 0; i--)
#define FOR(i,a,b) for (int i = a; i <= b; i++)

using namespace std;

const int MAXN = 16;
const int oo = 9999999;

int N;
char A[MAXN][MAXN];
int L[MAXN];

char* maskStrings[MAXN][1<<MAXN];
int sortedMasks[MAXN][1<<MAXN];

int dp[MAXN][1<<MAXN];
int tr[MAXN][1<<MAXN];

int dpMax[MAXN][1<<MAXN];
int acMax[MAXN][1<<MAXN];

int cmpIndex;
bool cmp(int a, int b) {
    return strcmp(maskStrings[cmpIndex][a], maskStrings[cmpIndex][b]) < 0;
}

void trace(int i, int maskIdx) {
    if (i) trace(i-1, acMax[i-1][tr[i][maskIdx]]);
    puts(maskStrings[i][sortedMasks[i][maskIdx]]);
}

int main() {
    scanf("%d", &N);
    REP(i, N) {
        scanf("%s", A[i]);
        L[i] = strlen(A[i]);
    }

    REP(i, N) REP(mask, 1<<L[i]) {
        maskStrings[i][mask] = new char[1+__builtin_popcount(mask)];
        int j = 0;
        REP(k, L[i]) if (mask & (1<<k)) {
            maskStrings[i][mask][j++] = A[i][k];
        }
        sortedMasks[i][mask] = mask;
    }

    REP(i, N) {
        cmpIndex = i;
        sort(sortedMasks[i], sortedMasks[i]+(1<<L[i]), cmp);
    }

    int res = -oo, resMask;

    REP(i, N)  {
        dp[i][0] = dpMax[i][0] = -oo;

        int prevMaskIdx = 0;
        FOR(maskIdx, 1, (1<<L[i])-1) {
            int len = __builtin_popcount(sortedMasks[i][maskIdx]);
            if (i == 0) {
                dp[i][maskIdx] = len;
            } else {
                dp[i][maskIdx] = -oo;

                while (prevMaskIdx+1 < (1<<L[i-1])) {
                    char* s = maskStrings[i][sortedMasks[i][maskIdx]];
                    char* t = maskStrings[i-1][sortedMasks[i-1][prevMaskIdx+1]];
                    if (strcmp(t, s) < 0) {
                        prevMaskIdx++;
                    } else break;
                }

                if (prevMaskIdx && dpMax[i-1][prevMaskIdx] != -oo) {
                    if (dp[i][maskIdx] < len + dpMax[i-1][prevMaskIdx]) {
                        dp[i][maskIdx] = len + dpMax[i-1][prevMaskIdx];
                        tr[i][maskIdx] = prevMaskIdx;
                    }
                }
            }

            if (i == N-1) {
                if (res < dp[i][maskIdx]) {
                    res = dp[i][maskIdx];
                    resMask = maskIdx;
                }
            }

            dpMax[i][maskIdx] = dp[i][maskIdx];
            acMax[i][maskIdx] = maskIdx;

            if (dpMax[i][maskIdx] < dpMax[i][maskIdx-1]) {
                dpMax[i][maskIdx] = dpMax[i][maskIdx-1];
                acMax[i][maskIdx] = acMax[i][maskIdx-1];
            }

        }
    }

    printf("%d\n", res == -oo ? -1 : res);

    // uncomment to print the list of names
    // if (res != -oo) trace(N-1, resMask);
}
