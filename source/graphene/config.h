#ifndef HEADER_CONFIG
#define HEADER_CONFIG
#include <string>

namespace graphene {
    namespace config {
        extern std::string webroot;
        extern unsigned short port;
        void load_from_arguments(int argc, char* argv[]);
    }
}

#endif /* HEADER_CONFIG */