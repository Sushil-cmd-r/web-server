#include <iostream>
#include "utils.h"

std::string parse_method(std::string client_msg)
{
  std::string method = "";

  for (int i = 0; i < (int)client_msg.size(); i++)
  {
    if (client_msg[i] == ' ')
      break;
    method += client_msg[i];
  }

  return method;
}

std::string parse_url(std::string client_msg)
{
  int flag = 0;
  std::string url = "";

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

std::string parse_ext(std::string url)
{

  std::string delimiter = ".";
  int len = url.size();

  std::string ext = url.substr(url.find(delimiter), len);

  return ext;
}