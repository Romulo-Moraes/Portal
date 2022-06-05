#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>
#include <stdio.h>
#include <WS2tcpip.h>
#include <stdlib.h>

#pragma comment(lib, "Ws2_32.lib")

int main(){
    SOCKET ClientSocket = INVALID_SOCKET;
    struct addrinfo *ptr,*result,hint;

    WSADATA Data;
    WSAStartup(MAKEWORD(2,2),&Data);

    FILE *f = fopen("./programinha.exe","wb");
    ZeroMemory(&hint,sizeof(hint));
    hint.ai_protocol = IPPROTO_TCP;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_family = AF_UNSPEC;
    getaddrinfo("127.0.0.1","8080",&hint,&result);

    ptr = result;

    ClientSocket = socket(ptr->ai_family,ptr->ai_socktype,ptr->ai_protocol);

    if(ClientSocket == INVALID_SOCKET){
        printf("Invalid sock\n");
        return 0;
    }

    if(connect(ClientSocket,ptr->ai_addr,ptr->ai_addrlen) == SOCKET_ERROR){
        printf("Cant connect\n");
    }
    char dataChunk[1025] = {0};

    char filesize[12] = {0};
    int filesizeAsNumber = 0;

    recv(ClientSocket,filesize,11,0);


    filesizeAsNumber = atoi(filesize);
    printf("%d\n",filesizeAsNumber);
    int ReadBytes = 0;


    while(filesizeAsNumber > 0 && (ReadBytes = recv(ClientSocket,dataChunk,1024,0)) != SOCKET_ERROR){
        
        fwrite(dataChunk,1,ReadBytes,f);
        filesizeAsNumber -= ReadBytes;
        ZeroMemory(dataChunk,1024);

    }
    fclose(f);


    return 0;
}