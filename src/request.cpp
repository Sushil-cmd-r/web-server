#include "request.hpp"
#include "utils.hpp"

void handle_get(int conn, std::string url);
void handle_post(int conn, std::string url, char buffer[]);
void serve_html(int conn, std::string url);
void serve_file(int conn, FILE *fp, std::string header);
std::string make_header(int status, std::string content_type);

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
  if (url == "/")
    url += "index.html";

  // Get extension
  std::string ext = parse_ext(url);
  // if no extension default to .html
  if (ext == "NA")
  {
    url += ".html";
    ext = ".html";
  }
  // switch based on the extension
  if (ext == ".html")
  {
    // serve html
    serve_html(conn, url);
  }
  else if (ext == ".css")
  {
    // serve static files
    std::string cwd = get_cwd();
    std::string path = cwd + "/static/" + url;
    std::string header;
    FILE *fp = fopen(path.c_str(), "r");
    if (fp == NULL)
    {
      header = make_header(404, "");
      write(conn, header.c_str(), strlen(header.c_str()));
    }
    else
    {
      header = make_header(200, "text/css");
      serve_file(conn, fp, header);
    }
  }
  else
  {
    std::string res = make_header(404, "");
    write(conn, res.c_str(), strlen(res.c_str()));
  }

  // close the connection
  close(conn);
}

void handle_post(int conn, std::string url, char buffer[])
{
  const char *response = "HTTP/1.1 200 OK\nContent-Type: text/plain\n\nThis is Post Method";

  std::cout << url << std::endl;
  write(conn, response, strlen(response));
  close(conn);
}

void serve_file(int conn, FILE *fp, std::string header)
{
  int flag = 0;
  char buff[4096];
  size_t bytes;

  while ((bytes = fread(buff, 1, 4096, fp)) > 0)
  {
    if (flag == 0)
    {
      write(conn, header.c_str(), strlen(header.c_str()));
      flag = 1;
    }
    write(conn, buff, bytes);
  }
  fclose(fp);
}

void serve_html(int conn, std::string url)
{
  std::string cwd = get_cwd();
  std::string path = cwd + "/static/templates" + url;
  std::string header;
  FILE *fp = fopen(path.c_str(), "r");
  if (fp == NULL)
  {
    path = cwd + "/static/templates/error.html";
    fp = fopen(path.c_str(), "r");
    if (fp == NULL)
      std::cout << "Unable to Open Any file\n";
    header = make_header(404, "text/html");
  }
  else
  {
    header = make_header(200, "text/html");
  }

  serve_file(conn, fp, header);
}

std::string make_header(int status, std::string content_type)
{
  std::string header = "HTTP/1.1 ";
  if (status == 404)
  {
    header += "404";
  }
  else
  {
    header += "200";
  }
  if (content_type != "")
  {
    header += "\nContent-Type: ";
    header += content_type;
  }
  header += "\n\n";

  return header;
}