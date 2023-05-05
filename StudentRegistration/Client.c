#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8888

int main()
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char serial_number[20], registration_number[20], name1[20], name2[20];
    char buffer[1024] = {0};

    // Get input from user
    printf("Enter serial number: ");
    scanf("%s", serial_number);
    printf("Enter registration number: ");
    scanf("%s", registration_number);
    printf("Enter name 1: ");
    scanf("%s", name1);
    printf("Enter name 2: ");
    scanf("%s", name2);

    // Create socket and connect to server
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\nSocket creation error \n");
        return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }

    // Send student data to server
    char message[100];
    sprintf(message, "%s,%s,%s,%s", serial_number, registration_number, name1, name2);
    send(sock, message, strlen(message), 0);
    printf("Student data sent to server\n");

    // Wait for response from server
    valread = read(sock, buffer, 1024);
    printf("%s\n", buffer);

    close(sock);

    return 0;
}
