<div align="center">
    <h1>Portal backdoor</h1>
    <img width="400px" src="./images/ExampleImage.jpeg">
    <p>Created by Rômulo Moraes</p>    
</div>

#

## My responsability for it
This is a toy project to me, but can make some damages with a right level, then if you use this code base for anything else that is not about learn, it's YOUR responsability



### \<===== Project under developement =====\>



## What's this
Portal is a backdoor malware created in C for windows platform, with some features to enable the attacker troll and hack the possible victim computer

## How its work
This program has a client (the malware) and the server (that will command the client), the client made in C and server made in Python. A Tcp connection will be maked between both, trading messages to make the Portal playground.

## Server dependency
The Portal program is not completly dependent of the server made in Python, you can just bind your server with a netcat, but some features like: Upload file and Write file will not be possible to do, but it's a Tcp conversation at all.

## Features of portal backdoor
Here is all features that this malware can do in victim computer.



### Beep Beep
Make a default Windows system beep in remote computer

Use: Beep



### ListProcess
Return all current process in remote computer

Use: ListProcess



### CurrentDirectory
Return the Portal current directory in remote computer

Use: CurrentDirectory



### PortalIntegration
Make that you enter in remote system and accept cmd commands to make anything

Use: PortalIntegration



### FileWrite
Write to a file in remote target

Use: WriteFile \<relative path in remote computer\>

Hint: After send this command (with Python server script) a notepad will pop-up for you write the file text, then you save and press enter in server terminal to send the file content



### FileRead 
Allow you to read a file in remote computer and bring the result to your terminal

Use: FileRead "\<relative path to remote file\>"



### ListDirectory
List the current directory or any path that you pass as argument

Use: ListDirectory . (or) \<custom path\>



### KillProcess
Try kill a process in remote computer

Use KillProcess "\<process name\>"



### BlindCmd
Execute a cmd command and let it go, no inputs, no outputs

Use: BlindCmd \<cmd command here\>



### UploadFile
Upload a local file to remote computer, good for upload your executables and shell scripts

Use: UploadFile "\<local file name\>" "\<remote file name destionation\>"



### FileSize 
Get the size of a specific file in remote system

Use: FileSize "\<remote file name\>"



### MoveFile
Move a file from source location to a destination location

Use: MoveFile "\<remote file name location\>" "\<remote destination location/<nome do arquivo\>\>"

Hint: Is necessary put the file name in the end of destination path, native winapi functions only work in this way




