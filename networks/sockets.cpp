#include <sys/socket.h>

#include "sockets.hpp"

void EventSelector::Add(FdHandler *h)
{
    int fd = h->GetFd();
    if (!handlers) {
        len = fd > 15 ? fd + 1 : 16;
        handlers = new FdHandler*[len];
        for (int i = 0; i < len; i++) {
            handlers[i] = 0;
        }
    } else if (fd >= len) {
        FdHandler **tmp = new FdHandler*[fd + 1];
        for (int i = 0; i <= fd; i++) {
            tmp[i] = i < len ? handlers[i] : 0;
        }
        len = fd + 1;
        delete[] handlers;
        handlers = tmp;
    }
    if (fd > maxfd) {
        maxfd = fd;
    }
    handlers[fd] = h;
}

bool EventSelector::Remove(FdHandler *h)
{
    int fd = h->GetFd();
    if (fd >= len || handlers[fd] != h) {
        return false;
    }
    handlers[fd] = 0;
    if (fd == maxfd) {
        while (maxfd >= 0 && !handlers[maxfd]) {
            maxfd--;
        }
    }
    return true;
}

void EventSelector::Run()
{
    quit = false;
    do {
        fd_set readfds, writefds;
        FD_ZERO(&readfds);
        FD_ZERO(&writefds);
        for (int i = 0; i <= maxfd; i++) {
            if (!handlers[i]) {
                continue;
            }
            if (handlers[i]->WantRead()) {
                FD_SET(i, &readfds);
            }
            if (handlers[i]->WantWrite()) {
                FD_SET(i, &writefds);
            }
        }

        int res = select(maxfd + 1, &readfds, &writefds, 0, 0);
        if (res < 0) {
            break;
        } else if (res > 0) {
            for (int i = 0; i <= maxfd; i++) {
                if (!handlers[i]) {
                    continue;
                }
                bool r = FD_ISSET(i, &readfds),
                     w = FD_ISSET(i, &writefds);
                if (r || w) {
                    handlers[i]->Handle(r, w);
                }
            }
        }
    } while (!quit);
}
