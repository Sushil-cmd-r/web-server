#ifndef _SERVER_HPP
#define _SERVER_HPP 1

#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include "thread_pool.hpp"

using namespace std;
#define MAXQUEUE 20

namespace HTTP
{
  class Server
  {
  private:
    int socket_fd, set = 1, PORT;
    struct sockaddr_in address;
    TP::Thread_Pool tp;

  public:
    // Constructor
    Server(int PORT);

    // Functions
    void start_listening();

    // Error Handling
    void err_and_exit(string msg);
  };
}

#endif