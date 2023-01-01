#include "request.hpp"
#include "utils.hpp"

void handle_get(int conn, std::string url);
void handle_post(int conn, std::string url, char buffer[]);

void handle_request(int conn)
{
  // Receive the request
  char buffer[30000] = {0};
  recv(conn, buffer, 30000, 0);

  // Parse the methods and handle accordingly
  std::string method = parse_method(buffer);
  std::string url = parse_url(buffer);

  if (method == "GET")
    handle_get(conn, url);
  else if (method == "POST")
    handle_post(conn, url, buffer);
}

// Handle Get Request
void handle_get(int conn, std::string url)
{
  const char *response = "HTTP/1.1 200 OK\nContent-Type: text/plain\n\nThis is Get Method";

  std::string cwd = get_cwd();
  std::cout << cwd << std::endl;

  // Get extension
  // if no extension default to .html
  // switch based on the extension

  // create appropiate header
  // send the file
  write(conn, response, strlen(response));
  close(conn);
}

void handle_post(int conn, std::string url, char buffer[])
{
  const char *response = "HTTP/1.1 200 OK\nContent-Type: text/plain\n\nThis is Post Method";

  std::cout << url << std::endl;
  write(conn, response, strlen(response));
  close(conn);
}