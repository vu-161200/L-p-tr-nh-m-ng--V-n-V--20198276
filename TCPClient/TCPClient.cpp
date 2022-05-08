// TCPClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32")
#pragma warning(disable:4996)

int main()
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(8000);

    system("pause");

    int ret = connect(client, (SOCKADDR*)&addr, sizeof(addr));
    if (ret == SOCKET_ERROR)
    {
        ret = WSAGetLastError();
        printf("Ket noi khong thanh công - %d\n", ret);
        return 1;
    }

    char c[256];

    ret = recv(client, c, sizeof(c), 0);
    if (ret <= 0)
        printf("Lỗi");


    printf("Noi dung tu server gui den la: %s\n", c);


    while (1)
    {
        char msg[1000];
        printf("Nhap noi dung gui den server: ");
        scanf("%s", &msg);
        send(client, msg, strlen(msg), 0);
    }

    closesocket(client);
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
