#include <arpa/inet.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

constexpr int BUFFER_SIZE = 1024;
constexpr int MAX_EVENTS = 100;

using namespace std;

int usage()
{
    cout << "Invalid argument\n";
    cout << "Start the server as ./simple_epoll_server <port>\n";
    return -1;
}

int main(int argc, char* argv[]) 
{
    if (2 != argc)
    {
	return usage();
    }

    int port = -1;

    try
    {
        port = stoi(argv[1]);
    }
    catch(...)
    {
	return usage();
    }
	
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (-1 == server_fd) 
    {
        cout << "Failed to create socket\n";
        return -1;
    }

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (-1 == bind(server_fd, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr))) 
    {
        cout << "Bind failed\n";
        close(server_fd);
        return -1;
    }

    if (-1 == listen(server_fd, SOMAXCONN)) 
    {
        cout << "Listen failed\n";
        close(server_fd);
        return -1;
    }

    int epoll_fd = epoll_create1(0);

    if (-1 == epoll_fd) 
    {
        cout << "Failed to create epoll\n";
        close(server_fd);
        return -1;
    }

    epoll_event server_event{};
    server_event.events = EPOLLIN;
    server_event.data.fd = server_fd;

    if (-1 == epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &server_event)) 
    {
        cout << "epoll registration failed\n";
        close(server_fd);
        close(epoll_fd);
        return -1;
    }

    cout << "Server running on port " << port << "\n";

    epoll_event events[MAX_EVENTS];

    while (true) 
    {
        int event_count = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);

        if (-1 == event_count) 
        {
            cout << "epoll event failed\n";
            break;
        }

        for (int num_event = 0; num_event < event_count; num_event++) 
        {
            int current_fd = events[num_event].data.fd;

            if (current_fd == server_fd) 
            {
                sockaddr_in client_addr{};
                socklen_t client_len = sizeof(client_addr);

                int client_fd = accept(server_fd, reinterpret_cast<sockaddr*>(&client_addr), &client_len);

                if (-1 == client_fd) 
                {
                    cout << "Accept failed\n";
                    continue;
                }

                epoll_event client_event{};
                client_event.events = EPOLLIN;
                client_event.data.fd = client_fd;

                epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &client_event);

                cout << "Client connected with file descriptor : " << client_fd << "\n";
            } 
            else 
            {
                char buffer[BUFFER_SIZE]{};

                ssize_t bytes_read = read(current_fd, buffer, BUFFER_SIZE);

                if (bytes_read <= 0) 
                {
                    cout << "Client disconnected with file descriptor : " << current_fd << "\n";
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, current_fd, nullptr);
                    close(current_fd);
                } 
                else 
                {
                    ssize_t bytes_written = write(current_fd, buffer, bytes_read);

		    if (-1 == bytes_written)
		    {
		        cout << "Failed writing a message back to client\n";
		    }
                }
            }
        }
    }

    close(server_fd);
    close(epoll_fd);

    return 0;
}
