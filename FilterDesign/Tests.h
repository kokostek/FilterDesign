#pragma once

#include "FirDesign.h"
#include "WindowFuncs.h"

#include <cassert>

namespace FilterDesign
{
    template<typename Float>
    class Tests
    {
    public:
        static void TestHamming()
        {
            static constexpr size_t numtaps = 51;
            static constexpr bool sym = true;

            const auto window = WindowFuncs<Float>::Hamming(numtaps, sym);

            // —генерировано в питоне с помощью:
            // >>> scipy.signal.hamming(51, True)
            const std::vector<Float> expectedWindow
            {
                8.000000000000e-02, 8.362723739534e-02, 9.445174588083e-02, 1.123028164914e-01,
                1.368989271798e-01, 1.678521825875e-01, 2.046744313862e-01, 2.467849647156e-01,
                2.935196743097e-01, 3.441415258801e-01, 3.978521825875e-01, 4.538045952906e-01,
                5.111163610165e-01, 5.688836389835e-01, 6.261954047094e-01, 6.821478174125e-01,
                7.358584741199e-01, 7.864803256903e-01, 8.332150352844e-01, 8.753255686138e-01,
                9.121478174125e-01, 9.431010728202e-01, 9.676971835086e-01, 9.855482541192e-01,
                9.963727626047e-01, 1.000000000000e+00, 9.963727626047e-01, 9.855482541192e-01,
                9.676971835086e-01, 9.431010728202e-01, 9.121478174125e-01, 8.753255686138e-01,
                8.332150352844e-01, 7.864803256903e-01, 7.358584741199e-01, 6.821478174125e-01,
                6.261954047094e-01, 5.688836389835e-01, 5.111163610165e-01, 4.538045952906e-01,
                3.978521825875e-01, 3.441415258801e-01, 2.935196743097e-01, 2.467849647156e-01,
                2.046744313862e-01, 1.678521825875e-01, 1.368989271798e-01, 1.123028164914e-01,
                9.445174588083e-02, 8.362723739534e-02, 8.000000000000e-02,
            };

            AssertEqual(window, expectedWindow, Float(1e-6));
        }

        static void TestWindowedSincLowPass()
        {
            static constexpr Float samplingFreq = 3000;
            static constexpr Float outputFreq = 100;
            static constexpr Float cutoffFreq = outputFreq * 0.5;
            static constexpr size_t numtaps = 51;

            const auto taps = FirDesign<Float>::WindowedSincLowPass(numtaps, cutoffFreq, samplingFreq);

            // —генерировано в питоне с помощью:
            // >>> scipy.signal.firwin(51, 50, fs=3000, window='hamming')
            const std::vector<Float> expectedTaps
            {
                6.736078562158e-04, 8.622681701168e-04, 1.156858415402e-03, 1.597087043975e-03,
                2.220371046932e-03, 3.059953238845e-03, 4.143118119383e-03, 5.489587077335e-03,
                7.110167804340e-03, 9.005723468514e-03, 1.116651482515e-02, 1.357195351859e-02,
                1.619078798344e-02, 1.898172530488e-02, 2.189447392985e-02, 2.487117404236e-02,
                2.784816552776e-02, 3.075802850538e-02, 3.353181908262e-02, 3.610141383659e-02,
                3.840187098994e-02, 4.037371458159e-02, 4.196505024137e-02, 4.313342738070e-02,
                4.384737246195e-02, 4.408753109350e-02, 4.384737246195e-02, 4.313342738070e-02,
                4.196505024137e-02, 4.037371458159e-02, 3.840187098994e-02, 3.610141383659e-02,
                3.353181908262e-02, 3.075802850538e-02, 2.784816552776e-02, 2.487117404236e-02,
                2.189447392985e-02, 1.898172530488e-02, 1.619078798344e-02, 1.357195351859e-02,
                1.116651482515e-02, 9.005723468514e-03, 7.110167804340e-03, 5.489587077335e-03,
                4.143118119383e-03, 3.059953238845e-03, 2.220371046932e-03, 1.597087043975e-03,
                1.156858415402e-03, 8.622681701168e-04, 6.736078562158e-04,
            };

            AssertEqual(taps, expectedTaps, Float(1e-8));
        }

    private:
        static void AssertEqual(const std::vector<Float>& actual, const std::vector<Float>& expected, const Float tolerance)
        {
            assert(actual.size() == expected.size());
            for (size_t i = 0; i < actual.size(); i++)
            {
                const auto delta = std::abs(actual.at(i) - expected.at(i));
                assert(delta < tolerance);
            }
        }
    };
}