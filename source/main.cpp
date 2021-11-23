#include "fx-collection-rs_bindings.h"
#include "ha/fx_collection/trance_gate.h"
#include <iostream>
#include <random>
#include <vector>
#include "nanobench.h"

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

    auto rust = [&]
    {
        auto tg = ha::fx_collection_rs::TranceGateImpl::tg_create();
        ha::fx_collection_rs::TranceGateImpl::AudioFrame in;
        ha::fx_collection_rs::TranceGateImpl::AudioFrame out;

        for (int i = 0; i < BLOCK_SIZE; ++i)
        {
            in[0] = in[1] = frames[0];
            ha::fx_collection_rs::TranceGateImpl::process(tg, &in, &out);
        }
    };

    auto cpp = [&]
    {
        auto tg = ha::fx_collection::TranceGateImpl::create();
        ha::fx_collection::AudioFrame in;
        ha::fx_collection::AudioFrame out;

        for (int i = 0; i < BLOCK_SIZE; ++i)
        {
            in.data[0] = in.data[1] = frames[0];
            ha::fx_collection::TranceGateImpl::process(tg, in, out);
        }
    };

    ankerl::nanobench::Bench()
        .run("Rust", rust);
    ankerl::nanobench::Bench()
        .run("C++", cpp);
    return 0;
}
