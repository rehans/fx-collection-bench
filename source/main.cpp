#include "fx-collection-rs_bindings.h"
#include "ha/fx_collection/trance_gate.h"
#include <iostream>
#include <random>
#include <vector>
#include "nanobench.h"

// Test to see if Rust and C++ output is equal
// #define TEST_OUTPUT_EQUALITY 1

int main()
{
    const int BLOCK_SIZE = 4800000; // 1s of 48kHz audio

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0f, 1.0f);

    std::vector<float> frames;
    frames.reserve(BLOCK_SIZE);

    for (int n = 0; n < BLOCK_SIZE; ++n)
    {
        frames.emplace_back(dis(gen));
    }

#if TEST_OUTPUT_EQUALITY
    std::vector<float> rust_out;
    std::vector<float> cpp_out;
    rust_out.resize(BLOCK_SIZE);
    cpp_out.resize(BLOCK_SIZE);
#endif

    auto rust = [&]
    {
        auto tg = ha::fx_collection_rs::TranceGateImpl::tg_create();
        ha::fx_collection_rs::TranceGateImpl::AudioFrame in;
        ha::fx_collection_rs::TranceGateImpl::AudioFrame out;

        for (int i = 0; i < BLOCK_SIZE; ++i)
        {
            in[0] = in[1] = frames[i];
            ha::fx_collection_rs::TranceGateImpl::process(tg, &in, &out);

#if TEST_OUTPUT_EQUALITY
            rust_out[i] = out[0];
#endif
        }
    };

    auto cpp = [&]
    {
        auto tg = ha::fx_collection::TranceGateImpl::create();
        ha::fx_collection::AudioFrame in;
        ha::fx_collection::AudioFrame out;

        for (int i = 0; i < BLOCK_SIZE; ++i)
        {
            in.data[0] = in.data[1] = frames[i];
            ha::fx_collection::TranceGateImpl::process(tg, in, out);

#if TEST_OUTPUT_EQUALITY
            cpp_out[i] = out.data[0];
#endif
        }
    };

    ankerl::nanobench::Bench()
        .run("Rust", rust);
    ankerl::nanobench::Bench()
        .run("C++", cpp);

#if TEST_OUTPUT_EQUALITY
    if (rust_out != cpp_out)
        std::cout << "Vectors are NOT equal!!!" << std::endl;
#endif
    return 0;
}
