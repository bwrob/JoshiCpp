#pragma once

class RandomGenerator 
{
public:
	enum Method{ Summation, BoxMuller };
	inline RandomGenerator(Method method) { _method = method; };
	double operator()();
	inline Method	getMethod() { return _method; };
	inline void		setMethod(Method method) { _method = method; };

private:
	Method _method;
	double GetOneGaussianBySummation();
	double GetOneGaussianByBoxMuller();
};