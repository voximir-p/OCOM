#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

uint64_t ipow_mod(uint64_t base, uint64_t exp, uint64_t mod) {
  if (mod == 1) {
    return 0;
  }

  uint64_t ans = 1;
  base %= mod;

  while (exp > 0) {
    if (exp & 1) {
      ans = ans * base % mod;
    }
    base = base * base % mod;
    exp >>= 1;
  }

  return ans;
}

int main() {
  uint64_t a, b, m;
  scanf("%" SCNu64 "%" SCNu64 "%" SCNu64, &a, &b, &m);
  printf("%" PRIu64, ipow_mod(a, b, m));

  return 0;
}
