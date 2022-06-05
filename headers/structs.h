struct ChildProcessConfigPackage
{
    HANDLE *ChildStdinWrite, *ChildStdinRead, *ChildStdoutWrite, *ChildStdoutRead;
    SOCKET *ClientSocket;
} ChildConfig;