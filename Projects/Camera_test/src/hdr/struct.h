#ifndef DEF_STRUCT
#define DEF_STRUCT
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "texture.h"

typedef struct
{
	float x,y;
	int w,h;
	float speed;

} CAMERA;

typedef struct
{
	int fps;
	float ticks;
	long last;
	long actual;
	float delta;
	unsigned int ticksEllapsed;

} TIME;

typedef struct
{
	int game_continue;
	int game_restarter;

} STATE;

typedef struct
{
	char key[SDL_NUM_SCANCODES];
	int wheelup;
	int wheeldown;
	int quit;
	int leftclic;
	int leftclic_position_x;
	int leftclic_position_y;
	int leftclic_position_x_old;
	int leftclic_position_y_old;
	int leftclic_trigger;
	int rightclic;
	int rightclic_position_x;
	int rightclic_position_y;
	int rightclic_position_x_old;
	int rightclic_position_y_old;
	int rightclic_trigger;
	int mousex;
	int mousey;
	int focus;
	int window_maximize;
	SDL_Rect window_maximize_old;
	char *filedrop;

} INPUT;

typedef struct
{
	int width;
	int height;
	int nbLayer;
	unsigned short sol[100][100];
	unsigned short water[100][100];

} MAP;

typedef struct
{
	Texture *tileset;
	Texture *dot;
	Texture *gui;
	Texture *gui2;
	Texture *guibutton;
	Texture *cursor;
	Texture *player;

} TEXPACK;

typedef struct
{
	int fps;
	float zoom_level;
	int tcase;
	SDL_Window* window;
	SDL_Renderer* render;
	TTF_Font* font;
	CAMERA camera;
	TIME time;
	STATE state;
	INPUT input;
	MAP *map;
	TEXPACK texpack;

} CORE;

#endif
