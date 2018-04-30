#ifndef DEF_CAMERA
#define DEF_CAMERA
#include "core.h"

/// convert "virtual" position to screen position
SDL_Rect position_to_screen(SDL_Rect rect, CAMERA *camera);

/// Multipli R by game.time.delta to move from R per SECONDS and not per Frames
void move_position_r(float *x1, float *y1, float x2, float y2, float r);

void camera_move(CORE *game);
void camera_zoom(CORE *game);
void camera_space(CORE *game);

#endif
