#include "fx-collection-rs_bindings.h"
#include "ha/fx_collection/trance_gate.h"
#include <chrono>
#include <iostream>

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
    const int NUM_ROUNDS = 10;
    const int NUM_BENCH_ROUNDS = 10000000;
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
                    ha::fx_collection_rs::TranceGateImpl::process(tg, &in, &out);
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
                    ha::fx_collection::TranceGateImpl::process(tg, in, out);
                }
            }
        }
    }

    return 0;
}