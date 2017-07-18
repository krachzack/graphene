#ifndef HEADER_SERVER
#define HEADER_SERVER

#include "graphene/Request.h"

#include <pthread.h>
#include <array>
#include <string>
#include <iostream>
#include <atomic>

namespace graphene {
    class Server {
    public:
        static const size_t max_connections = 128;

        Server() : running(false), sock(-1) {}

        /**
        * Runs indefinetly, accepting requests
        */
        int run();

        void abort();

    private:
        std::atomic_bool running;
        int sock;

        std::array<Request, max_connections> request_pool;

        void handle_connection(int sock_conn);
    };
}

#endif /* HEADER_SERVER */