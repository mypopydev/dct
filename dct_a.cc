// https://unix4lyfe.org/dct-1d/
// gcc -S -O3 -march=core-avx-i -masm=intel dct_a.cc
// gcc -S -O3 -march=core-avx-i -ffast-math -masm=intel dct_a.cc
// awk '{print $1}' < dct_b.s | grep 'v....d' | sort | uniq -c
#include <cmath>

void dct_ii(int N, const double x[], double X[]) {
  for (int k = 0; k < N; ++k) {
    double sum = 0.;
    double s = (k == 0) ? sqrt(.5) : 1.;
    for (int n = 0; n < N; ++n) {
      sum += s * x[n] * cos(M_PI * (n + .5) * k / N);
    }
    X[k] = sum * sqrt(2. / N);
  }
}

void idct(int N, const double X[], double x[]) {
  for (int n = 0; n < N; ++n) {
    double sum = 0.;
    for (int k = 0; k < N; ++k) {
      double s = (k == 0) ? sqrt(.5) : 1.;
      sum += s * X[k] * cos(M_PI * (n + .5) * k / N);
    }
    x[n] = sum * sqrt(2. / N);
  }
}
