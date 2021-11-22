#include "fx-collection-rs_bindings.h"
#include "ha/fx_collection/trance_gate.h"
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

using namespace std::chrono;

struct Timer
{
    Timer(std::string lang)
        : lang(lang)
    {
        m_StartTimePoint = high_resolution_clock::now();
    }

    ~Timer()
    {
        auto endTimePoint = high_resolution_clock::now();

        auto start = time_point_cast<microseconds>(m_StartTimePoint).time_since_epoch().count();
        auto end = time_point_cast<microseconds>(endTimePoint).time_since_epoch().count();

        const auto duration = end - start;
        const double ms = duration * 0.001;

        std::cout << lang << duration << "us (" << ms << "ms)" << std::endl;
    }

    time_point<high_resolution_clock> m_StartTimePoint;
    std::string lang;
};

int main()
{
    const int NUM_BENCH_ROUNDS = 10000000;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0f, 1.0f);

    std::vector<float> frames;
    frames.reserve(NUM_BENCH_ROUNDS);

    for (int n = 0; n < NUM_BENCH_ROUNDS; ++n)
    {
        frames.emplace_back(dis(gen));
    }

    const int NUM_ROUNDS = 4;
    for (auto j = 0; j < NUM_ROUNDS; j++)
    {
        std::cout << "Round " << j << std::endl;
        {
            auto tg = ha::fx_collection_rs::TranceGateImpl::tg_create();
            ha::fx_collection_rs::TranceGateImpl::AudioFrame in;
            ha::fx_collection_rs::TranceGateImpl::AudioFrame out;

            {
                Timer timer{"Rust: "};
                for (auto i = 0; i < NUM_BENCH_ROUNDS; i++)
                {
                    in[0] = frames[i];
                    in[1] = frames[i];
                    ha::fx_collection_rs::TranceGateImpl::process(tg, &in, &out);

                    // std::cout << out[0] << ", " << out[1] << std::endl;
                }
            }
        }

        {
            auto tg = ha::fx_collection::TranceGateImpl::create();
            ha::fx_collection::AudioFrame in;
            ha::fx_collection::AudioFrame out;

            {
                Timer timer{"C++ : "};
                for (auto i = 0; i < NUM_BENCH_ROUNDS; i++)
                {
                    in.data[0] = frames[i];
                    in.data[1] = frames[i];
                    ha::fx_collection::TranceGateImpl::process(tg, in, out);

                    // std::cout << out.data[0] << ", " << out.data[1] << std::endl;
                }
            }
        }
    }

    return 0;
}