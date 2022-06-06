from threading import Thread
from socket import *
import execute_command

SERVER_BIND_ADDRESS = "0.0.0.0"
SERVER_BIND_PORT = 8080
RECV_BUFFER_SIZE = 128

def ReceiveData(ClientSocket):
    while True:
        TcpBytes = ""
        TcpBytes = ClientSocket.recv(RECV_BUFFER_SIZE)
        if(bytes.decode(TcpBytes,"ISO-8859-1") != ""):
            print(bytes.decode(TcpBytes,"ISO-8859-1"),end="")

def main():
    ServerSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

    ServerSocket.bind((SERVER_BIND_ADDRESS,SERVER_BIND_PORT))

    ServerSocket.listen(0)

    [ClientSocket,ClientAddress] = ServerSocket.accept()

    print("Connection received!")

    ReceiveThread = Thread(target=ReceiveData,args=(ClientSocket,))
    ReceiveThread.start()

    while True:
        CommandToSend = input("")
        if(CommandToSend != ""):
            execute_command.CommandParser(CommandToSend,ClientSocket)

if(__name__ == "__main__"):
    main()