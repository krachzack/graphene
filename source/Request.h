#ifndef HEADER_REQUEST
#define HEADER_REQUEST


namespace graphene {
    class Request {
    public:

        Request() : in_use(false), sock(-1)  {}

        void use(int new_sock);

        void handle();

        bool is_in_use() { return in_use; }

    private:
        volatile bool in_use;
        int sock;
    };
}

#endif /* HEADER_REQUEST */