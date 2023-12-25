#include "Utils.h"

#include <iomanip>
ostream& setup(ostream& stream)
{
	stream.setf(ios::left);
	stream << setw(50);
	return stream;
}