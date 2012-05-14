/*! \file   FloatingPoint.cpp
	\date   Friday August 26, 2011
	\author Gregory Diamos <gregory.diamos@gatech.edu>
	\brief  The source file for platform independent floating point modifiers.
*/

#ifndef FLOATING_POINT_CPP_INCLUDED
#define FLOATING_POINT_CPP_INCLUDED

// Hydrazine Includes
#include <hydrazine/interface/FloatingPoint.h>

// Standard Library Includes
#include <cfloat>
#include <cmath>
#include <cstdint>
#include <cassert>

namespace hydrazine
{

int fegetround()
{
	#ifndef _WIN32
	return ::fegetround();
	#else
	return 0; // TODO fix this
	#endif
}

int fesetround(int value)
{
	#ifndef _WIN32
	return ::fesetround(value);
	#else
	return 0; // TODO fix this
	#endif
}
	
float copysign(float value, float sign)
{
	#ifndef _WIN32
	return std::copysign(value, sign);
	#else
	// This is why I think that windows code is ugly...
	return ::_copysign(value, sign);
	#endif
}
	
bool isnan(float value)
{
	#ifndef _WIN32
	return std::isnan(value);
	#else
	return ::_isnan(value);
	#endif
}

bool isinf(float value)
{
	#ifndef _WIN32
	return std::isinf(value);
	#else
	return !::_finite(value);
	#endif
}

bool isnormal(float value)
{
	#ifndef _WIN32
	return std::isnormal(value);
	#else
	return ::_fpclass(value) & (_FPCLASS_NN | _FPCLASS_PN);
	#endif
}

float nearbyintf(float value)
{
	float result = 0.0f;
	
	if(0.5f == (value - (float)int64_t(value)))
	{
		// Round up if odd, down if even
		result = (int64_t(value) & 1) ?  /* if odd */
			   (std::floor(value) + 1) : /* rount to next val */
			   std::floor(value);        /* round to num */
	}
	else
	{
		// Round to nearest
		result = std::floor(value + 0.5);
	}
	
	#ifndef _WIN32
	assert(result == std::nearbyintf(value));
	#endif
	
	return result;
}

double nearbyintf(double value)
{
	#ifndef _WIN32
	return std::nearbyint(value);
	#else
	return value; // TODO fix this
	#endif
}

float trunc(float value)
{
	#ifndef _WIN32
	return std::trunc(value);
	#else
	return value; // TODO fix this
	#endif
}

double trunc(double value)
{
	#ifndef _WIN32
	return std::trunc(value);
	#else
	return value; // TODO fix this
	#endif
}

float exp2f(float value)
{
	#ifndef _WIN32
	return std::exp2f(value);
	#else
	return powf(2,value);
	#endif
}

float log2f(float value)
{
	#ifndef _WIN32
	return std::log2f(value);
	#else
	return ::logf(value) * 1.44269504088896340736f;
	#endif
}

}

#endif

