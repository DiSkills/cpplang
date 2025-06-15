#ifndef SERVER_HPP
#define SERVER_HPP

#include "sockets.hpp"

enum {
    listen_qlen = 16,
    buffer_size = 512,
};

class Session;

class Server : FdHandler {
    friend class Session;

    long long int value;
    EventSelector *selector;

    static const char welcome_msg[];
public:
    virtual ~Server();
    static Server *Start(EventSelector *sel, int port);
private:
    Server(EventSelector *sel, int fd);
    void Close(Session *sess);
    void Execute(Session *sess, const char *cmd);
    virtual void Handle(bool r, bool w);
};

class Session : FdHandler {
    friend class Server;

    Server *server;
    char buffer[buffer_size];
    unsigned int usage;
private:
    Session(Server *serv, int fd);
    virtual void Handle(bool r, bool w);
    void Send(const char *msg);

    static bool IsSpace(char c) { return c == ' ' || c == '\t'; }
    static void Strip(char **s);

    void ProcessLine(char *s) { Strip(&s); server->Execute(this, s); }
    void CheckLines();
};

#endif
