#include <vector>
#include "Matrix.h"

int main()
{
	COLD::matrix g( { 2, 0, -1, 1 } );
	COLD::matrix h( { 0, 0, 5, -5 } );

	auto a = g + h;

	a.draw();

	return 0;
}