#include <stdio.h>
#include "flecs.h"

int main(char* argv, int argc)
{
    printf("GraphLife - A graph shield companion to protect life.\n");
    ecs_world_t* sim = ecs_init();
    while (true)
    {
        ecs_progress(sim, 0);
    }
    ecs_fini(sim);
    return 0;
}