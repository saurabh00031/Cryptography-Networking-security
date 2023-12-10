// #include <iostream>
// #include <string>
// #include <sstream>
// #include <cstring>
// #include <cmath>
// #include <netinet/in.h>
// #include <sys/socket.h>
// #include <unistd.h>
// #include<bits/stdc++.h>

// int main() {
//     int client_socket;
//     struct sockaddr_in server_addr;

//     client_socket = socket(AF_INET, SOCK_STREAM, 0);

//     server_addr.sin_family = AF_INET;
//     server_addr.sin_port = htons(12345);
//     server_addr.sin_addr.s_addr = INADDR_ANY;

//     connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));

//     char server_key_buffer[1024];
//     recv(client_socket, server_key_buffer, sizeof(server_key_buffer), 0);
//     std::string server_key_data(server_key_buffer);

//     int prime, base, client_partial_key;
//     std::istringstream server_key_stream(server_key_data);
//     server_key_stream >> prime;
//     server_key_stream.ignore(1);
//     server_key_stream >> base;
//     server_key_stream.ignore(1);
//     server_key_stream >> client_partial_key;

//     int client_private_key = std::rand() % (prime - 1) + 1;
//     int client_partial_key = std::pow(base, client_private_key);
//     client_partial_key = fmod(client_partial_key, prime);

//     send(client_socket, std::to_string(client_partial_key).c_str(), std::to_string(client_partial_key).size(), 0);

//     int shared_key = std::pow(server_partial_key, client_private_key);
//     shared_key = fmod(shared_key, prime);

//     std::cout << "Shared Key: " << shared_key << std::endl;

//     close(client_socket);

//     return 0;
// }











#include <iostream>
#include <cmath>
#include <winsock2.h>



long long p = 17; // Large prime number (public)
long long alpha = 5;  // Primitive root modulo p (public)


long long powM(long long a, long long b, long long n){
    if (b == 1){
        return a % n;
    }
    long long x = powM(a, b / 2, n);
    x = (x * x) % n;
    if (b % 2){
        x = (x * a) % n;
    }
    return x;
}


int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock" << std::endl;
        return -1;
    }


    SOCKET clientSocket;
    struct sockaddr_in serverAddress;


    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Error creating socket" << std::endl;
        WSACleanup();
        return -1;
    }


    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1"); //Localhost


    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Error connecting to Bob" << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return -1;
    }


    int xa = 4; // Alice's private key


    // Alice computes A = (alpha^xa) % p
    int A = powM(alpha, xa, p);
    std::cout << "Alice computes A: " << A << std::endl;


    // Send Alice's public value A to Bob
    send(clientSocket, (char*)&A, sizeof(A), 0);
    std::cout << "Sent Alice's public value A to Bob" << std::endl;


    // Receive Bob's public value B
    int B;
    recv(clientSocket, (char*)&B, sizeof(B), 0);
    std::cout << "Received Bob's public value B: " << B << std::endl;


    // Calculate the shared secret key
    int shared_key_alice = powM(B, xa, p);
    std::cout << "Shared key calculated by Alice: " << shared_key_alice << std::endl;


    closesocket(clientSocket);
    WSACleanup();


    return 0;
}
