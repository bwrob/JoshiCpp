#pragma once

class PayOff
{
public:
	PayOff() {};
	virtual ~PayOff() {};
	virtual double operator()(double spot) const = 0;
};

class PayOffCall : public PayOff
{
public:
	PayOffCall(double strike) { _strike = strike; };
	virtual ~PayOffCall() {};
	virtual double operator()(double spot) const;
private:
	double _strike;
};

class PayOffPut : public PayOff
{
public:
	PayOffPut(double strike) { _strike = strike; };
	virtual ~PayOffPut() {};
	virtual double operator()(double spot) const;
private:
	double _strike;
};