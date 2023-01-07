#ifndef _UTILS_HPP
#define _UTILS_HPP 1

#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

string get_cwd();
string parse_ext(string request);
string parse_method(string request);
string parse_url(string request);

#endif