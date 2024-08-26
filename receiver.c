#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h> 

#define PORT 8080

int main() {
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    int buffer[1024] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    int n;
    int arr[100];
    printf("Enter the size of array: " );
    scanf("%d", &n);
    printf("Enter the numbers :");
   for(int i =0;i<n;i++){
   scanf("%d" , &arr[i]);
   }

    int message[1024] = {0};
    message[0] = n;
    for (int i = 0; i < n; i++) {
        message[i + 1] = arr[i];
    }

    send(sock, message, sizeof(message), 0);
    printf("Unsorted array sent to server\n");

    valread = read(sock, buffer, 1024);
    n = buffer[0];
    printf("Sorted array received from server: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", buffer[i + 1]);
    }
    printf("\n");

    close(sock);
    return 0;
}

