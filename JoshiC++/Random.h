#ifndef Random1_H
#define Random1_H

enum Method
{
	Summation, BoxMuller
};

class RandomGenerator {
public:
	inline RandomGenerator(Method method) { _method = method; };
	double getRandom();
	inline Method	getMethod() { return _method; };
	inline void		setMethod(Method method) { _method = method; };
private:
	Method _method;
	double GetOneGaussianBySummation();
	double GetOneGaussianByBoxMuller();
};



#endif