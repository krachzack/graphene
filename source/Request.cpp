#include "Request.h"
#include "Response.h"

#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sstream>

using namespace graphene;

void Request::use(int new_sock) {
    in_use = true;
    sock = new_sock;    
}

void Request::handle() {
    std::cout << u8"Handling request…" << std::endl; 

    ssize_t read_len = read(sock, (void*)buf_read, sizeof(buf_read));

    if(read_len > 0) {
        std::string message(reinterpret_cast<const char*>(buf_read), read_len);

        std::cout << u8"Got message…" << message << std::endl; 

        Response response;
        response.set_bad_request();
        response.flush(sock);
    }
    

    std::cout << u8"Finished handling request…" << std::endl; 
    close(sock);
    in_use = false;
}

/*void Request::respond_bad_request() {
    const char* status = "HTTP/1.1 400 Bad Request\n";
    const char* content = "<html><body><h1>400 Bad Request</h1></body></html>";

    std::ostringstream header_stream;

    header_stream << "Server: graphen/1.0\n";
    header_stream << "Content-Length: " << strlen(content) << "\n";
    header_stream << "\n";
    std::string header_str = header_stream.str();

    write(sock, status, strlen(status));
    write(sock, header_str.c_str(), header_str.size());
    write(sock, content, strlen(content));
}*/