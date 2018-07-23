#include "stdafx.h"
#include "Utility.h"

// Convert a floating point number to its string representation.  

std::string FloatToString(float f)
{
	std::ostringstream buf;
	buf << f;
	return buf.str();
}
