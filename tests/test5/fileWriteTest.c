#include <stdio.h>
#include <Windows.h>

char buffer[128] = {0};

VOID CALLBACK ReadCb(DWORD dwErrorCode,DWORD dwNumberOfBytesTransfered,LPOVERLAPPED lpOverlapped)
{
    printf("fuck");
}


int main(){
    OVERLAPPED ovStruct;
    HANDLE File = CreateFile("./copy.c",GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_FLAG_OVERLAPPED,NULL);
    if(File == NULL){
        puts("aff :(");
        return 1;
    }
    ReadFileEx(File,buffer,127,&ovStruct,ReadCb);

    Sleep(2000);

    return 0;
}