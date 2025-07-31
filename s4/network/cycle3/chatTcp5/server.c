#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#define PORT 8085
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024
int clients[MAX_CLIENTS] = {0};
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
void broadcast_message(char *message, int sender_fd)
{
    pthread_mutex_lock(&lock);
    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        if (clients[i] != 0 && clients[i] != sender_fd)
        {
            send(clients[i], message, strlen(message), 0);
        }
    }
    pthread_mutex_unlock(&lock);
}
void *handle_client(void *arg)
{
    int client_fd = *(int *)arg;
    char buffer[BUFFER_SIZE];
    int bytes_received;
    while ((bytes_received = recv(client_fd, buffer, BUFFER_SIZE, 0)) > 0)
    {
        buffer[bytes_received] = '\0';
        printf("Client %d: %s", client_fd, buffer);
        broadcast_message(buffer, client_fd);
    }
    pthread_mutex_lock(&lock);
    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        if (clients[i] == client_fd)
        {
            clients[i] = 0;
            break;
        }
    }
    pthread_mutex_unlock(&lock);
    close(client_fd);
    free(arg);
    pthread_exit(NULL);
}
int main()
{
    int server_fd, new_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size = sizeof(client_addr);
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_fd, MAX_CLIENTS);
    printf("Chat server started on port %d...\n", PORT);
    while (1)
    {
        new_socket = accept(server_fd, (struct sockaddr *)&client_addr, &addr_size);
        pthread_mutex_lock(&lock);
        int added = 0;
        for (int i = 0; i < MAX_CLIENTS; i++)
        {
            if (clients[i] == 0)
            {
                clients[i] = new_socket;
                added = 1;
                break;
            }
        }
        pthread_mutex_unlock(&lock);
        if (!added)
        {
            printf("Server full. Connection refused.\n");
            close(new_socket);
            continue;
        }
        pthread_t thread;
        int *client_sock = malloc(sizeof(int));
        *client_sock = new_socket;
        pthread_create(&thread, NULL, handle_client, client_sock);
    }
    return 0;
}