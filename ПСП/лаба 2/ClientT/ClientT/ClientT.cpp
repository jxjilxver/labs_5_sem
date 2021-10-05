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
        if ((cC = socket(AF_INET, SOCK_STREAM, NULL)) == INVALID_SOCKET)
            throw SetErrorMsgText("socket:", WSAGetLastError());
        SOCKADDR_IN serv; // параметры сокета сервера
        serv.sin_family = AF_INET; // используется IP-адресация 
        serv.sin_port = htons(2000); // TCP-порт 2000
        serv.sin_addr.s_addr = inet_addr("127.0.0.1"); // адрес сервера
        if ((connect(cC, (sockaddr*)&serv, sizeof(serv))) == SOCKET_ERROR)
            throw SetErrorMsgText("connect:", WSAGetLastError());
        
        int libuf = 0, //количество принятых байт
            lobuf = 0; //количество отправленных байт
        for (int i = 1; i <= 100; i++) {
            char bto[50] = "Ты опять выходишь на связь?";
            int n = i;
            char num[4] = "";
            while (n != 0) {
            num[strlen(num)] = (n % 10)+'0';
            n /= 10;
            }
            for (int j = strlen(num) - 1; j >= 0; j--) {
                bto[strlen(bto)] = num[j];
            }
            if ((lobuf = send(cC, bto, strlen(bto) + 1, NULL)) == SOCKET_ERROR)
                throw SetErrorMsgText("send:", WSAGetLastError());
            Sleep(50);
            if ((libuf = recv(cC, bto, sizeof(bto), NULL)) == SOCKET_ERROR)
                throw SetErrorMsgText("recv:", WSAGetLastError());
            //cout << bto << endl;
            char buf1[4] = "";
            while (bto[strlen(bto) - 1] >= '0' && bto[strlen(bto) - 1] <= 9 + '0') {
                buf1[strlen(buf1)] = bto[strlen(bto) - 1];
                bto[strlen(bto) - 1] = char();
            }
            int f = strlen(buf1);
            reverse(buf1, buf1 + f);
            int value = atoi(buf1);
            value++;
            itoa(value, buf1, 10);
            cout << buf1 << " "<< bto << endl;
            strcat(bto, buf1);
            if ((lobuf = send(cC, bto, strlen(bto) + 1, NULL)) == SOCKET_ERROR)
                throw SetErrorMsgText("send:", WSAGetLastError());
            Sleep(50);
        }
        char bto[50] = "";
        if ((lobuf = send(cC, bto, strlen(bto) + 1, NULL)) == SOCKET_ERROR)
            throw SetErrorMsgText("send:", WSAGetLastError());
        Sleep(50);
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
