#include "utils.hpp"
#include "error.hpp"

std::string parse_method(char request[])
{
  std::string method;

  for (int i = 0; i < 4; i++)
  {
    if (request[i] == ' ')
      break;
    method += request[i];
  }

  return method;
}
std::string parse_url(char request[])
{
  int flag = 0;
  std::string url = "";

  for (int i = 0; i < 100; i++)
  {
    if (flag == 1)
    {
      if (request[i] == ' ')
        break;
      url += request[i];
    }
    else if (flag == 0 && request[i] == ' ')
    {
      flag = 1;
    }
  }

  return url;
}

std::string parse_ext(std::string url)
{
  std::string delimiter = ".";
  int pos = url.find(delimiter);
  if (pos == -1)
    return "NA";

  std::string ext = url.substr(pos, url.size());
  return ext;
}

std::string get_cwd()
{
  // get current directory
  char cwd[PATH_MAX];
  if (getcwd(cwd, sizeof(cwd)) == NULL)
  {
    err_and_exit("Unable to get current working directory");
  }

  return std::string(cwd);
}