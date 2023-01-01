#include <bits/stdc++.h>
#include <unistd.h>
#include <cstring>

#include "request.h"
#include "error.h"
#include "utils.h"

void send_response(int conn, std::string method, std::string url);
std::string make_header(int status, std::string content_type);
void serve_file(int conn, std::string path);

void handle_request(int conn, char client_request[])
{
  std::string client_msg = strtok(client_request, "\n");

  std::string method = parse_method(client_msg);
  std::string url = parse_url(client_msg);

  if (url == "/")
    url = "/index.html";
  send_response(conn, method, url);

  // Close the connection
  close(conn);
}

void send_response(int conn, std::string method, std::string url)
{
  // get current directory
  char cwd[PATH_MAX];
  if (getcwd(cwd, sizeof(cwd)) == NULL)
  {
    err_and_exit("Unable to get current working directory");
  }

  // GET methods
  if (method == "GET")
  {
    std::string ext = parse_ext(url);
    std::string path = cwd;
    if (ext == ".html")
    {
      path += "/static/templates";
      path += url;
      std::string header = make_header(200, "text/html");
      write(conn, header.c_str(), strlen(header.c_str()));
    }
    else if (ext == ".css")
    {
      path += "/static";
      path += url;
      std::string header = make_header(200, "text/css");
      write(conn, header.c_str(), strlen(header.c_str()));
    }

    serve_file(conn, path);
  }
}

void serve_file(int conn, std::string path)
{
  FILE *fp = fopen(path.c_str(), "r");
  if (fp == NULL)
    std::cout << "Unable to Open File" << std::endl;

  char buff[4096];
  size_t bytes;

  while ((bytes = fread(buff, 1, 4096, fp)) > 0)
  {
    write(conn, buff, bytes);
  }
  fclose(fp);
}

std::string make_header(int status, std::string content_type)
{
  std::string header = "HTTP/1.1 ";
  if (status == 404)
  {
    header += "404\nContent-Type: text/html\n\n";
    return header;
  }
  header += "200\nContent-Type: ";
  header += content_type;
  header += "\n\n";

  return header;
}
