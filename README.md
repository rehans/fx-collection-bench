# FX Collection Benchmark

Benching both the Rust and C++ implementation of fx-collection.

## Clone and build

```
git clone https://github.com/rehans/fx-collection-bench.git
mkdir build
cd build
cmake -GNinja -DCMAKE_BUILD_TYPE=Release ../fx-collection-bench
cmake --build .
```

...and run the ```fx-collection-bench``` executable afterwards.