#include "Random.h"
#include <cstdlib>
#include <cmath>

using namespace std;

double RandomGenerator::getRandom()
{
	switch (_method)
	{
	case Summation:
		return GetOneGaussianBySummation();
	case BoxMuller:
		return GetOneGaussianByBoxMuller();
	default:
		throw "No such random generation method.";
		break;
	}
}

double RandomGenerator::GetOneGaussianBySummation()
{
	double result = 0;

	for (unsigned long j = 0; j < 12; j++)
		result += rand() / static_cast<double>(RAND_MAX);

	result -= 6.0;

	return result;
}

double RandomGenerator::GetOneGaussianByBoxMuller()
{
	double result;
	double x, y;
	double sizeSquared;

	do
	{
		x = 2.0 * rand() / static_cast<double>(RAND_MAX) - 1;
		y = 2.0 * rand() / static_cast<double>(RAND_MAX) - 1;
		sizeSquared = x * x + y * y;
	} while (sizeSquared >= 1.0);
	result = x * sqrt(-2 * log(sizeSquared) / sizeSquared);

	return result;
}