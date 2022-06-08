from importlib.resources import path
from io import SEEK_END, SEEK_SET
from msilib.schema import RemoveFile
from os import popen, remove
import os.path

HARDCODE_FILE_NAME = "./asdfswoigjgjigisjgesgkojrieorjger.txt"
TEXT_CHUNK_SIZE = 128

def CommandParser(CommandToParse, ClientSocket):
    if(CommandToParse != ""):
        PrincipalCommand = CommandToParse.split(" ")[0]

        if(PrincipalCommand == "WriteFile"):
            if(len(CommandToParse.split("\"")) == 3):
                RemoteFileName = CommandToParse.split("\"")[1]
                if(RemoteFileName != ""):
                    RemoteFileName = "\"" + RemoteFileName + "\""
                    CommandToParse = PrincipalCommand + " " + RemoteFileName

                    if(os.path.exists(HARDCODE_FILE_NAME)):
                        remove(HARDCODE_FILE_NAME)
                    FileHandler = open(HARDCODE_FILE_NAME,"w")
                    FileHandler.close()

                    popen(f"notepad {HARDCODE_FILE_NAME}","r")

                    input("Press enter when finish of write your text, don't forget to save!")

                    FileHandler = open(HARDCODE_FILE_NAME,"r",encoding="utf-8")
                    FileLines = FileHandler.readlines()
            
                    FileText = ""

                    for Line in FileLines:
                        FileText += Line

                    CommandToParse += " " + str(len(FileText)) + " " + FileText 
                    ClientSocket.send(bytes(CommandToParse,"utf8"))
                else:
                    print("You need type a remote file name")
            else:
                print("Use: WriteFile \"remote file name\"")   
        else:
            if(PrincipalCommand == "UploadFile"):

                if(len(CommandToParse.split(" ")) == 3):
                    LocalFileName = CommandToParse.split("\"")[1]
                    RemoteFileName = CommandToParse.split("\"")[3]

                    if(LocalFileName != "" and RemoteFileName != ""):
                        if(os.path.exists(LocalFileName)):
                            FileHandler = open(LocalFileName,"rb")
                            FileHandler.seek(0,SEEK_END)
                            FileSize = FileHandler.tell()
                            FileHandler.seek(SEEK_SET)

                            ClientSocket.send(bytes(f"UploadFile {RemoteFileName} {FileSize}","utf8"))

                            Data = FileHandler.read(1024)

                            while Data:
                                ClientSocket.send(Data)
                                Data = FileHandler.read(1024)

                            FileHandler.close()
                        else:
                            print("Local file not exists")
                    else:
                        print("Use: UploadFile \"local file name\" \"remote file name\"")
                    
                else:
                    print("Use: UploadFile \"<local file name>\" \"remote file name of distiny")

            else:
                ClientSocket.send(bytes(CommandToParse,"utf8"))