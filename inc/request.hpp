#ifndef _REQUEST_HPP
#define _REQUEST_HPP 1

#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

#include "utils.hpp"

using namespace std;

void handle_request(int *_conn);

#endif