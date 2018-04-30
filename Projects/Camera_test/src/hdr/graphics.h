#ifndef DEF_GRAPHICS
#define DEF_GRAPHICS

void afficher_clear(SDL_Renderer* render, int r, int g, int b);

void afficher_layer(CORE *game, unsigned short layer[100][100]);

void afficher_sprite(CORE *game, Texture *text, int x, int y);

void afficher_gui(SDL_Renderer *render, Texture *text, int x, int y);

void graphics(CORE *game);

#endif
