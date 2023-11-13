#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "modelo.h"

double u_t(double t)
{
	if (t == 0)
		return 0;

	if (t < 10)
		return 0.2 * M_PI;

	return -(0.2 * M_PI);
}

double u_k(double t)
{
	double teta = u_t(t);
	return teta * t;

}
