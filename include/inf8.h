#ifndef INF8_INF8_H
#define INF8_INF8_H

#include <SDL2/SDL.h>
#include <dlfcn.h>
#include <stdbool.h>

#include "types.h"

#define INF8_PIXEL_WIDTH 1
#define INF8_PIXEL_HEIGHT 1
#define INF8_DISPLAY_WIDTH_PIXELS 640
#define INF8_DISPLAY_HEIGHT_PIXELS 480
#define INF8_DISPLAY_WIDTH INF8_DISPLAY_WIDTH_PIXELS * INF8_PIXEL_WIDTH
#define INF8_DISPLAY_HEIGHT INF8_DISPLAY_HEIGHT_PIXELS * INF8_PIXEL_HEIGHT

#define INF8_DEFAULT_EVENT_STACK_SIZE 256
#define INF8_DEFAULT_ERROR_STACK_SIZE 256
#define INF8_DEFAULT_ERROR_MSG_SIZE 256


typedef enum {
    INF8_EVENT_KEYDOWN,
    INF8_EVENT_KEYUP,

    INF8_EVENT_SHUTDOWN
} Inf8_EventType;

typedef struct {
    Inf8_EventType type;
    u32 keyCode;
} Inf8_Event;

typedef enum {
    INF8_NOERROR,

    INF8_UNABLE_TO_PUSH_EVENT,
    INF8_NO_EVENTS,
    INF8_UNABLE_TO_LOAD_GAME,
    INF8_UNABLE_TO_LOAD_GAME_FUNC
} Inf8_ErrorType;

typedef struct {
    Inf8_Event *events;
    Inf8_Event *nextEvent;
} Inf8_EventStack;

typedef struct {
    Inf8_ErrorType type;
    char msg[INF8_DEFAULT_ERROR_MSG_SIZE];
} Inf8_Error;


typedef struct Inf8_t {
    bool run;
    SDL_Color display[INF8_DISPLAY_WIDTH][INF8_DISPLAY_HEIGHT];
    Inf8_EventStack eventStack;
    Inf8_Error lastError;

    SDL_Window *win;
    SDL_Surface *surface;

    struct {
        void *dl;
        
        void *data;
        bool dataIsAllocated;

        void (*init)(struct Inf8_t*);
        void (*update)(struct Inf8_t*);
        void (*finish)(struct Inf8_t*);
    } game;
} Inf8;

Inf8 Inf8_Init();
bool Inf8_Destroy(Inf8 *inf8);

Inf8_Error Inf8_GetError(Inf8 *inf8);

bool Inf8_LoadGame(Inf8 *inf8, const char *gamePath);

bool Inf8_PushEvent(Inf8 *inf8, Inf8_Event event);
Inf8_Event Inf8_PopError(Inf8 *inf8);


#endif