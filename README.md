# File-Transfer

This is socket programming in python, that is written with reference from Socket-Programming from gulshan-mittal
https://github.com/gulshan-mittal/Socket-Programming

## How to use (.py file)

1. Place the file (with an extension) (not a folder) into the Data folder
2. Run the CAserver.py with the PC containing the file
3. Run the CAclientNP.py/CAclientP.py with the PC receiving the file (another PC)
4. Key in the IP address that appears on the Server program into the Client program

## How to build (.exe file)

1. Run "pip install auto-py-to-exe" in cmd prompt
2. Run "auto-py-to-exe" in cmd prompt
3. Compile and build CAserver.exe, CAclientNP.exe and CAclientP.exe with CAserver.py, CAclientNP.py and CAclientP.py respectively. (A sample image is shown below.)
![Sample Image](sample.PNG)

## How to use (.exe file)

1. Place the file (with an extension) (not a folder) into the Data folder
2. Run the CAserver.exe with the PC containing the file
3. Run the CAclientNP.exe/CAclientP.exe with the PC receiving the file (another PC)
4. Key in the IP address that appears on the Server program into the Client program

### Take Note (Some problems encountered):

1. Please ensure that the firewall (windows or antivirus) is not blocking the internet connection of your program (Meaning, check the program or python has access through the firewall)
2. Please also make sure that the default program for the .py file is python so that the .py file can access the dir via scandir() when you open it with python, not idle (Meaning, if idle.bat is the default program, and the .py file is run with python, the program is not able to access the Data folder.)
3. Please take note that MacOS is not supported.
