#ifndef SERVER_HPP
#define SERVER_HPP

#include "sockets.hpp"

class Session;

class Server : public FdHandler {
    enum { listen_qlen = 16 };

    long long int value;
    EventSelector *selector;
public:
    static const char welcome_msg[];
private:
    Server(EventSelector *sel, int fd);
public:
    virtual ~Server();

    static Server *Start(EventSelector *sel, int port);

    void Close(Session *sess);
    void Execute(Session *sess, const char *cmd);

    virtual void Handle(bool r, bool w);
};

class Session : public FdHandler {
    enum { buffer_size = 512 };

    Server *server;
    char buffer[buffer_size];
    unsigned int usage;
public:
    Session(Server *serv, int fd);
    virtual void Handle(bool r, bool w);
    void Send(const char *msg);
private:
    static bool IsSpace(char c) { return c == ' ' || c == '\t'; }
    static void Strip(char **s);
    void ProcessLine(char *s) { Strip(&s); server->Execute(this, s); }
    void CheckLines();
};

#endif
