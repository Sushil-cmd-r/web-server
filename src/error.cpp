#include "error.hpp"

// Error Handling
void err_and_exit(std::string msg)
{
  std::cout << msg << std::endl;
  exit(EXIT_FAILURE);
}