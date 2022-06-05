from io import SEEK_END, SEEK_SET
from msilib.schema import File
import os
import socket
s = socket.socket()
s.bind(("localhost", 8080))
s.listen(1)
c,a = s.accept()
filetosend = open("main.exe", "rb")
size = 0
filetosend.seek(0,SEEK_END)
size = filetosend.tell()
filetosend.seek(0,SEEK_SET)
c.send(bytes(f"UploadFile \"./salve.exe\" {size}","utf8"))
data = filetosend.read(1024)
while data:
    print("Sending...")
    c.send(data)
    data = filetosend.read(1024)
filetosend.close()
print("Done Sending.")
c.shutdown(2)
c.close()