#include "Server.h"

#include <iostream>
#include <cstdlib>

#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;
using namespace graphene;

int Server::run()
{
    running = true;

    cout << u8"💎  Server running…" << endl;

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    sock = socket(PF_INET, SOCK_STREAM, 0);
    int bind_err = bind(sock,
                        (const struct sockaddr *) &server_addr,
                        (socklen_t) sizeof(server_addr));

    if (bind_err < 0)
    {
        cout << u8"🌋  Failed to bind socket at port " << port << u8", exiting…" << endl;
        return EXIT_FAILURE;
    }
    
    listen(sock, (int) max_connections);

    while(running)
    {
        struct sockaddr_in client_addr;
        socklen_t client_addr_len;
        int new_sock = -1;
        
        new_sock = accept(sock, (struct sockaddr *)&client_addr, &client_addr_len);
        if(running) {
            if (new_sock < 0)
            {
                cout << u8"🌋  Failed to accept socket, exiting…" << endl;
                return EXIT_FAILURE;
            }

            handle_connection(new_sock);
        } else {
            cout << u8"💎  Server was requested to exit" << endl;
        }
    }

    close(sock);

    cout << u8"💎  Server exiting gracefully…" << endl;
    return EXIT_SUCCESS;
}

void Server::abort() {
    running = false;
    shutdown(sock, SHUT_RDWR);
    close(sock);
}

void* handle_concurrently(void* data) {
    Request* req = (Request*) data;
    req->handle();
    return nullptr;
}

void Server::handle_connection(int sock_conn)
{
    bool handled = false;
    for(auto& req : request_pool)
    {
        if(!req.is_in_use()) {
            req.use(sock_conn);
            pthread_t worker_thread;
            pthread_create(&worker_thread, NULL, &handle_concurrently, (void*) &req);
            handled = true;
            break;
        }
    }

    if(!handled) {
        cout << u8"🌋  No request in pool, dropping a connection because of server overload";
        close(sock_conn);
    }
}