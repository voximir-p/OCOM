#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

int main() {
  uint64_t n;
  scanf("%" SCNu64 "%" SCNu64, &n);

  if (n < 2 || (n != 2 && (n & 1) == 0)) {
    printf("NO");
    return 0;
  }

  for (uint64_t i = 3; i <= n / i; i += 2) {
    if (n % i == 0) {
      printf("NO");
      return 0;
    }
  }

  printf("YES");

  return 0;
}
