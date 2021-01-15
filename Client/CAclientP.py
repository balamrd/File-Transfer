from socket import *
from sys import * 
from time import *



def recvFile(s, request):
    fb = open(request, 'wb')
    print('Receiving Data...')
    while True:
        response = recvData(s)
        if b'END OF FILE CHECK' in response:
            response = response[:len(response)-len(b'END OF FILE CHECK')]
            if response:
                fb.write(response)
            break
        else:
            fb.write(response)
    fb.close()
    print('Successfully got the file:', request)

def sendData(s, request):
    try:
        s.sendall(request)
    except error as e:
        print('Error sending data:', e)
        exit(1)
    
    
def recvData(s):
    try:
        response = s.recv(4096) # may change to a function to receive data
    except error as e:
        print('Error receiving data:', e)
        exit(1)
    return response

def socketinit(host, port):
    try:
        s = socket(AF_INET, SOCK_STREAM)
    except error as e:
        print('Error creating server socket:', e)
        exit(1)
    try:
        s.connect((host, port))
    except:
        print('Client and Server are not having the same IP address')
        host = input('New Server Address: ')
        try:
            s.connect((host, port))
        except gaierror as e:
            print('Address-related error connecting to server:', e)
            exit(1)
        except error as e:
            print('Connection Error:', e)
            exit(1)
    return s, host

def get_ip():
    s = socket(AF_INET, SOCK_DGRAM)
    try:
        # doesn't even have to be reachable
        s.connect(('10.255.255.255', 1))
        IP = s.getsockname()[0]
    except:
        IP = '127.0.0.1'
    finally:
        s.close()
    return IP

if __name__ == '__main__':
    host = get_ip()
    port = 9641           

    s, host = socketinit(host, port)

    request = 'Requesting Persistent connection...'
    print(request)
    request = request.encode('utf-8')
    sendData(s, request)
    response = recvData(s)
    response = response.decode('utf-8')

    lst = response.split('|?!~') 
    print('There are', str(len(lst)), 'objects in the server')
    print(lst)

    # Initial time in milliseconds before file transfer 
    initial_time = int(round(time() * 1000))

    for i in range(len(lst)):

        print('Requesting', lst[i])
        lst[i] = lst[i].encode('utf-8')
        sendData(s, lst[i])
        lst[i] = lst[i].decode('utf-8')
        recvFile(s, lst[i])
    
    s.close()
    print('connection closed')
    
    # Final time in milliseconds after closing of the connection
    final_time = int(round(time() * 1000))

    print(final_time - initial_time)
