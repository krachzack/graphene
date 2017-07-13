#ifndef HEADER_REQUEST
#define HEADER_REQUEST
#include <stdint.h>
#include <sstream>
#include <string>
#include <atomic>

namespace graphene {
    class Request {
    public:

        Request() : in_use(false), sock(-1)  {}

        void use(int new_sock);

        void handle();

        bool is_in_use() { return in_use.load(); }

    private:
        static const char* const http_header_end;
        static const char* const http_endl;
        static const int BUF_SIZE = 4096;

        std::atomic_bool in_use;

        int sock;
        std::string verb;
        std::string path;

        uint8_t buf_read[BUF_SIZE];
        uint8_t buf_write[BUF_SIZE];

        bool parse(std::string& request_text);

        //void respond_bad_request();
    };
}

#endif /* HEADER_REQUEST */