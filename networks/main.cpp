#include <stdio.h>
#include <stdlib.h>

#include "server.hpp"

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Expected: %s <port>\n", argv[0]);
        return 1;
    }

    char *endptr;
    long port = strtol(argv[1], &endptr, 10);
    if (!*argv[1] || *endptr) {
        fprintf(stderr, "The port is invalid\n");
        return 2;
    }

    EventSelector selector;
    Server *serv = Server::Start(&selector, port);
    if(!serv) {
        perror("server");
        return 3;
    }
    selector.Run();
    delete serv;
    return 0;
}
