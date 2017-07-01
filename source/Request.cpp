#include "Request.h"

#include <iostream>
#include <unistd.h>

using namespace graphene;

void Request::use(int new_sock) {
    in_use = true;
    sock = new_sock;    
}

void Request::handle() {
    std::cout << u8"Handling request…" << std::endl; 
    write(sock,"I got your message",18);
    std::cout << u8"Finished handling request…" << std::endl; 
    close(sock);
    in_use = false;
}