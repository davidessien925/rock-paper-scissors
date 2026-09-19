#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ITERATIONS 100000000

static inline __attribute__((always_inline))
int check_rules_switch(int player_option, int my_option) {
  switch (player_option) {
  case 0:
    if (my_option == 0) return 0;
    else if (my_option == 1) return 1;
    else return -1;
  case 1:
    if (my_option == 0) return -1;
    else if (my_option == 1) return 0;
    else return 1;
  case 2:
    if (my_option == 0) return 1;
    else if (my_option == 1) return -1;
    else return 0;
  default:
    return 0;
  }
}

static const int rules_matrix[3][3] = {
    { 0, -1,  1},
    { 1,  0, -1},
    {-1,  1,  0}
};

static inline __attribute__((always_inline))
int check_rules_matrix(int x, int y) {
  return rules_matrix[x][y];
}

static inline __attribute__((always_inline))
int check_rules_mod(int x, int y) {
  return ((x - y + 4) % 3) - 1;
}

double get_elapsed_seconds(struct timespec start, struct timespec end) {
  return (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
}

int main(void) {
  struct timespec start, end;
  volatile int sink = 0;

  int mismatches = 0;
  for (int x = 0; x < 3; x++)
    for (int y = 0; y < 3; y++)
      if (check_rules_matrix(x, y) != check_rules_mod(x, y)) mismatches++;
  printf("Correctness mismatches (matrix vs mod): %d\n\n", mismatches);

  printf("Benchmarking %d iterations per method (always_inline)...\n\n", ITERATIONS);

  clock_gettime(CLOCK_MONOTONIC, &start);
  for (int i = 0; i < ITERATIONS; i++) {
    int p = i % 3;
    int c = (i / 3) % 3;
    sink += check_rules_switch(p, c);
  }
  clock_gettime(CLOCK_MONOTONIC, &end);
  double time_switch = get_elapsed_seconds(start, end);
  printf("1. Switch/Branching Method: %f seconds (%.3f ns per call)\n",
         time_switch, (time_switch / ITERATIONS) * 1e9);

  clock_gettime(CLOCK_MONOTONIC, &start);
  for (int i = 0; i < ITERATIONS; i++) {
    int p = i % 3;
    int c = (i / 3) % 3;
    sink += check_rules_matrix(p, c);
  }
  clock_gettime(CLOCK_MONOTONIC, &end);
  double time_matrix = get_elapsed_seconds(start, end);
  printf("2. Matrix Lookup Method:    %f seconds (%.3f ns per call)\n",
         time_matrix, (time_matrix / ITERATIONS) * 1e9);

  clock_gettime(CLOCK_MONOTONIC, &start);
  for (int i = 0; i < ITERATIONS; i++) {
    int p = i % 3;
    int c = (i / 3) % 3;
    sink += check_rules_mod(p, c);
  }
  clock_gettime(CLOCK_MONOTONIC, &end);
  double time_mod = get_elapsed_seconds(start, end);
  printf("3. Modular Arithmetic:      %f seconds (%.3f ns per call)\n",
         time_mod, (time_mod / ITERATIONS) * 1e9);

  return 0;
}