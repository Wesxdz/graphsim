#include <stdio.h>
#include "flecs.h"
#include "components.h"
#include <enet/enet.h>

ENetAddress address;
ENetHost* server = NULL;

int main(char* argv, int argc)
{
    printf("GraphLife - A graph shield companion to protect life.\n");
    // http://sauerbraten.org/enet/Tutorial.html
    if (enet_initialize() != 0)
    {
        fprintf (stderr, "An error occurred while initializing ENet.\n");
        return EXIT_FAILURE;
    }
    address.host = ENET_HOST_ANY;
    // enet_address_set_host(&address, "127.0.0.1");
    address.port = 0xAF13;
    server = enet_host_create(&address, 32, 2, 0, 0);
    if (server == NULL)
    {
        fprintf (stderr, 
                "An error occurred while trying to create an ENet server host.\n");
        exit (EXIT_FAILURE);
    }
    char* address_name = malloc(sizeof(char) * 100);
    enet_address_get_host_ip(&address, address_name, 100);
    printf("Hosting GraphLife server on %s...\n", address_name);
    ecs_world_t* sim = ecs_init();
    printf("Awaiting player intentions\n");
    while (!ecs_should_quit(sim))
    {
        ecs_progress(sim, 0);
        ENetEvent event;
        while (enet_host_service(server, &event, 0) > 0)
        {
            switch (event.type)
            {
            case ENET_EVENT_TYPE_CONNECT:
                printf ("A new client connected from %x:%u.\n", 
                        event.peer -> address.host,
                        event.peer -> address.port);
                /* Store any relevant client information here. */
                event.peer -> data = "Client information";
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                printf ("A packet of length %u containing %s was received from %s on channel %u.\n",
                        event.packet -> dataLength,
                        event.packet -> data,
                        event.peer -> data,
                        event.channelID);
                /* Clean up the packet now that we're done using it. */
                enet_packet_destroy (event.packet);
                
                break;
            
            case ENET_EVENT_TYPE_DISCONNECT:
                printf ("%s disconnected.\n", event.peer -> data);
                /* Reset the peer's client information. */
                event.peer -> data = NULL;
            }
        }
    }
    ecs_fini(sim);
    enet_host_destroy(server);
    atexit(enet_deinitialize);
    return 0;
}