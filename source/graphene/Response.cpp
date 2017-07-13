#include "graphene/Response.h"
#include <cassert>
#include <sstream>
#include <unistd.h>

using namespace graphene;

const char* const Response::http_endl = "\r\n";

void Response::flush(int sock)
{
    assert(status_code != -1);
    assert(status_text);

    std::ostringstream header_stream;

    header_stream << "HTTP/1.1 " << status_code << " " << status_text << http_endl;

    header_stream << "Server: graphen/1.0" << http_endl;
    header_stream << "Content-Length: " << content.size() << http_endl;
    header_stream << http_endl;

    std::string header = header_stream.str();

    write(sock, header.c_str(), header.size());
    write(sock, content.c_str(), content.size());
}
