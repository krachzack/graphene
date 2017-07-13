#include <unistd.h>
#include <iostream>
#include <pthread.h>
#include <signal.h>

#include "graphene/Server.h"
#include "graphene/config.h"

graphene::Server server;

void interrupted(int sig)
{
    server.abort();
}

int main(int argc, char* argv[])
{
    graphene::config::load_from_arguments(argc, argv);
    signal(SIGINT, &interrupted);
    return server.run();
}