#include <iostream>
#include "server.hpp"

using namespace std;
#define PORT 5000

int main()
{
  HTTP::Server server(PORT);
  server.start_listening();
}