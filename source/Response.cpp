#include "Response.h"
#include <cassert>
#include <sstream>
#include <unistd.h>

using namespace graphene;

void Response::flush(int sock)
{
    assert(status_code != -1);
    assert(status_text);

    std::ostringstream header_stream;

    header_stream << "HTTP/1.1 " << status_code << " " << status_text << "\n";

    header_stream << "Server: graphen/1.0\n";
    header_stream << "Content-Length: " << content.size() << "\n";
    header_stream << "\n";

    std::string header = header_stream.str();

    write(sock, header.c_str(), header.size());
    write(sock, content.c_str(), content.size());
}
