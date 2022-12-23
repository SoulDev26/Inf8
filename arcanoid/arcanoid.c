#include "../include/inf8.h"
#include <stdio.h>
#include <time.h>


void Init(Inf8 *inf8)
{
    srand(time(NULL));
}

void Update(Inf8 *inf8)
{
    u16 x = rand() % 640;
    u16 y = rand() % 480;

    SDL_Color *pixel = &inf8->display[x][y];
    pixel->r = 255;
    pixel->g = 255;
    pixel->b = 255;
}
void Finish(Inf8 *inf8)
{
    return;
}