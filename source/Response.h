#ifndef HEADER_RESPONSE
#define HEADER_RESPONSE

#include <string>

namespace graphene {
    class Response {
    public:

        Response() : status_code(-1), status_text(nullptr) {}

        void set_bad_request()
        {
            status_code = 400;
            status_text = "Bad Request";
            content = "<html><body><h1>400 Bad Request</h1></body></html>";
        }

        void flush(int sock);

    private:
        int status_code;
        const char* status_text;
        std::string content;
    };
}

#endif /* HEADER_RESPONSE */