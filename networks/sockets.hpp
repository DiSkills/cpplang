#ifndef SOCKETS_HPP
#define SOCKETS_HPP

#include <unistd.h>

class FdHandler {
    int fd;
    bool owner;
public:
    FdHandler(int sd, bool is_owner = true) : fd(sd), owner(is_owner) {}
    virtual ~FdHandler() { if (owner) close(fd); }

    virtual void Handle(bool r, bool w) = 0;

    int GetFd() const { return fd; }

    virtual bool WantRead() const { return true; }
    virtual bool WantWrite() const { return false; }
};

class EventSelector {
    FdHandler **handlers;
    int len;
    int maxfd;
    bool quit;
public:
    EventSelector() : handlers(0), len(0), maxfd(-1), quit(false) {}
    ~EventSelector() { if (handlers) delete[] handlers; }

    void Add(FdHandler *h);
    bool Remove(FdHandler *h);

    void BreakLoop() { quit = true; }

    void Run();
};

#endif
