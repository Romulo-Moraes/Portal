from io import SEEK_END, SEEK_SET
from threading import Thread
from socket import *
from time import sleep


ServerSock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)

ServerSock.bind(("0.0.0.0",8080))

ServerSock.listen(0)

[cSock,addr] = ServerSock.accept()

print("Accepted!");

FileHandler = open("./program.exe","rb")
FileHandler.seek(0,SEEK_END)
FileSize = FileHandler.tell()
FileHandler.seek(0,SEEK_SET)

cSock.send(bytes(f"{FileSize}","utf8"))

sleep(1)

Data = FileHandler.read(1024)
while Data:
    print(Data)
    cSock.send(Data)
    Data = FileHandler.read(1024)

cSock.shutdown(0)
cSock.close()
ServerSock.close()