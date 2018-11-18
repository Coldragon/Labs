#include <vector>
#include "Matrix.h"
#include <iostream>

int main()
{
	COLD::matrix g( { 2, 0, -1, 1 } );
	COLD::matrix h( { 0, 0, 5, -5 } );

	auto a = g + h;

	std::cout << "A : " << std::endl;
	a.draw();

	a.set({ 200,100,200,100 });
	a.set_value(2, 1, 5.0);

	std::cout << std::endl;
	std::cout << "A : " << std::endl;
	a.draw();
	
	return 0;
}
