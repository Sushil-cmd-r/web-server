#include "utils.hpp"

string get_cwd()
{
  // get current directory
  char cwd[PATH_MAX];
  if (getcwd(cwd, sizeof(cwd)) == NULL)
  {
    cout << "Unable to get current working directory" << endl;
    exit(EXIT_FAILURE);
  }

  return string(cwd);
}

string parse_method(string client_msg)
{
  string method = "";

  for (int i = 0; i < (int)client_msg.size(); i++)
  {
    if (client_msg[i] == ' ')
      break;
    method += client_msg[i];
  }

  return method;
}

string parse_url(string client_msg)
{
  int flag = 0;
  string url = "";

  for (int i = 0; i < (int)client_msg.size(); i++)
  {
    if (flag == 1)
    {
      if (client_msg[i] == ' ')
        break;
      url += client_msg[i];
    }
    else if (flag == 0 && client_msg[i] == ' ')
    {
      flag = 1;
    }
  }

  return url;
}

string parse_ext(string url)
{
  string delimiter = ".";
  int len = url.size();
  int idx = url.find(delimiter);
  if (idx == -1)
    return "NA";

  string ext = url.substr(idx + 1, len);

  return ext;
}