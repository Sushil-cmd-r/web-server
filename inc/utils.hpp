#ifndef _UTILS_HPP
#define _UTILS_HPP

#include <bits/stdc++.h>
#include <unistd.h>

std::string parse_method(char request[]);
std::string parse_url(char request[]);
std::string parse_ext(std::string url);
std::string get_cwd();

#endif