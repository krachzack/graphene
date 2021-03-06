# graphene
Graphene is a lightweight web server implementing a small subset of the HTTP specification.

## Building and usage
Build the project with cmake and start the graphene executable.
You can select a port with the `-p 8080` switch and a document root with the
`-w ../some/../path` switch.

Default port is 10000 and default webroot is `./webroot` relative to the current working directory.
Graphene tries `../webroot` next, in case you run from the build directory, and if that also fails
it just takes the current working directory as webroot.

The server will now keep running until interrupted, e.g. by pressing `ctrl+c`.

    phil:graphene krachzack$ mkdir build && cd build && cmake .. && make
    [… … …]
    [100%] Built target graphene
    phil:build krachzack$ ./graphene -p 10001 -w ../webroot
    💎  graphene running on port 10001…
    Web root: /Users/krachzack/Development/graphene/webroot
    Got GET request for / …
    Got GET request for /favicon.ico …
    Got GET request for /favicon.ico …
    Got GET request for /test2.html …
    ^C💎  Server was requested to exit
    💎  Server exiting gracefully…

## Features
* Partial support for GET requests with status codes 200 and 404