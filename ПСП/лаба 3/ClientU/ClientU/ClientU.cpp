#include <iostream>
#include "Winsock2.h"
#include <algorithm>
using namespace std;
#pragma comment(lib, "WS2_32.lib")
#pragma warning(disable:4996)

string GetErrorMsgText(int code)    // cформировать текст ошибки 
{
    string msgText;
    switch (code)                      // проверка кода возврата  
    {
    case WSAEINTR:          msgText = "WSAEINTR";         break;
    case WSAEACCES:         msgText = "WSAEACCES";        break;
        //..........коды WSAGetLastError ..........................
    case WSASYSCALLFAILURE: msgText = "WSASYSCALLFAILURE"; break;
    default:                msgText = "***ERROR***";      break;
    };
    return msgText;
};

string  SetErrorMsgText(string msgText, int code)
{
    return  msgText + GetErrorMsgText(code);
};

int main()
{
    setlocale(LC_ALL, "Russian");
    WSADATA wsaData;
    try
    {
        if (WSAStartup(MAKEWORD(2, 0),//[in] версия Windows Sockets
            &wsaData)//[out] указатель на WSADATA
            != 0)
            throw SetErrorMsgText("Startup:", WSAGetLastError());
        SOCKET cC; // серверный сокет
        if ((cC = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
            throw SetErrorMsgText("socket:", WSAGetLastError());
        SOCKADDR_IN serv; // параметры сокета сервера
        serv.sin_family = AF_INET; // используется IP-адресация 
        serv.sin_port = htons(2000); // TCP-порт 2000
        serv.sin_addr.s_addr = inet_addr("127.0.0.1"); // адрес сервера
        char ibuf[50];
        int lc = sizeof(serv);
        int lobuf = 0; //количество отправленных
        for (int i = 1; i <= 100; i++) {
            char obuf[50] = "Hello from ClientU"; //буфер вывода
            int n = i;
            char num[4] = "";
            while (n != 0) {
                num[strlen(num)] = (n % 10) + '0';
                n /= 10;
            }
            for (int j = strlen(num) - 1; j >= 0; j--) {
                obuf[strlen(obuf)] = num[j];
            }
            if ((lobuf = sendto(cC, obuf, strlen(obuf) + 1, NULL,
                (sockaddr*)&serv, sizeof(serv))) == SOCKET_ERROR)
                throw SetErrorMsgText("recv:", WSAGetLastError());
            if (lobuf = recvfrom(cC, ibuf, sizeof(ibuf), NULL, (sockaddr*)&serv, &lc) == SOCKET_ERROR)
                throw SetErrorMsgText("send:", WSAGetLastError());
            cout << ibuf << endl;
            char buf1[4] = "";
            while (ibuf[strlen(ibuf) - 1] >= '0' && ibuf[strlen(ibuf) - 1] <= 9 + '0') {
                buf1[strlen(buf1)] = ibuf[strlen(ibuf) - 1];
                ibuf[strlen(ibuf) - 1] = char();
            }
            int f = strlen(buf1);
            reverse(buf1, buf1 + f);
            int value = atoi(buf1);
            value++;
            itoa(value, buf1, 10);
            strcat(ibuf, buf1);
            if ((lobuf = sendto(cC, ibuf, strlen(ibuf) + 1, NULL,
                (sockaddr*)&serv, sizeof(serv))) == SOCKET_ERROR)
                throw SetErrorMsgText("recv:", WSAGetLastError());
        }
        char bto[50] = "";
        if ((lobuf = sendto(cC, bto, strlen(bto) + 1, NULL,
            (sockaddr*)&serv, sizeof(serv))) == SOCKET_ERROR)
            throw SetErrorMsgText("recv:", WSAGetLastError());
        //...........................................................
        if (closesocket(cC) == SOCKET_ERROR)
            throw SetErrorMsgText("closesocket:", WSAGetLastError());
        if (WSACleanup() == SOCKET_ERROR)
            throw SetErrorMsgText("Cleanup:", WSAGetLastError());
    }
    catch (string errorMsgText)
    {
        cout << endl << errorMsgText;
    }
    return 0;
}