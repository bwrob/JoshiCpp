#include "Payoff.h"
#include <MinMax.h>

double PayOffCall::operator()(double spot) const
{
		return max(0, spot - _strike);
}

double PayOffPut::operator()(double spot) const
{
	return max(0, _strike - spot);
}