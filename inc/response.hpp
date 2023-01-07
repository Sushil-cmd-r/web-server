#ifndef _RESPONSE_HPP
#define _RESPONSE_HPP 1

#include <iostream>
using namespace std;

typedef enum
{
    HTTP_HEADER,
    BAD_REQUEST,
    NOT_FOUND

} messageType;

string fileExtension[] = {
    "css",
    "gif",
    "ico",
    "js",
    "json",
    "png",
    "svg",
    "txt",
    "html",
    "images",
    "images"};

string ContentType[] = {
    "Content-Type: text/css\r\n\r\n",
    "Content-Type: image/gif\r\n\r\n",
    "Content-Type: image/vnd.microsoft.icon\r\n\r\n",
    "Content-Type: text/javascript\r\n\r\n",
    "Content-Type: application/json\r\n\r\n",
    "Content-Type: image/png\r\n\r\n",
    "Content-Type: image/svg+xml\r\n\r\n",
    "Content-Type: text/plain\r\n\r\n",
    "Content-Type: text/html\r\n\r\n",
    "Content-Type: image/jpeg\r\n\r\n",
    "Content-Type: image/jpeg\r\n\r\n"};

string Messages[] = {
    "HTTP/1.1 200 Ok\n",
    "HTTP/1.0 500 Bad Request\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE html><html><body>Bad Request or System is busy right now.</body></html>",
    "HTTP/1.0 404 File not found\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE html><html><body>The Requested file does not exist on this server</body></html>"};

#endif