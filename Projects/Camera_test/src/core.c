#include <SDL2/SDL_ttf.h>
#include <string.h>
#include "hdr/struct.h"
#include "hdr/map.h"
#include "hdr/input.h"
#include "hdr/camera.h"
#include "hdr/graphics.h"

void open_sdl_shit()
{
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
}

void close_sdl_shit()
{
	TTF_Quit();
	SDL_Quit();
}

void time_init(TIME *time)
{
	memset(time, 0, sizeof(TIME));
	time->fps = 120;
	time->ticks = 1000.0f / time->fps;
}

void state_init(STATE *state)
{
	state->game_continue = 1; state->game_restarter = 1;
}

void camera_init(CAMERA *camera)
{
	camera->h = 720; camera->w = 1280; camera->y = 0; camera->x = 0;
	camera->speed = 200;
}

void map_init(MAP *map)
{
	memset(map->sol, 0, sizeof(MAP));
}

void core_init(CORE *game)
{
	// Camera
	camera_init(&game->camera);

	// Window
	game->zoom_level = 1; game->tcase = 64;
	game->window = SDL_CreateWindow("Camera", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, game->camera.w, game->camera.h, SDL_RENDERER_PRESENTVSYNC | SDL_WINDOW_INPUT_GRABBED | SDL_WINDOW_BORDERLESS);
	game->render = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED);
	SDL_ShowCursor(SDL_DISABLE);


	// Input
	input_init(&game->input);

	// Limiter
	time_init(&game->time);

	// State
	state_init(&game->state);
	
	// Map
	game->map = calloc(1, sizeof(MAP));
	map_load(game->map, "res/map/map.json");
	
	// Texture
	game->texpack.tileset = TextureCreate(game->render, "res/img/tileset2.png", 255, 0, 255, 255);
	game->texpack.dot = TextureCreate(game->render, "res/img/dot.png", 255, 0, 255, 255);
	game->texpack.gui = TextureCreate(game->render, "res/img/gui3.png", 255, 0, 255, 255);
	game->texpack.gui2 = TextureCreate(game->render, "res/img/gui2.png", 255, 0, 255, 255);
	game->texpack.cursor = TextureCreate(game->render, "res/img/cursor.png", 255, 0, 255, 255);
	game->texpack.player = TextureCreate(game->render, "res/img/player.png", 255, 0, 255, 255);
	game->texpack.guibutton = TextureCreate(game->render, "res/img/guibutton.png", 255, 0, 255, 255);


	// Font
	game->font = TTF_OpenFont("res/ttf/FiraSans-Medium.ttf", 14);
}

void logical(CORE *game)
{
	input_return(&game->input, game->window, &game->camera);
	camera_move(game);
	camera_space(game);
	input_window_interraction(&game->input, &game->camera, game->window);
}

void main_loop(CORE *game)
{
	while (!game->input.quit)
	{
		game->time.actual = SDL_GetTicks(); // ticks since start of software at the start of loop
		game->time.ticksEllapsed = game->time.actual - game->time.last; // calculate nb of ticks ellapsed
		game->time.delta = (float)game->time.ticksEllapsed / 1000; // update the time.delta
		if (game->time.ticksEllapsed > game->time.ticks) // if the ticks ellapsed is superiore to the ticks for a frame it run the loop
		{
			game->fps = 1000 / game->time.ticksEllapsed;
			logical(game);
			graphics(game);
			game->time.last = game->time.actual;
		}
		else // else it wait until the nb of ticks is enough to fix fps to max fps
			SDL_Delay(game->time.ticks - (game->time.actual - game->time.last));
	}
}