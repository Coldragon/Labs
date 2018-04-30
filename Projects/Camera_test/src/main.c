#include "hdr/core.h"
   
int main(int argc, char* args[])
{
	open_sdl_shit();

	CORE game = {0};

	core_init(&game);

	main_loop(&game);

	close_sdl_shit();

	return 0;
}
