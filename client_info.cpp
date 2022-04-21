#include <stdio.h>
#include <WinSock2.h>
#include <string>

#pragma comment(lib, "ws2_32")
#pragma warning(disable:4996)

int main()
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    //nhap địa chỉ IP và port
    char IP[100];
    int port;
    printf("nhap dia chi IP: ");
    fgets(IP, sizeof(IP), stdin);
    printf("nhap cong ket noi (port): ");
    scanf("%d", &port);
       
    
    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(IP);
    addr.sin_port = htons(port);

    system("pause");

    int ret = connect(client, (SOCKADDR*)&addr, sizeof(addr));
    if (ret == SOCKET_ERROR)
    {
        ret = WSAGetLastError();
        printf("Ket noi khong thanh cong - %d\n", ret);
        return 1;
    }
    //lấy tên máy tính
    const char* str = "Ten may tinh la: ";
    send(client, str, strlen(str), 0);
    char name[256];
    DWORD size = sizeof(name);
    GetComputerNameA(name, &size);
    send(client, name, size, 0);

    //lấy danh sách ổ đĩa
    const char* str2 = "\nDanh sach cac o dia trong may tinh: ";
    send(client, str2, strlen(str2), 0);
    // Buffer length
    DWORD mydrives = 20;
    // Buffer for drive string storage
    char lpBuffer[18];
    
    DWORD test;
    test = GetLogicalDriveStrings(mydrives, (LPWSTR)lpBuffer);

    for (int i = 0; i < sizeof(lpBuffer); i++) {
        const char buf2 = lpBuffer[i];
        printf("%c", buf2);
        send(client, &buf2, sizeof(buf2), 0);
    }

    //kích thước các



    printf("\n");
   


    

    closesocket(client);
    WSACleanup();
}