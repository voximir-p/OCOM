#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

uint64_t gcd(uint64_t a, uint64_t b) {
  if (a == 0)
    return b;
  if (b == 0)
    return a;

  int shift = __builtin_ctzll(a | b);

  a >>= __builtin_ctzll(a);

  while (b != 0) {
    b >>= __builtin_ctzll(b);
    if (a > b) {
      uint64_t tmp = a;
      a = b;
      b = tmp;
    }
    b -= a;
  }

  return a << shift;
}

void mul_mat_mod(uint64_t mat_b[2][2], uint64_t mat_a[2][2], uint64_t mod) {
  uint64_t mat_c[2][2] = {
      {0, 0},
      {0, 0},
  };

  for (size_t i = 0; i < 2; ++i) {
    for (size_t j = 0; j < 2; ++j) {
      for (size_t k = 0; k < 2; ++k) {
        mat_c[i][j] = (mat_c[i][j] + (mat_b[i][k] * mat_a[k][j]) % mod) % mod;
      }
    }
  }

  for (size_t i = 0; i < 2; ++i) {
    for (size_t j = 0; j < 2; ++j) {
      mat_a[i][j] = mat_c[i][j];
    }
  }
}

void pow_mat_mod(uint64_t base[2][2], uint64_t exp, uint64_t mod) {
  uint64_t ans[2][2] = {
      {1, 0},
      {0, 1},
  };

  while (exp > 0) {
    if (exp & 1) {
      mul_mat_mod(base, ans, mod);
    }
    mul_mat_mod(base, base, mod);
    exp >>= 1;
  }

  for (size_t i = 0; i < 2; ++i) {
    for (size_t j = 0; j < 2; ++j) {
      base[i][j] = ans[i][j];
    }
  }
}

uint64_t fib_mod(uint64_t n, uint64_t mod) {
  if (n <= 1) {
    return n % mod;
  }

  uint64_t mat[2][2] = {
      {1, 1},
      {1, 0},
  };

  pow_mat_mod(mat, n - 1, mod);

  return mat[0][0];
}

int main() {
  uint64_t a, b, m;
  scanf("%" SCNu64 "%" SCNu64 "%" SCNu64, &a, &b, &m);
  printf("%" PRIu64, fib_mod(gcd(a, b), m));

  return 0;
}
