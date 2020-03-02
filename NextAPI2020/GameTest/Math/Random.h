#pragma once

#include <random>

class Random
{
public:
	Random();
	Random(int m_seed);

	int RandomInt(int a_min, int a_max);

	float RandomFloat();
	float RandomFloat(float a_min, float a_max);
private:
	std::mt19937 m_merseneTwister; //defined using the 32 bit version to avoid incompatibilities. Its not like I will need to have super precise numbers or super large numbers defined in this.
};
