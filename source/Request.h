#ifndef HEADER_REQUEST
#define HEADER_REQUEST
#include <stdint.h>
#include <sstream>

namespace graphene {
    class Request {
    public:

        Request() : in_use(false), sock(-1)  {}

        void use(int new_sock);

        void handle();

        bool is_in_use() { return in_use; }

    private:
        static const int BUF_SIZE = 4096;

        volatile bool in_use;

        int sock;

        uint8_t buf_read[BUF_SIZE];
        uint8_t buf_write[BUF_SIZE];

        //void respond_bad_request();
    };
}

#endif /* HEADER_REQUEST */