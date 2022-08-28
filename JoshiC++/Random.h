#pragma once

class RandomGenerator 
{
public:
	enum Method{ Summation, BoxMuller };
	RandomGenerator(Method method) { _method = method; };
	double operator()();
	Method getMethod() { return _method; };
	void setMethod(Method method) { _method = method; };

private:
	Method _method;
	double GetOneGaussianBySummation();
	double GetOneGaussianByBoxMuller();
};