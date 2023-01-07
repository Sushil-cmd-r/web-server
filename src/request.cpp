#include "request.hpp"
#include "response.hpp"

string base_path = get_cwd() + "/public/";

void handle_get(int conn, string url, string ext);
void handle_request(int *_conn)
{
  // Receive Client Request
  int conn = *_conn;
  char buffer[30000] = {0};
  recv(conn, buffer, 30000, 0);

  // Parse client request
  string client_msg = strtok(buffer, "\n");
  // Parse method
  string method = parse_method(client_msg);
  // Parse url
  string url = parse_url(client_msg);
  if (url == "/")
  {
    url = "/index.html";
  }
  // Pares ext
  string ext = parse_ext(url);
  if (ext == "NA")
  {
    ext = "html";
    url += ".html";
  }
  else if (ext == "jpg" || ext == "jpeg")
  {
    ext = "images";
  }

  if (method == "GET")
  {
    handle_get(conn, url, ext);
  }
  else
  {
    string res = Messages[BAD_REQUEST];
    write(conn, res.c_str(), strlen(res.c_str()));
    cout << method << " REQUEST for " << url << " completed unsuccessfully" << endl;
    close(conn);
  }
}

void handle_get(int conn, string url, string ext)
{
  string path = base_path + ext + url;
  // try opening the file
  FILE *fp = fopen(path.c_str(), "r");
  if (fp == NULL)
  {
    string res = Messages[NOT_FOUND];
    write(conn, res.c_str(), strlen(res.c_str()));
    cout << "GET REQUEST received for " << url << " completed unsuccessfully" << endl;
    close(conn);
    return;
  }

  // Create header
  string header = Messages[HTTP_HEADER];
  for (int i = 0; i < (int)ContentType->length(); i++)
  {
    if (fileExtension[i] == ext)
    {
      header += ContentType[i];
    }
  }

  char buff[4096];
  size_t bytes;

  // Send header
  write(conn, header.c_str(), strlen(header.c_str()));

  while ((bytes = fread(buff, 1, 4096, fp)) > 0)
  {
    write(conn, buff, bytes);
  }

  fclose(fp);
  cout << "GET REQUEST received for " << url << " completed" << endl;
  close(conn);
}