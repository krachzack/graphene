#include "config.h"
#include "cxxopts.hpp"
#include <stdlib.h>
#include <limits.h>
#include <cassert>
#include <iostream>

using namespace std;

namespace graphene {
    namespace config {
        std::string webroot;
    }
}

void graphene::config::load_from_arguments(int argc, char* argv[])
{
    char webroot_absolute[PATH_MAX];

    cxxopts::Options options("graphene", "Lightweight web server");
    options.add_options()
        ("w,webroot", "Directory from which files are served to clients", cxxopts::value<std::string>()->default_value("../webroot"))
    ;
    options.parse(argc, argv);

    std::string webroot_relative = options["webroot"].as<string> ();

    bool ok = realpath(webroot_relative.c_str(), webroot_absolute);
    assert(ok);

    graphene::config::webroot = webroot_absolute;
}