#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
using namespace std;

#define PORT 5000
#define MAXQUEUE 20

void err_and_exit(string msg);
string parse_method(string *msg);
string parse_url(string msg);
void handle_request(int conn, string client_msg);

int main()
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
  if ((listen(socket_fd, MAXQUEUE)) == -1)
    err_and_exit("Unable To start Listening");
  else
  {
    cout << "Listening on Port " << PORT << endl;
    fflush(stdout);
  }

  // Loop for listening for connections
  while (true)
  {
    int conn;
    struct sockaddr_in client;
    socklen_t clientLen = sizeof(client);
    bzero(&client, clientLen);
    if ((conn = accept(socket_fd, (struct sockaddr *)&client, &clientLen)) < 0)
      err_and_exit("Unable to connect");

    char buffer[30000] = {0};
    recv(conn, buffer, 30000, 0);
    string client_msg = strtok(buffer, "\n");

    handle_request(conn, client_msg);
  }
}

// Error Handling
void err_and_exit(string msg)
{
  cout << msg << endl;
  exit(EXIT_FAILURE);
}

// Parsers
string parse_method(string *msg)
{
  string delimiter = " ";
  string method = msg->substr(0, msg->find(delimiter));
  *msg = msg->substr(msg->find(delimiter));
  return method;
}

string parse_url(string msg)
{
  string url;
  for (int i = 0; i < (int)msg.size(); i++)
  {
    if (msg[i] == ' ' && msg[i + 1] == 'H')
      break;
    url += msg[i];
  }
  url.erase(remove(url.begin(), url.end(), ' '), url.end());
  return url;
}

string parse_ext(string str)
{
  string delimiter = ".";
  int len = str.size();

  string ext = str.substr(str.find(delimiter), len);

  return ext;
}

void serve_file(int conn, char *path, const char *header)
{
  int flag = 0;
  FILE *fp = fopen(path, "r");
  if (fp == NULL)
    cout << "Unable to Open file" << endl;

  char buff[4096];
  size_t bytes;
  while ((bytes = fread(buff, 1, 4096, fp)) > 0)
  {
    if (flag == 0)
    {
      write(conn, header, strlen(header));
      flag = 1;
    }
    write(conn, buff, bytes);
  }
  fclose(fp);
  close(conn);
}

// Request Handling
void handle_request(int conn, string client_msg)
{
  char cwd[PATH_MAX];
  if (getcwd(cwd, sizeof(cwd)) == NULL)
  {
    err_and_exit("Unable to get current working directory");
  }

  string method = parse_method(&client_msg);
  string url = parse_url(client_msg);
  if (url == "/" || url == "/index.html")
  {
    const char *header = "HTTP/1.1 200 OK\nContent-Type:text/html\n\r\n\r";
    char *path = strcat(cwd, "/static/templates/index.html");
    serve_file(conn, path, header);
  }
  else
  {
    string ext = parse_ext(url);

    if (ext == ".css")
    {
      const char *header = "HTTP/1.1 200 OK\nContent-Type:text/css\n\r\n\r";
      char *path = strcat(cwd, "/static/styles/index.css");
      serve_file(conn, path, header);
    }
  }
}
