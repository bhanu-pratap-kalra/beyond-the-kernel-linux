#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <thread>
#include <vector>

constexpr int BUFFER_SIZE = 1024;

using namespace std;

int usage()
{
    cout << "Invalid arguments\n";
    cout << "Send requesdt as ./simple_client <server_port> <number_of_client_threads>\n";
    return -1;
}

void client(int num_client, int port)
{
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (-1 == client_fd)
    {
        cout << "Failed to create socket for client " << num_client << "\n";
	return;
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    if (-1 == connect(client_fd, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr)))
    {
        cout << "Failed to connect for client " << num_client << "\n";
	close(client_fd);
	return;
    }

    string message = "This is a message to simple epoll server by client " + std::to_string(num_client);

    ssize_t bytes_written = write(client_fd, message.c_str(), message.size());

    if (-1 == bytes_written)
    {
        cout << "Error in writing message to server\n";
	close(client_fd);
	return;
    }

    char buffer [BUFFER_SIZE]{};

    ssize_t bytes_read = read(client_fd, buffer, BUFFER_SIZE);

    if (bytes_read > 0)
    {
        cout << "Message received from server by client " << num_client << "\n";
    }

    close(client_fd);
}

int main(int argc, char* argv[])
{
    if (3 != argc)
    {
	return usage();
    }

    int port = -1;
    int num_clients = -1;

    try
    {
        port = stoi(argv[1]);
	num_clients = stoi(argv[2]);
    }
    catch(...)
    {
        return usage();
    }

    std::vector<std::thread> client_threads;

    for (int num_thread = 0; num_thread < num_clients; num_thread++)
    {
        client_threads.emplace_back(client, num_thread, port);
    }

    for (auto& thread : client_threads)
    {
        thread.join();
    }

    return 0;
}
