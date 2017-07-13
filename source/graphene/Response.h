#ifndef HEADER_RESPONSE
#define HEADER_RESPONSE

#include <string>

namespace graphene {
    class Response {
    public:

        Response() : status_code(-1), status_text(nullptr) {}

        void set_ok(const std::string& content)
        {
            status_code = 200;
            status_text = "OK";
            this->content = content;
        }

        void set_not_found()
        {
            status_code = 404;
            status_text = "Not Found";
            content = "<html><body><h1>404 Not Found</h1></body></html>";
        }

        void set_bad_request()
        {
            status_code = 400;
            status_text = "Bad Request";
            content = "<html><body><h1>400 Bad Request</h1></body></html>";
        }

        void flush(int sock);

    private:
        static const char* const http_endl;
        int status_code;
        const char* status_text;
        std::string content;
    };
}

#endif /* HEADER_RESPONSE */