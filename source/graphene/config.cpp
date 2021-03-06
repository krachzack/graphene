#include "config.h"
#include "cxxopts.hpp"
#include <stdlib.h>
#include <limits.h>
#include <cassert>
#include <iostream>
#include <unistd.h>

using namespace std;

namespace graphene {
    namespace config {
        std::string webroot;
        unsigned short port;
    }
}

void graphene::config::load_from_arguments(int argc, char* argv[])
{
    char webroot_absolute[PATH_MAX];

    cxxopts::Options options("graphene", "Lightweight web server");
    options.add_options()
        ("w,webroot", "Directory from which files are served to clients", cxxopts::value<std::string>()->default_value("webroot"))
        ("p,port", "Port to take connections from", cxxopts::value<int>()->default_value("10000"))
    ;
    options.parse(argc, argv);

    std::string webroot_relative = options["webroot"].as<string> ();
    int param_port = options["port"].as<int> ();
    assert(((unsigned short) param_port) == param_port); // assume fits into unsigned short

    // First search for webroot in current working directory, either given as -w paramater
    // or the default "webroot"
    bool ok = realpath(webroot_relative.c_str(), webroot_absolute);
    if(!ok) {
        // If unsuccessful, try ../webroot
        ok = realpath("../webroot", webroot_absolute);

        if(!ok) {
            // If unsuccessful, just use the current working directory
            ok = getcwd(webroot_absolute, PATH_MAX);
        }
    }
    assert(ok);

    graphene::config::webroot = webroot_absolute;
    graphene::config::port = (unsigned short) param_port;
}