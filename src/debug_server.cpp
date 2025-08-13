#include "debug_server.h"
#include "config.h"
#ifdef DEBUG

#include <thread>
#include <cstdarg>
#include <cstdio>
#include <string>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

DebugServer* g_debugServer = nullptr;

DebugServer::DebugServer(int port) {
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 1);

    std::cout << "[DEBUG] Waiting for debugger to connect on port " << port << "...\n";
    accept_client();
}

DebugServer::~DebugServer() {
    if (client_fd > 0) close(client_fd);
    if (server_fd > 0) close(server_fd);
}

void DebugServer::send_message(int log_level, const std::string& msg) {
    if (client_fd == 0) {
        return;
    }
    if (this->log_level != 0 && this->log_level <= log_level) {
        send(client_fd, msg.c_str(), msg.size(), 0);
    }
}


void DebugServer::accept_client() {
    client_fd = accept(server_fd, nullptr, nullptr);
    if (client_fd < 0) {
        perror("accept");
        return;
    }
    this->client_connected = true;
    std::cout << "[DEBUG] Debugger connected!\n";


    std::thread([this]() {
        std::string buffer;
        char temp[512];
        while (this->client_connected) {
           int n = recv(client_fd, temp, sizeof(temp)-1, 0);
           if (n <= 0) {
               std::cout << "[DEBUG] Client disconnected!\n";
               this->client_connected = false;
               close(client_fd);
               break;
           }
           temp[n] = '\0';
           buffer += temp;

           size_t pos;
           while ((pos = buffer.find('\n')) != std::string::npos) {
               std::string msg = buffer.substr(0, pos);
               handle_message(msg);
               buffer.erase(0, pos + 1);
           }
        }
    }).detach();
}

void DebugServer::handle_message(const std::string& msg) {
    std::cout << "[DEBUG CLIENT] " << msg << std::endl;

    if (msg.rfind("[LEVEL]=", 0) == 0) {
        // starts with
        try {
            this->log_level = std::stoi(msg.substr(8));
            std::cout << "[DEBUG] Log level set to " << this->log_level << std::endl;
        } catch (...) {
            std::cout << "[DEBUG] Invalid log level: " << msg << std::endl;
        }
    }
}

#endif

void debug_log(int log_level, const char* fmt, ...) {
#ifdef DEBUG
    if (!g_debugServer) return;

    char buffer[512];

    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args); // format the string
    va_end(args);

    g_debugServer->send_message(log_level, buffer);
#endif
}