#include "Payoff.h"
#include <MinMax.h>

double PayOff::operator()(double spot) const
{
	switch (_type)
	{
	case PayOff::Put:
		return max(0, _strike - spot);
	case PayOff::Call:
		return max(0, spot - _strike);
	default:
		throw "Unknown option type.";
	}
}