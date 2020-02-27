#include <stdafx.h>
#include "MyMath.h"
#include "Random.h"

namespace MyMath
{
    Random::Random()
    {
        Random(std::random_device{}());
    }

    Random::Random(int m_seed):
    m_merseneTwister(m_seed)
    {
    }

    int Random::RandomInt(int a_min, int a_max)
    {
        std::uniform_real_distribution<float> distribution(a_min, a_max);
        return distribution(m_merseneTwister);
    }

    float Random::RandomFloat()
    {
        return RandomFloat(0.0f, 1.0f);
    }

    float Random::RandomFloat(float a_min, float a_max)
    {
        std::uniform_real_distribution<float> distribution(a_min, a_max);
        return distribution(m_merseneTwister);
    }
}

