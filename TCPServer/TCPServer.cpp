// TCPServer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32")
#pragma warning(disable:4996)

int main(int argc, char* argv[])
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);
    SOCKET listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(8000);

    bind(listener, (SOCKADDR*)&addr, sizeof(addr));

    listen(listener, 5);
    SOCKET client = accept(listener, NULL, NULL);

    FILE* helloClient;
    FILE* testClient;
    char c[256];
    helloClient = fopen("helloClient.txt", "r");
    testClient = fopen("test.txt", "a");
    fgets(c, sizeof(c), helloClient);
    send(client, c, sizeof(c), 0);
    while (1)
    {
        char msg[1000];
        int ret = recv(client, msg, sizeof(msg), 0);
        if (ret <= 0)
        {
            system("pause");
            return 1;
        }
        if (ret < 1000)
            msg[ret] = 0;
        fprintf(testClient, "%s\n", msg);
    }

    fclose(helloClient);
    fclose(testClient);

    closesocket(client);
    closesocket(listener);
    WSACleanup();
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
