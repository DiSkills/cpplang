#include <netinet/in.h>
#include <sys/socket.h>

#include <stdio.h>
#include <string.h>

#include "server.hpp"

const char Server::welcome_msg[] = "up/show/down\n";

Server::Server(EventSelector *sel, int fd)
    : FdHandler(fd), value(0), selector(sel)
{
    selector->Add(this);
}

Server::~Server()
{
    selector->Remove(this);
}

Server *Server::Start(EventSelector *sel, int port)
{
    int lsd = socket(AF_INET, SOCK_STREAM, 0);
    if (lsd == -1) {
        return 0;
    }

    int opt = 1;
    setsockopt(lsd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);
    int res = bind(lsd, (struct sockaddr *)&addr, sizeof(addr));
    if (res == -1) {
        return 0;
    }
    listen(lsd, listen_qlen);
    return new Server(sel, lsd);
}

void Server::Close(Session *sess)
{
    selector->Remove(sess);
    delete sess;
}

void Server::Execute(Session *sess, const char *cmd)
{
    if (0 == strcmp(cmd, "show")) {
        char str[128];
        sprintf(str, "%lld\n", value);
        sess->Send(str);
        return;
    } else if (0 == strcmp(cmd, "up")) {
        value++;
    } else if (0 == strcmp(cmd, "down")) {
        value--;
    } else {
        sess->Send("Unknown command\n");
        return;
    }
    sess->Send("Ok\n");
}

void Server::Handle(bool r, bool w)
{
    if (!r) {
        return;
    }
    int fd = accept(GetFd(), NULL, NULL);
    if (fd == -1) {
        return;
    }
    selector->Add(new Session(this, fd));
}

/* -------------------------------- Session -------------------------------- */
Session::Session(Server *serv, int fd)
    : FdHandler(fd), server(serv), usage(0)
{
    Send(Server::welcome_msg);
}

void Session::Handle(bool r, bool w)
{
    if (!r) {
        return;
    }
    int rc = read(GetFd(), buffer + usage, buffer_size - usage);
    if (rc <= 0) {
        server->Close(this);
        return;
    }
    usage += rc;

    CheckLines();
    if (usage >= buffer_size) {
        Send("Line is too long...\n");
        server->Close(this);
    }
}

void Session::Send(const char *msg)
{
    write(GetFd(), msg, strlen(msg));
}

void Session::Strip(char **s)
{
    while (IsSpace(**s)) {
        (*s)++;
    }
    if (!**s) {
        return;
    }

    char *end = *s + strlen(*s) - 1;
    while (end > *s && IsSpace(*end)) {
        end--;
    }
    *(end + 1) = '\0';
}

void Session::CheckLines()
{
    for (unsigned int i = 0; i < usage; i++) {
        if (buffer[i] == '\n') {
            buffer[i] = '\0';
            if (i > 0 && buffer[i - 1] == '\r') {
                buffer[i - 1] = '\0';
            }
            ProcessLine(buffer);
            usage -= i + 1;
            memmove(buffer, buffer + i + 1, usage);
            CheckLines();
            return;
        }
    }
}
