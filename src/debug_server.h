#ifndef DEBUG_SERVER_H
#define DEBUG_SERVER_H
#include <string>
#include "config.h"

#ifdef DEBUG

class DebugServer {
public:
    DebugServer(int port);
    ~DebugServer();
    void send_message(int log_level, const std::string& msg);
    void accept_client();
    void handle_message(const std::string& msg);
    bool client_connected;
    int log_level = 0;
private:
    int server_fd;
    int client_fd;
};
extern DebugServer* g_debugServer; // global pointer

#endif

void debug_log(int log_level, const char* fmt, ...);

#endif //DEBUG_SERVER_H
