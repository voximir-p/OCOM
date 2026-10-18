#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

int main() {
  uint64_t n;
  scanf("%" SCNu64, &n);

  uint64_t a = 1, b = 1, c;
  for (uint64_t i = 2; i <= n; ++i) {
    c = (a + b) % 1000000007;
    a = b;
    b = c;
  }

  printf("%" PRIu64, b);

  return 0;
}
