#include <windows.h> 
#include <tchar.h>
#include <stdio.h> 
#include <strsafe.h>

HANDLE g_hChildStd_IN_Rd = NULL;
HANDLE g_hChildStd_IN_Wr = NULL;
HANDLE g_hChildStd_OUT_Rd = NULL;
HANDLE g_hChildStd_OUT_Wr = NULL;
HANDLE writeFileHandler = NULL;


int main(){
    SECURITY_ATTRIBUTES saAttr;


    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES); 
    saAttr.bInheritHandle = TRUE; 
    saAttr.lpSecurityDescriptor = NULL; 

    if ( ! CreatePipe(&g_hChildStd_OUT_Rd, &g_hChildStd_OUT_Wr, &saAttr, 0) ) 
      puts("StdoutRd CreatePipe");

// Ensure the read handle to the pipe for STDOUT is not inherited.


// Create a pipe for the child process's STDIN. 
 
   if (! CreatePipe(&g_hChildStd_IN_Rd, &g_hChildStd_IN_Wr, &saAttr, 0)) 
      puts("Stdin CreatePipe");

// Ensure the write handle to the pipe for STDIN is not inherited. 
 

   

    // Create child process
    STARTUPINFO Info;
    PROCESS_INFORMATION ProcInfo;
    ZeroMemory( &ProcInfo, sizeof(PROCESS_INFORMATION) );
    ZeroMemory( &Info, sizeof(STARTUPINFO) );


    // Set up members of the PROCESS_INFORMATION structure. 
 
   ZeroMemory( &ProcInfo, sizeof(PROCESS_INFORMATION) );
 
// Set up members of the STARTUPINFO structure. 
// This structure specifies the STDIN and STDOUT handles for redirection.
 
   ZeroMemory( &Info, sizeof(STARTUPINFO) );
   Info.cb = sizeof(STARTUPINFO); 
   Info.hStdError = g_hChildStd_OUT_Wr;
   Info.hStdOutput = g_hChildStd_OUT_Wr;
   Info.hStdInput = g_hChildStd_IN_Rd;
   Info.dwFlags |= STARTF_USESTDHANDLES;

    if(CreateProcess(NULL,"cmd.exe",NULL,NULL,TRUE,0,NULL,NULL,&Info,&ProcInfo) == 0){
        puts("fffffff");
    }


    writeFileHandler = CreateFile(
       "./output.txt", 
       GENERIC_WRITE, 
       0, 
       NULL, 
       CREATE_ALWAYS, 
       FILE_ATTRIBUTE_NORMAL, 
       NULL); 

    if(writeFileHandler == NULL){
        puts("dddddd");
    }

    char inputBuffer[128] = {0};
    char ToChilInput[] = "dir";
    DWORD opa;
    if(WriteFile(g_hChildStd_IN_Wr,"dir",3,&opa,NULL) == 0){
        puts("ccccc");
    }


    char ToChildOutput[128] = {0};
    if(ReadFile(g_hChildStd_OUT_Rd,ToChildOutput,120,&opa,NULL) == 0){
        puts("bbbbb");
    }


    if(WriteFile(writeFileHandler,ToChildOutput,strlen(ToChildOutput),&opa,NULL) == 0){
        puts("aaaaaa");
    }


    return 0;
}