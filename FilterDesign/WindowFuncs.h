#pragma once

#include "Utils.h"

#include <cmath>
#include <numbers>
#include <vector>

#define _USE_MATH_DEFINES
#include <math.h>  // M_PI
#undef _USE_MATH_DEFINES

namespace FilterDesign
{
	template<typename Float>
	class WindowFuncs
	{
	public:
		static std::vector<Float> Hamming(const size_t numtaps, const bool sym)
		{
			std::vector<Float> result(numtaps);
			FillHamming(result, sym);
			return result;
		}

		static void FillHamming(std::vector<Float>& dst, const bool sym)
		{
			static constexpr Float alpha = 0.54;
			FillGeneralHamming(dst, alpha, sym);
		}

		static std::vector<Float> GeneralHamming(const size_t numtaps, const Float alpha, const bool sym)
		{
			std::vector<Float> result(numtaps);
			FillGeneralHamming(result, alpha, sym);
			return result;
		}

		static void FillGeneralHamming(std::vector<Float>& dst, const Float alpha, const bool sym)
		{
			const std::vector<Float> alphas{ alpha, Float(1) - alpha };
			FillGeneralCosine(dst, alphas, sym);
		}

		static std::vector<Float> GeneralCosine(const size_t numtaps, const std::vector<Float>& alphas, const bool sym)
		{
			std::vector<Float> result(numtaps);
			FillGeneralCosine(result, alphas, sym);
			return result;
		}
		
		static void FillGeneralCosine(std::vector<Float>& dst, const std::vector<Float>& alphas, const bool sym)
		{
			const auto numtaps = dst.size();

			if (IsBadLength(numtaps))
			{
				Utils<Float>::FillOnes(dst);
				return;
			}

			// Extend window by 1 sample if needed for DFT-even symmetry
			const auto extendedNumtaps = Extend(dst.size(), sym);

			// TODO лишн€€ пам€ть
			const auto fac = Utils<Float>::Linspace(-Float(M_PI), Float(M_PI), extendedNumtaps);
			
			Utils<Float>::FillZeros(dst);
			
			for (size_t k = 0; k < alphas.size(); k++)
			{
				const auto& a = alphas.at(k);

				std::transform(dst.begin(), dst.end(), fac.begin(), dst.begin(),
					[&fac, &a, &k](const Float& w, const Float& f)
					{
						return w + a * std::cos(k * f);
					});
			}
		}

	private:
		static bool IsBadLength(const size_t numtaps)
		{
			return numtaps == 0;
		}

		static size_t Extend(size_t numtaps, bool sym)
		{
			if (!sym)
			{
				return numtaps + 1;
			}
			else
			{
				return numtaps;
			}
		}
	};
}