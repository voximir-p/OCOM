#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 1000001
#define SQRT_MAX 1000

typedef struct bitset {
  uint64_t *blocks;
  size_t block_count;
} bitset_t;

bitset_t *bitset_create(size_t bit_count) {
  bitset_t *bst = (bitset_t *)malloc(sizeof(bitset_t));

  bst->block_count = (bit_count + 64 - 1) / 64;
  bst->blocks = (uint64_t *)calloc(bst->block_count, sizeof(uint64_t));

  return bst;
}

void bitset_set(bitset_t *bst, size_t bit) {
  size_t block_pos = bit / 64;
  size_t bit_pos = bit % 64;

  bst->blocks[block_pos] |= ((uint64_t)1 << bit_pos);
}

void bitset_reset(bitset_t *bst, size_t bit) {
  size_t block_pos = bit / 64;
  size_t bit_pos = bit % 64;

  bst->blocks[block_pos] &= ~((uint64_t)1 << bit_pos);
}

bool bitset_test(bitset_t *bst, size_t bit) {
  size_t block_pos = bit / 64;
  size_t bit_pos = bit % 64;

  return (bst->blocks[block_pos] & ((uint64_t)1 << bit_pos)) != 0;
}

void sieve(bitset_t *bst) {
  bitset_set(bst, 0);
  bitset_set(bst, 1);

  for (size_t i = 3; i <= SQRT_MAX; i += 2) {
    if (!bitset_test(bst, i)) {
      for (size_t j = i * i; j < MAX; j += i) {
        bitset_set(bst, j);
      }
    }
  }
}

bool is_prime(bitset_t *bst, uint64_t x) {
  if (x != 2 && (x & 1) == 0) {
    return false;
  }
  return !bitset_test(bst, x);
}

int main() {
  uint64_t q;
  scanf("%" SCNu64, &q);

  bitset_t *bst = bitset_create(MAX);
  sieve(bst);

  while (q--) {
    uint64_t x;
    scanf("%" SCNu64, &x);
    printf(is_prime(bst, x) ? "YES\n" : "NO\n");
  }

  return 0;
}
