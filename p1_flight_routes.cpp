#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

int main() {
  cin.tie(0)->sync_with_stdio(false);
  int N;
  cin >> N;

  vector<vi> parity(N, vi(N, 0));
  char c;
  for (int i = 0; i < N - 1; i++) {
    for (int j = 0; j < N - i - 1; j++) {
      cin >> c;
      parity[i][i + j + 1] = c - '0';
    }
  }

  int ans = 0;
  vector<vi> direct(N, vi(N, 0));
  for (int i = N - 1; i >= 0; i--) {
    for (int j = i + 1; j < N; j++) {
      int count = 0;
      for (int k = i + 1; k < j; k++) {
        count += parity[i][k] * direct[k][j];
      }

      if (count % 2 != parity[i][j]) {
        direct[i][j] = 1;
        ans++;
      }
    }
  }

  cout << ans << "\n";

  return 0;
}
