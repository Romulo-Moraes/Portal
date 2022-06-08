<div align="center">
    <h1>Portal backdoor</h1>
    <img width="400px" src="./images/image.png">
    <p>Created by Rômulo Moraes</p>    
</div>

#

## My responsability for it
This is a toy project to me, but can make some damages with a right level, then if you use this code base for anything else that is not about learn, it's YOUR responsability


<div align="center">
    <h3><===== Project under development =====></h3>
</div>



## What's this
Portal is a backdoor malware created in C for windows platform, with some features to enable the attacker troll and hack the possible victim computer. This is a more project created inspired by the mobile game Hackers : join the cyberwar. Another project inspired by this game is the Battering ram, that's the link: https://github.com/Romulo-Moraes/Battering-ram

## How its work
This program has a client (the malware) and the server (that will command the client), the client made in C and server made in Python. A Tcp connection will be maked between both, trading messages to make the Portal playground.

## Server dependency
The Portal program is not completly dependent of the server made in Python, you can just bind your server with a netcat, but some features like: Upload file and Write file will not be possible to do, but it's a Tcp conversation at all.

## Features of portal backdoor
Here is all features that this malware can do in victim computer.



### Beep Beep
```txt
Make a default Windows system beep in remote computer

Use: Beep
```


### ListProcess
```txt
Return all current process in remote computer

Use: ListProcess
```


### CurrentDirectory
```txt
Return the Portal current directory in remote computer

Use: CurrentDirectory
```


### PortalIntegration
```txt
Make that you enter in remote system and accept cmd commands to make anything

Use: PortalIntegration
```

### WriteFile
```txt
Write to a file in remote target

Use: WriteFile <relative path in remote computer>

Hint: After send this command (with Python server script) a notepad will pop-up for you write the file text, then you save and press enter in server terminal to send the file content
```


### ReadFile
```txt
Allow you to read a file in remote computer and bring the result to your terminal

Use: FileRead "<relative path to remote file>"
```


### ListDirectory
```txt
List the current directory or any path that you pass as argument

Use: ListDirectory . (or) <custom path>
```


### KillProcess
```txt
Try kill a process in remote computer

Use: KillProcess "<process name>"
```


### BlindCmd
```txt
Execute a cmd command and let it go, no inputs, no outputs

Use: BlindCmd <cmd command here>
```


### UploadFile
```txt
Upload a local file to remote computer, good for upload your executables and shell scripts

Use: UploadFile "<local file name>" "<remote file name destionation>"
```


### FileSize 
```txt
Get the size of a specific file in remote system

Use: FileSize "<remote file name>"
```


### MoveFile
```txt
Move a file from source location to a destination location

Use: MoveFile "<remote file name location>" "<remote destination location/<nome do arquivo>>"

Hint: Is necessary put the file name in the end of destination path, native winapi functions only work in this way
```

## More features coming...
The project is under development, so new features will come up to this repository soon

## How to configure for gameplay
To change target connection and host bind is easy, in macros/macros.h has HOST_ADDRESS and HOST_PORT, you can change it to dial to any place in internet. In server/server.py has some constants that control the bind address and port, that is the: SERVER_BIND_ADDRESS and SERVER_BIND_PORT, feel free to change them for any valid value.

### Compiling the client C code
For this project i tried a MINGW that is pretty easy to install and use, but for some cases like Winsockets it sucks, then the best option that i chose is the Microsoft C compiler called as "cl", it comes with the Visual Studio, 2019 in my case, this command is available in Developer Command Prompt and compile with this is as follow:
```txt
cl client.c
```
Then you rename your file for anything that you wan't

### Interpreting the Python script
The server script made in python can be executed by a interpreter with Python 3.10.0 (Tested), or later, and execute it is as follow:
```
py server.py
```
This version of Portal server works better in Windows, because call the "notepad.exe" executable to run "WriteFile" command, but better support will be implemented.






