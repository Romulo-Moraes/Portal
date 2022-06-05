#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <TlHelp32.h>
#include <io.h>
#include <signal.h>

int main(){
    STARTUPINFO Info;
    PROCESS_INFORMATION procInfo;
    memset(&Info, 0, sizeof(Info));
    Info.cb = sizeof(Info);
    
    Info.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    Info.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    Info.hStdError = GetStdHandle(STD_ERROR_HANDLE);
    if(CreateProcess(NULL,"cmd.exe",NULL,NULL,TRUE,0,NULL,NULL,&Info,&procInfo) == 0){
        puts("Fail!");
    }
    puts("Hello?");
    DWORD CmdExitProcess = 0;

    HANDLE ProcessHandler = OpenProcess(PROCESS_QUERY_INFORMATION,0,procInfo.dwProcessId);
    while(1){
        GetExitCodeProcess(ProcessHandler,&CmdExitProcess);
        if(CmdExitProcess != STILL_ACTIVE){
            puts("Cmd finished!");
            break;
        }
        Sleep(1000);
    }

    CloseHandle(ProcessHandler);

}