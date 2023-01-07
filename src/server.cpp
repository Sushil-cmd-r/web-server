#include "server.hpp"

using namespace HTTP;

Server::Server(int _PORT)
{
  PORT = _PORT;
  // Create a Socket
  if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    err_and_exit("Socket Creation Failed");
  setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &set, sizeof(set));

  // Initialize address struct
  address.sin_family = AF_INET;
  address.sin_port = htons(_PORT);
  address.sin_addr.s_addr = INADDR_ANY;
  memset(address.sin_zero, 0, sizeof(address.sin_zero));

  // Bind address to socket
  if ((bind(socket_fd, (struct sockaddr *)&address, sizeof(address))) < 0)
    err_and_exit("Binding failed");
}

void Server::start_listening()
{
  // Start Listening
  if ((listen(socket_fd, MAXQUEUE)) == -1)
    err_and_exit("Unable To start Listening");
  else
  {
    cout << "Server Listening on port " << PORT << "...\n"
         << endl;
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

    tp.add_work(&conn);
  }
}

void Server::err_and_exit(string msg)
{
  cout << msg << endl;
  exit(EXIT_FAILURE);
}