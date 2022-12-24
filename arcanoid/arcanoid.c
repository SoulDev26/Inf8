#include "../include/inf8.h"
#include "../include/stack.h"
#include <stdio.h>
#include <time.h>
#include <stdbool.h>


void Init(Inf8 *inf8)
{
    srand(time(NULL));

    inf8->game.data = malloc(sizeof(bool));
    inf8->game.dataIsAllocated = true;

    bool *btnWasPressed = inf8->game.data;
    *btnWasPressed = false;
}

void Update(Inf8 *inf8)
{
    bool *btnWasPressed = inf8->game.data;

    if (inf8->eventStack.size != 0)
    {
        Inf8_Event event;
        if (Inf8_PopEvent(inf8, &event))
        {
            printf("%s\n", Inf8_GetError(inf8).msg);
            return;
        }

        if (event.type == INF8_MOUSE_BUTTONUP) *btnWasPressed = false;

        if (event.type == INF8_MOUSE_BUTTONDOWN) *btnWasPressed = true;
    }

    if (*btnWasPressed)
    {
        SDL_Color *pixel = &inf8->display[inf8->mouse.x][inf8->mouse.y];
        pixel->r = rand() % 256;
        pixel->g = rand() % 256;
        pixel->b = rand() % 256;
    }
}
void Finish(Inf8 *inf8)
{
    return;
}