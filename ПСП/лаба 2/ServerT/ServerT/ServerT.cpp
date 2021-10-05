#include <iostream>
#include "Winsock2.h"
using namespace std;
#pragma comment(lib, "WS2_32.lib")

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
    SOCKET sS; // дескриптор сокета
    WSADATA wsaData; 
    try
    {
        if (WSAStartup(MAKEWORD(2, 0),//[in] версия Windows Sockets
            &wsaData)//[out] указатель на WSADATA
            != 0)
            throw SetErrorMsgText("Startup:", WSAGetLastError());
        if ((sS = socket(AF_INET,//[in] формат адреса
            SOCK_STREAM,//[in] тип сокета
            NULL))//[in] протокол
            == INVALID_SOCKET)
            throw SetErrorMsgText("socket:", WSAGetLastError());
        SOCKADDR_IN serv; // параметры сокета sS
        serv.sin_family = AF_INET; // используется IP-адресация 
        serv.sin_port = htons(2000); // порт 2000
        serv.sin_addr.s_addr = INADDR_ANY; // любой собственный IP-адрес
        if (bind(sS, (LPSOCKADDR)&serv, sizeof(serv)) == SOCKET_ERROR)//установка параметров существующего сокета
            throw SetErrorMsgText("bind:", WSAGetLastError());
        if(listen(sS, SOMAXCONN) == SOCKET_ERROR)//режим прослушивания
            throw SetErrorMsgText("listen:", WSAGetLastError());
        SOCKET cS; // сокет для обмена данными с клиентом
        SOCKADDR_IN clnt; // параметры сокета клиента
        memset(&clnt, 0, sizeof(clnt)); // обнулить память
        int lclnt = sizeof(clnt); // размер SOCKADDR_IN
        if ((cS = accept(sS, (sockaddr*)&clnt, &lclnt)) == INVALID_SOCKET)//создание канала на стороне сервера и создание сокета для обмена данными по этому каналу
            throw SetErrorMsgText("accept:", WSAGetLastError());
        cout << "IP: " << clnt.sin_addr.s_addr;
        cout << endl << "Порт: " << htons(clnt.sin_port)<<endl;
        char ibuf[50], //буфер ввода
            obuf[50] = "sever: принято "; //буфер вывода
        int libuf = 0, //количество принятых байт
            lobuf = 0; //количество отправленных байь
        while (true) {
            if ((libuf = recv(cS, ibuf, sizeof(ibuf), NULL)) == SOCKET_ERROR)
                throw SetErrorMsgText("recv:", WSAGetLastError());
            if (strlen(ibuf)==0) break;
            else {
                cout << ibuf << endl;
                Sleep(50);
                if ((lobuf = send(cS, ibuf, strlen(ibuf) + 1, NULL)) == SOCKET_ERROR)
                    throw SetErrorMsgText("send:", WSAGetLastError());
                if ((libuf = recv(cS, ibuf, sizeof(ibuf), NULL)) == SOCKET_ERROR)
                    throw SetErrorMsgText("recv:", WSAGetLastError());
                cout << ibuf << endl;
            }
        }
        //...........................................................
        if (closesocket(sS) == SOCKET_ERROR)
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

