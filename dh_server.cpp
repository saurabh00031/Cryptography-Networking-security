// #include <iostream>
// #include <string>
// #include <sstream>
// #include <cstring>
// #include <cmath>
// #include <netinet/in.h>
// #include <sys/socket.h>
// #include <unistd.h>

// int getPrimitiveRoot(int prime) {
//     for (int root = 2; root < prime; root++) {
//         int result = 1;
//         bool found = false;
//         for (int i = 1; i < prime - 1; i++) {
//             result = (result * root) % prime;
//             if (result == 1) {
//                 found = true;
//                 break;
//             }
//         }
//         if (!found) {
//             return root;
//         }
//     }
//     return -1; // No primitive root found
// }

// int main() {
//     int server_socket, client_socket;
//     struct sockaddr_in server_addr, client_addr;

//     server_socket = socket(AF_INET, SOCK_STREAM, 0);

//     server_addr.sin_family = AF_INET;
//     server_addr.sin_port = htons(12345);
//     server_addr.sin_addr.s_addr = INADDR_ANY;

//     bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
//     listen(server_socket, 5);

//     std::cout << "Server waiting for connections..." << std::endl;

//     client_socket = accept(server_socket, nullptr, nullptr);

//     int prime, base;
//     std::cout << "Enter a prime number: ";
//     std::cin >> prime;
//     base = getPrimitiveRoot(prime);

//     int server_private_key = std::rand() % (prime - 1) + 1;
//     int server_partial_key = std::pow(base, server_private_key);
//     server_partial_key = fmod(server_partial_key, prime);

//     std::ostringstream server_key_stream;
//     server_key_stream << prime << "," << base << "," << server_partial_key;
//     std::string server_key_data = server_key_stream.str();

//     send(client_socket, server_key_data.c_str(), server_key_data.size(), 0);

//     char client_key_buffer[1024];
//     recv(client_socket, client_key_buffer, sizeof(client_key_buffer), 0);
//     int client_partial_key = std::stoi(client_key_buffer);

//     int shared_key = std::pow(client_partial_key, server_private_key);
//     shared_key = fmod(shared_key, prime);

//     std::cout << "Shared Key: " << shared_key << std::endl;

//     close(client_socket);
//     close(server_socket);

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


    SOCKET serverSocket;
    struct sockaddr_in serverAddress;
    SOCKET clientSocket;
    struct sockaddr_in clientAddress;


    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Error creating socket" << std::endl;
        WSACleanup();
        return -1;
    }


    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;


    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Error binding to port" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return -1;
    }


    listen(serverSocket, 1);
    std::cout << "Bob is waiting for Alice to connect..." << std::endl;


    int clientAddress_size = sizeof(clientAddress);
    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddress_size);


    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Error accepting the connection" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return -1;
    }


    int xb = 6; // Bob's private key


    // Receive Alice's public value A
    int A;
    recv(clientSocket, (char*)&A, sizeof(A), 0);
    std::cout << "Received Alice's public value A: " << A << std::endl;


    // Bob computes B = (alpha^xb) % p
    int B = powM(alpha, xb, p);
    std::cout << "Bob computes B: " << B << std::endl;


    // Send Bob's public value B to Alice
    send(clientSocket, (char*)&B, sizeof(B), 0);
    std::cout << "Sent Bob's public value B to Alice" << std::endl;


    // Calculate the shared secret key
    int shared_key_bob = powM(A, xb, p);
    std::cout << "Shared key calculated by Bob: " << shared_key_bob << std::endl;


    closesocket(serverSocket);
    closesocket(clientSocket);
    WSACleanup();


    return 0;
}

