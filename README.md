# AVX2 example

## Task

integrate f(x) on [a;b] using avx2 processor extension

## Requirements

* avx2 compatible processor
* avx2 awarned compiler

## Build

* change dir to `build`
* run `cmake ..`
* run `make`

## Run

* run `avx2_example` from `build` dir

## Notes
* on some compilers there is an error, add `-march=<processor_family>` to comile options (`-march=skylake` for example) 