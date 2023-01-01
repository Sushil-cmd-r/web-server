#include "server.hpp"
#include "error.hpp"
#include "request.hpp"

#define MAX_QUEUE 20

void listen_server(int socket_fd);

void create_server(int PORT)
{
  // Create a Socket
  int socket_fd, set = 1;
  if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    err_and_exit("Socket Creation Failed");
  setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &set, sizeof(set));

  // Initialize address struct
  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_port = htons(PORT);
  memset(address.sin_zero, 0, sizeof(address.sin_zero));

  // Bind address to socket
  if ((bind(socket_fd, (struct sockaddr *)&address, sizeof(address))) < 0)
    err_and_exit("Binding failed");

  // Start Listening
  listen_server(socket_fd);
}

void listen_server(int socket_fd)
{
  // Start Listening
  if ((listen(socket_fd, MAX_QUEUE)) == -1)
    err_and_exit("Unable To start Listening");
  else
  {
    std::cout << "Server Listening..." << std::endl;
    fflush(stdout);
  }

  // Loop for listening for connections
  while (true)
  {
    int conn;
    // Client Socket
    struct sockaddr_in client;
    socklen_t clientLen = sizeof(client);
    bzero(&client, clientLen);

    // Connect To Client
    if ((conn = accept(socket_fd, (struct sockaddr *)&client, &clientLen)) < 0)
      err_and_exit("Unable to connect");

    handle_request(conn);
    }
}