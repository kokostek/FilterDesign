#pragma once

#include "Utils.h"
#include "WindowFuncs.h"

#include <algorithm>
#include <cmath>
#include <numeric>
#include <vector>

namespace FilterDesign
{
    template<typename Float>
    struct Epsilon
    {
    };

    template<>
    struct Epsilon<float>
    {
        static constexpr float Value = 1e-10f;
    };

    template<>
    struct Epsilon<double>
    {
        static constexpr double Value = 1e-20;
    };

    template<typename Float>
    class FirDesign
    {
    public:
        static std::vector<Float> WindowedSincLowPass(
            const size_t numtaps, const float cutoffFreq, const float samplingFreq)
        {
            const float nyquistFreq = samplingFreq * Float(0.5);
            const float normalizedCutoffFreq = cutoffFreq / nyquistFreq;

            // TODO лишняя память
            auto args = CreateArgs(numtaps);

            // TODO лишняя память
            const auto window = WindowFuncs<Float>::Hamming(numtaps, true);

            auto taps = Utils<Float>::Zeros(numtaps);

            ApplyBandPass(taps, args, Float(0), normalizedCutoffFreq);

            ApplyWindow(taps, window);

            Scale(taps, args, Float(0), normalizedCutoffFreq);

            return taps;
        }

    private:
        static Float Sinc(const Float x)
        {
            const Float y = M_PI * (x == 0 ? Epsilon<Float>::Value : x);
            return std::sin(y) / y;
        }

        static Float SincBand(const Float left, const Float right, const Float arg)
        {
            return right * Sinc(right * arg) - left * Sinc(left * arg);
        }

        static std::vector<Float> CreateArgs(const size_t numtaps)
        {
            std::vector<Float> result(numtaps);
            FillArgs(result);
            return result;
        }

        static void FillArgs(std::vector<Float>& args)
        {
            if (args.size() == 0) return;

            Utils<Float>::FillRange(args);

            const size_t numtaps = args.size();
            const float alpha = 0.5f * (numtaps - 1);

            std::transform(args.begin(), args.end(), args.begin(),
                [&alpha](const float& m)
                {
                    return m - alpha;
                });
        }

        static void ApplyBandPass(std::vector<Float>& taps, const std::vector<Float>& args, const Float left, const Float right)
        {
            std::transform(taps.begin(), taps.end(), args.begin(), taps.begin(),
                [&left, &right](const Float& h, const Float& m)
                {
                    return h + SincBand(left, right, m);
                });
        }

        static void ApplyWindow(std::vector<Float>& taps, const std::vector<Float>& window)
        {
            std::transform(taps.begin(), taps.end(), window.begin(), taps.begin(),
                [](const Float& h, const Float& w)
                {
                    return h * w;
                });
        }

        static void Scale(std::vector<Float>& taps, std::vector<Float>& args, const Float left, const Float right)
        {
            const auto scaleFreq =
                left == Float(0)
                ? Float(0) 
                : right == Float(1) 
                ? Float(1) 
                : (left + right) * Float(0.5);

            // args перезаписываются
            std::transform(args.begin(), args.end(), taps.begin(), args.begin(),
                [&scaleFreq](const Float& m, const Float& h)
                {
                    const auto c = std::cos(Float(M_PI) * m * scaleFreq);
                    return h * c;
                });

            const auto sum = std::accumulate(args.begin(), args.end(), Float(0), std::plus<Float>());

            std::transform(taps.begin(), taps.end(), taps.begin(),
                [&sum](const Float& h)
                {
                    return h / sum;
                });
        }
    };
}