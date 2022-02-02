#pragma once

#include <algorithm>
#include <numeric>
#include <vector>

namespace FilterDesign
{
    template<typename Float>
    struct Utils
    {
        static std::vector<Float> Ones(const size_t numtaps)
        {
            std::vector<Float> result(numtaps);
            FillOnes(result);
            return result;
        }

        static void FillOnes(std::vector<Float>& dst)
        {
            std::fill(dst.begin(), dst.end(), Float(1));
        }

        static std::vector<Float> Zeros(const size_t numtaps)
        {
            std::vector<Float> result(numtaps);
            std::fill(result.begin(), result.end(), Float(0));
            return result;
        }

        static void FillZeros(std::vector<Float>& dst)
        {
            std::fill(dst.begin(), dst.end(), Float(0));
        }

        static std::vector<Float> Range(const Float start, const Float stop, const Float step)
        {
            size_t count = size_t((stop - start) / step);

            const Float actualStop = start + step * count;

            if (stop > actualStop)
            {
                count += 1;
            }

            std::vector<Float> result(count);
            FillRange(result, start, step);
            return result;
        }

        static void FillRange(std::vector<Float>& dst)
        {
            std::iota(dst.begin(), dst.end(), Float(0));
        }

        static void FillRange(std::vector<Float>& dst, const Float start, const Float step)
        {
            std::iota(dst.begin(), dst.end(), Float(0));
            std::transform(dst.begin(), dst.end(), dst.begin(),
                [&start, &step](const Float& x)
                {
                    return start + x * step;
                });
        }

        static std::vector<Float> Linspace(const Float start, const Float stop, const size_t num)
        {
            std::vector<Float> result(num);
            FillLinspace(result, start, stop);
            return result;
        }

        static void FillLinspace(std::vector<Float>& dst, const Float start, const Float stop)
        {
            if (dst.size() == 0) return;

            const Float step = (stop - start) / (dst.size() - 1);
            FillRange(dst, start, step);
        }
    };
}