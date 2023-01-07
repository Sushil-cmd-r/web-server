#include "request.hpp"

void handle_request(int *_conn)
{
  // Receive Client Request
  int conn = *_conn;
  char buffer[30000] = {0};
  recv(conn, buffer, 30000, 0);

  const char *res = "HTTP/1.1 200 OK\nContent-Type: text/plain\n\r\n\rHello World";

  write(conn, res, strlen(res));
  close(conn);
}