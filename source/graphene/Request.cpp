#include "graphene/config.h"
#include "graphene/Request.h"
#include "graphene/Response.h"

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <sys/types.h>
#include <sys/socket.h>
#include <cassert>
#include <limits.h>

using namespace graphene;
using namespace std;

const char* const Request::http_header_end = "\r\n\r\n";
const char* const Request::http_endl = "\r\n";

void Request::use(int new_sock)
{
    in_use = true;
    sock = new_sock;
    verb.clear();
    path.clear();
    
    struct timeval tv;
    tv.tv_sec = 30;  /* 30 Secs Timeout */
    tv.tv_usec = 0;
    setsockopt(new_sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv,sizeof(struct timeval));
}

void Request::handle()
{
    string request_text;

    ssize_t read_len;
    bool header_received = false;
    bool read_ok;

    do {
        read_len = read(sock, (void*)buf_read, sizeof(buf_read));
        read_ok = read_len > 0;

        if(read_ok) {
            string chunk(reinterpret_cast<const char*>(buf_read), read_len);
            request_text += chunk;
            header_received = request_text.find(http_header_end) != string::npos;
        }
    } while(read_ok && !header_received);

    Response response;
    if(header_received && parse(request_text)) {
        
        if(verb == "GET") {
            string abspath = config::webroot + path;

            if(path == "/")
            {
                abspath += "index.html";
            }

            ifstream file(abspath);

            if(file.good()) {
                string file_contents((istreambuf_iterator<char>(file)),
                                     istreambuf_iterator<char>());

                response.set_ok(file_contents);
            } else {
                // Should be 404
                response.set_bad_request();
            }

        } else {
            response.set_bad_request();
        }

    } else {
        response.set_bad_request();
    }

    if(read_ok) {
        response.flush(sock);
    }

    close(sock);
    in_use = false;
}

bool Request::parse(string& request_text)
{
    size_t first_endl_pos = request_text.find(http_endl);
    if(first_endl_pos != string::npos)
    {
        string request_line = request_text.substr(0, first_endl_pos);

        vector<string> tokens;
        istringstream request_line_stream(request_line);
        copy(istream_iterator<string>(request_line_stream),
             istream_iterator<string>(),
             back_inserter(tokens));

        if(tokens.size() == 3 &&
           (tokens[2] == "HTTP/1.1" || tokens[2] == "HTTP/1.0"))
        {
            verb = tokens[0];
            path = tokens[1];

            cout << "Got " << verb << " request for " << path << u8" …" << endl;

            return true;
        }
    }

    return false;
}
