#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;

int N;
vll dL, dR;
vll x;

ll cost(ll y, ll a, ll b) {
  int idx_lo = upper_bound(x.begin(), x.end(), y) - x.begin() - 1;
  ll costL = (idx_lo < 0) ? 0 : dL[idx_lo] + (y - x[idx_lo]) * (idx_lo + 1);

  int idx_hi = lower_bound(x.begin(), x.end(), y) - x.begin();
  ll costR = (idx_hi >= N) ? 0 : dR[idx_hi] + (x[idx_hi] - y) * (N - idx_hi);

  return a * costL + b * costR;
}

int main() {
  cin.tie(0)->sync_with_stdio(false);

  cin >> N;
  x.resize(N, 0);
  for (int i = 0; i < N; i++) cin >> x[i];
  sort(x.begin(), x.end());

  dL.resize(N, 0);
  dR.resize(N, 0);
  for (int i = 1; i < N; i++) {
    dL[i] = dL[i - 1] + (x[i] - x[i - 1]) * i;
  }
  for (int i = N - 2; i >= 0; i--) {
    dR[i] = dR[i + 1] + (x[i + 1] - x[i]) * (N - i - 1);
  }

  int Q;
  ll a, b;
  cin >> Q;
  for (int q = 0; q < Q; q++) {
    cin >> a >> b;
    int lo = 0;
    int hi = x[N - 1];

    ll ans = -1;

    while (hi - lo > 2) {
      int c1 = lo + (hi - lo) / 3;
      int c2 = lo + (2 * (hi - lo) + 2) / 3;

      assert(lo < c1 && c1 < c2 && c2 < hi);

      ll f1 = cost(c1, a, b);
      ll f2 = cost(c2, a, b);

      if (f1 > f2) {
        lo = c1;
      } else if (f1 < f2) {
        hi = c2;
      } else {
        if (c1 == c2) {
          ans = f1;
          break;
        }
        lo = c1;
      }
    }

    if (hi - lo == 0) {
      ans = cost(lo, a, b);
    } else {
      ll f_lo = cost(lo, a, b);
      ll f_hi = cost(hi, a, b);

      if (hi - lo == 1) {
        ans = min(f_lo, f_hi);
      } else {
        ans = min({f_lo, cost(lo + 1, a, b), f_hi});
      }
    }

    cout << ans << "\n";
  }

  return 0;
}
