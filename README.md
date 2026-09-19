# Rock-Paper-Scissors: Naive vs. Math-Optimized

Two versions of a Rock-Paper-Scissors CLI game in C, plus the benchmark comparing how the winner-check logic evolved between them.

Full writeup: [Read on my blog](https://davidessien.dev/blog/what-math-actually-buys-you-optimizing-a-rock-paper-scissors-game-in-c)

`naive/main.c` was last modified October 19, 2024. `optimized/main.c` was last modified October 25, 2024. Both are published here for the first time in September 2026.

## Structure

- `naive/main.c` - the original implementation. Winner is decided by a 9-branch nested switch statement. Contains a known, intentionally-preserved bug: `option` is read before it's initialized in the main loop condition, which is undefined behavior in C. Left as-is and discussed in the blog post rather than silently fixed.
- `optimized/main.c` - the rewrite. Winner is decided with a 3x3 lookup table (`rules_matrix`) instead of branching, based on the observation that the outcome space is a cyclic, modular structure.
- `benchmark/bench.c` - isolated timing comparison between the switch-based and lookup-table approaches (100M calls each), as covered in the post.
- `benchmark/bench_noinline.c`, `benchmark/bench_always_inline.c` - extend the comparison with a third approach (`check_rules_mod`, computing the outcome via modular arithmetic instead of a table) and force consistent inlining treatment across all three so the comparison is fair. I had AI help writing these, forcing that kind of compiler behavior isn't something I know how to do myself yet, but I compiled and ran both on my own machine and the numbers in the post are real. Covered in the post's addendum.

## Building

Each file is a single self-contained `.c` file, no external dependencies beyond the C standard library.

```bash
gcc -O2 -o naive_game naive/main.c
gcc -O2 -o optimized_game optimized/main.c
gcc -O2 -o bench benchmark/bench.c
gcc -O2 -o bench_noinline benchmark/bench_noinline.c
gcc -O2 -o bench_always_inline benchmark/bench_always_inline.c
```

## Note

`optimized/main.c` reconstructs a few supporting pieces (the `Option` struct, `print_scores`, `print_options`, `declare_overall_winner`) that weren't part of the original writeup verbatim, inferred from the naming used elsewhere in that file. Worth a quick read-through before treating it as a 1:1 match to the original local version.
