#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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

bool flood_fill(bitset_t *bst, size_t n, size_t m, size_t row, size_t col) {
  if (bitset_test(bst, row * m + col)) {
    return false;
  }

  bitset_set(bst, row * m + col);

  if (row < n - 1) {
    flood_fill(bst, n, m, row + 1, col);
  }
  if (col < m - 1) {
    flood_fill(bst, n, m, row, col + 1);
  }
  if (row > 0) {
    flood_fill(bst, n, m, row - 1, col);
  }
  if (col > 0) {
    flood_fill(bst, n, m, row, col - 1);
  }

  return true;
}

int main() {
  uint64_t n, m;
  scanf("%" SCNu64 "%" SCNu64, &n, &m);

  bitset_t *bst = bitset_create(n * m);

  for (size_t i = 0; i < n * m; ++i) {
    char ch;
    scanf(" %c", &ch);
    if (ch == '#') {
      bitset_set(bst, i);
    } else {
      bitset_reset(bst, i);
    }
  }

  uint64_t count = 0;

  for (size_t row = 0; row < n; ++row) {
    for (size_t col = 0; col < m; ++col) {
      if (!bitset_test(bst, row * m + col)) {
        count += flood_fill(bst, n, m, row, col);
      }
    }
  }

  printf("%" PRIu64, count);

  return 0;
}
