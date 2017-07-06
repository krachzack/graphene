cmake_minimum_required (VERSION 2.6)
project (graphene)

set(
  IMPL_FILES
  "source/main.cpp"
  "source/Server.cpp"
  "source/Request.cpp"
  "source/Response.cpp"
)

include_directories(source)

# Add Executable and sources
add_executable(
  graphene
  ${IMPL_FILES}
)

# Packages to check for available headers, functions and types
include (CheckSymbolExists)
include (CheckIncludeFiles)
include (CheckTypeSize)

find_package(Threads REQUIRED)

if(THREADS_HAVE_PTHREAD_ARG)
  target_compile_options(PUBLIC graphene "-pthread")
endif()
if(CMAKE_THREAD_LIBS_INIT)
  target_link_libraries(graphene "${CMAKE_THREAD_LIBS_INIT}")
endif()

check_include_files ("sys/types.h;sys/socket.h;netinet/in.h;fcntl.h;netdb.h" HAVE_POSIX_SOCKETS)

# Enable C++11 features
target_compile_features(graphene PRIVATE cxx_range_for cxx_auto_type cxx_nullptr cxx_generic_lambdas cxx_lambdas cxx_lambda_init_captures)
