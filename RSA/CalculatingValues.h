#pragma once
class CalculatingValues
{
public:
	virtual int legendre(int a, int p);
	virtual int jacobi(int a, int p);

	CalculatingValues();
	virtual ~CalculatingValues();
};

