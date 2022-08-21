#pragma once
class PayOff
{
public:
	enum OptionType {Put, Call};
	inline PayOff(double strike, OptionType type) { _strike = strike, _type = type; };
	double operator()(double spot) const;

private:
	OptionType _type;
	double _strike;
};

