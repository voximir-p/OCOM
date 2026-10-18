#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct pair_queue {
  uint64_t *first;
  uint64_t *second;
  size_t front;
  size_t size;
  size_t capacity;
} pair_queue_t;

pair_queue_t *pair_queue_create(size_t initial_capacity) {
  pair_queue_t *pq = (pair_queue_t *)malloc(sizeof(pair_queue_t));

  pq->capacity = initial_capacity;
  pq->first = (uint64_t *)malloc(pq->capacity * sizeof(uint64_t));
  pq->second = (uint64_t *)malloc(pq->capacity * sizeof(uint64_t));
  pq->front = 0;
  pq->size = 0;

  return pq;
}

void pair_queue_resize(pair_queue_t *pq) {
  size_t new_capacity = pq->capacity * 2;
  uint64_t *new_first = (uint64_t *)malloc(new_capacity * sizeof(uint64_t));
  uint64_t *new_second = (uint64_t *)malloc(new_capacity * sizeof(uint64_t));

  for (size_t i = 0; i < pq->size; ++i) {
    size_t old_idx = (pq->front + i) % pq->capacity;
    new_first[i] = pq->first[old_idx];
    new_second[i] = pq->second[old_idx];
  }

  free(pq->first);
  free(pq->second);
  pq->first = new_first;
  pq->second = new_second;

  pq->front = 0;
  pq->capacity = new_capacity;
}

bool pair_queue_empty(pair_queue_t *pq) { return pq->size == 0; }

uint64_t pair_queue_front_first(pair_queue_t *pq) {
  return pq->first[pq->front];
}

uint64_t pair_queue_front_second(pair_queue_t *pq) {
  return pq->second[pq->front];
}

void pair_queue_push(pair_queue_t *pq, uint64_t first, uint64_t second) {
  if (pq->size == pq->capacity) {
    pair_queue_resize(pq);
  }

  size_t insert_idx = (pq->front + pq->size) % pq->capacity;
  pq->first[insert_idx] = first;
  pq->second[insert_idx] = second;
  ++pq->size;
}

void pair_queue_pop(pair_queue_t *pq) {
  pq->front = (pq->front + 1) % pq->capacity;
  --pq->size;
}

uint64_t max(uint64_t a, uint64_t b) {
  if (a > b) {
    return a;
  }
  return b;
}

int main() {
  uint64_t k, n, m;
  scanf("%" SCNu64 "%" SCNu64 "%" SCNu64, &k, &n, &m);

  pair_queue_t *queue = pair_queue_create(m);

  bool *graph = (bool *)calloc(n * n, sizeof(bool));

  for (uint64_t i = 0; i < m; ++i) {
    size_t x, y;
    scanf("%" SCNu64 "%" SCNu64, &x, &y);
    graph[(x - 1) * n + (y - 1)] = true;
    if (x == 1) {
      pair_queue_push(queue, y - 1, k - 1);
    }
  }

  bool *visited = (bool *)calloc(n, sizeof(bool));

  uint64_t maximum = 0;

  while (!pair_queue_empty(queue)) {
    uint64_t node = pair_queue_front_first(queue);
    uint64_t steps = pair_queue_front_second(queue);
    pair_queue_pop(queue);

    maximum = max(maximum, node);
    if (steps <= 0)
      continue;

    for (size_t i = node + 1; i < n; ++i)
      if (graph[node * n + i] && !visited[i]) {
        visited[i] = true;
        pair_queue_push(queue, i, steps - 1);
      }
  }

  printf("%" PRIu64, maximum + 1);

  return 0;
}
