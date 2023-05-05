// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <unistd.h>

// #define PORT 8888
// #define BUFFER_SIZE 1024

// int main(int argc, char const *argv[])
// {
//     int server_fd, new_socket, valread;
//     struct sockaddr_in address;
//     int opt = 1;
//     int addrlen = sizeof(address);
//     char buffer[BUFFER_SIZE] = {0};
//     char response[200];

//     // Create socket file descriptor
//     if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
//     {
//         perror("socket failed");
//         exit(EXIT_FAILURE);
//     }

//     // Attach socket to the port
//     if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
//     {
//         perror("setsockopt");
//         exit(EXIT_FAILURE);
//     }
//     address.sin_family = AF_INET;
//     address.sin_addr.s_addr = INADDR_ANY;
//     address.sin_port = htons(PORT);

//     // Bind the socket to the specified port
//     if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
//     {
//         perror("bind failed");
//         exit(EXIT_FAILURE);
//     }

//     // Start listening for incoming connections
//     if (listen(server_fd, 3) < 0)
//     {
//         perror("listen");
//         exit(EXIT_FAILURE);
//     }

//     // Wait for incoming connection and process data
//     while (1)
//     {
//         printf("\nWaiting for client connection...\n");
//         if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
//         {
//             perror("accept");
//             exit(EXIT_FAILURE);
//         }

//         // Receive data from client
//         valread = read(new_socket, buffer, BUFFER_SIZE);
//         printf("Received data from client:\n%s\n", buffer);

//         // Parse data and write to file
//         // Parse data and write to file
//         char serial_number[20], registration_number[20], name1[20], name2[20];
//         sscanf(buffer, "%s %s %s %s", serial_number, registration_number, name1, name2);

//         // Check for duplicates
//         FILE *fp = fopen("data3.txt", "r");
//         int duplicate_found = 0;
//         if (fp != NULL)
//         {
//             char line[100];

//             while (fgets(line, sizeof(line), fp))
//             {

//                 char *token = strtok(line, " ");
//                 if (strcmp(token, serial_number) == 0)
//                 {
//                     printf("Duplicate serial number found!\n");
//                     duplicate_found = 1;
//                     break;
//                 }
//                 token = strtok(NULL, " ");
//                 if (strcmp(token, registration_number) == 0)
//                 {
//                     printf("Duplicate registration number found!\n");
//                     duplicate_found = 1;
//                     break;
//                 }
//             }
//             fclose(fp);
//         }

//         // Write to file if no duplicates found
//         if (!duplicate_found)
//         {
//             fp = fopen("data3.txt", "a");
//             if (fp != NULL)
//             {
//                 // Check if file is empty before adding headings
//                 fseek(fp, 0, SEEK_END);
//                 int size = ftell(fp);
//                 if (size == 0)
//                 {
//                     fprintf(fp, "%-20s%-20s%-20s%-20s\n", "Serial Number", "Registration Number", "Name 1", "Name 2"); // Add column headings with fixed widths
//                 }

//                 fprintf(fp, "%-20s%-20s%-20s%-20s\n", serial_number, registration_number, name1, name2); // Use fixed widths for each column

//                 fclose(fp);
//                 printf("Data written to file successfully!\n");
//                 strcpy(response, "Data saved successfully!\n"); // Update response message
//             }
//         }
//         else
//         {
//             strcpy(response, "Data not saved. Duplicate found!\n"); // Update response message
//         }

//         // Send response to client
//         send(new_socket, response, strlen(response), 0);
//         printf("Response sent to client.\n");

//         close(new_socket);
//     }

//     return 0;
// }
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 8888
#define BUFFER_SIZE 1024

int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char response[200];

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Attach socket to the port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the specified port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Start listening for incoming connections
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    // Wait for incoming connection and process data
    while (1)
    {
        printf("\nWaiting for client connection...\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        int pid = fork();
        if (pid < 0) // Fork failed
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0) // Child process
        {
            // Receive data from client
            valread = read(new_socket, buffer, BUFFER_SIZE);
            printf("Received data from client:\n%s\n", buffer);

            // Parse data and write to file
            char serial_number[20], registration_number[20], name1[20], name2[20];
            sscanf(buffer, "%s %s %s %s", serial_number, registration_number, name1, name2);

            // Check for duplicates
            FILE *fp = fopen("data3.txt", "r");
            int duplicate_found = 0;
            if (fp != NULL)
            {
                char line[100];

                while (fgets(line, sizeof(line), fp))
                {

                    char *token = strtok(line, " ");
                    if (strcmp(token, serial_number) == 0)
                    {
                        printf("Duplicate serial number found!\n");
                        duplicate_found = 1;
                        break;
                    }
                    token = strtok(NULL, " ");
                    if (strcmp(token, registration_number) == 0)
                    {
                        printf("Duplicate registration number found!\n");
                        duplicate_found = 1;
                        break;
                    }
                }
                fclose(fp);
            }

            // Write to file if no duplicates found
            if (!duplicate_found)
            {
                fp = fopen("data3.txt", "a");
                if (fp != NULL)
                {
                    // Check if file is empty before adding headings
                    fseek(fp, 0, SEEK_END);
                    int size = ftell(fp);
                    if (size == 0)
                    {
                        fprintf(fp, "%-20s%-20s%-20s%-20s\n", "Serial Number", "Registration Number", "Name 1", "Name 2"); // Add column headings with fixed widths
                    }
                    fprintf(fp, "%-20s%-20s%-20s%-20s\n", serial_number, registration_number, name1, name2); // Write data to file with fixed widths
                    fclose(fp);

                    // Wait for incoming connection and process data
                    while (1)
                    {
                        printf("\nWaiting for client connection...\n");
                        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
                        {
                            perror("accept");
                            exit(EXIT_FAILURE);
                        }

                        // Create child process to handle request
                        pid_t pid = fork();

                        if (pid == -1)
                        {
                            perror("fork");
                            exit(EXIT_FAILURE);
                        }
                        else if (pid == 0) // Child process
                        {
                            // Receive data from client
                            valread = read(new_socket, buffer, BUFFER_SIZE);
                            printf("Received data from client:\n%s\n", buffer);

                            // Parse data and write to file
                            // ...

                            // Send response to client
                            send(new_socket, response, strlen(response), 0);
                            printf("Response sent to client.\n");

                            close(new_socket);
                            exit(EXIT_SUCCESS);
                        }
                        else // Parent process
                        {
                            close(new_socket);
                        }
                    }
                }
            }
        }
    }
}
