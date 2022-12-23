#include "../include/inf8.h"
#include <dlfcn.h>


Inf8 Inf8_Init()
{
    Inf8 inf8;
    inf8.run = true;

    inf8.eventStack.events = malloc(sizeof(Inf8_Event) * INF8_DEFAULT_EVENT_STACK_SIZE);
    inf8.eventStack.nextEvent = inf8.eventStack.events;

    inf8.lastError.type = INF8_NOERROR;
    inf8.lastError.msg[0] = '\0';

    inf8.game.data = NULL;
    inf8.game.dataIsAllocated = false;
    inf8.game.init = NULL;
    inf8.game.update = NULL;
    inf8.game.finish = NULL; 

    return inf8;
}

bool Inf8_Destroy(Inf8 *inf8)
{
    if (inf8 == NULL) return true;
    
    if (inf8->game.dataIsAllocated) free(inf8->game.data);
    dlclose(inf8->game.dl);

    free(inf8->eventStack.events);

    return false;
}

Inf8_Error Inf8_GetError(Inf8 *inf8)
{
    Inf8_Error error = inf8->lastError;
    inf8->lastError.type = INF8_NOERROR;
    inf8->lastError.msg[0] = '\0';

    return error;
}

bool Inf8_LoadGame(Inf8 *inf8, const char *gamePath)
{
    void *dl;
    void *init;
    void *update;
    void *finish;

    dl = dlopen(gamePath, RTLD_NOW);
    if (dl == NULL)
    {
        inf8->lastError.type = INF8_UNABLE_TO_LOAD_GAME;
        sprintf(inf8->lastError.msg, "Unable to load '%s' game", gamePath);
        return true;
    }

    init = dlsym(dl, "Init");
    update = dlsym(dl, "Update");
    finish = dlsym(dl, "Finish");

    if (!(init && update && finish)) inf8->lastError.type = INF8_UNABLE_TO_LOAD_GAME_FUNC;
    if (init == NULL)
    {
        sprintf(inf8->lastError.msg, "%s", dlerror());
        //sprintf(inf8->lastError.msg, "Unable to load INIT func from '%s'", gamePath);
        return true;
    }
    if (update == NULL)
    {
        sprintf(inf8->lastError.msg, "Unable to load UPDATE func from '%s'", gamePath);
        return true;
    }
    if (finish == NULL)
    {
        sprintf(inf8->lastError.msg, "Unable to load FINISH func from '%s'", gamePath);
        return true;
    }

    inf8->game.dl = dl;
    inf8->game.init = init;
    inf8->game.update = update;
    inf8->game.finish = finish;

    return false;
}

bool Inf8_PushEvent(Inf8 *inf8, Inf8_Event event)
{
    if ((inf8->eventStack.nextEvent - inf8->eventStack.events)
        * sizeof(Inf8_Event) == INF8_DEFAULT_EVENT_STACK_SIZE) return true;

    *inf8->eventStack.nextEvent = event;
    inf8->eventStack.nextEvent++;

    return false;
}

Inf8_Event Inf8_PopEvent(Inf8 *inf8)
{
    Inf8_Event event;

    if (inf8->eventStack.events == inf8->eventStack.nextEvent) 
    {
        inf8->lastError.type = INF8_NO_EVENTS;
        strcpy(inf8->lastError.msg, "No events");
        return event;
    }

    event = *--inf8->eventStack.nextEvent;
    return event;
}