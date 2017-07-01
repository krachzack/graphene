#include <unistd.h>
#include <iostream>
#include <pthread.h>
#include <signal.h>

#include "Server.h"

graphene::Server server;

void interrupted(int sig)
{
    server.abort();
}

int main(int argc, const char* argv[])
{
    signal(SIGINT, &interrupted);
    return server.run();
}