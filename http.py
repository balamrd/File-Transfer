from socket import *
from sys import *
from os import scandir

def nonPersistentrequest(conn):
    print('Sending', request)
    sendFile(conn, request)
    sendData(conn, b'END OF FILE CHECK')
    print('Done Sending Files')
    conn.close()
    print('Connection Closed')



def Persistentrequest(conn):
    request = recvData(conn)
    while request:
        request = request.decode('utf-8')
        print('Sending', request)
        sendFile(conn, request)
        sendData(conn, b'END OF FILE CHECK')
        print('Done Sending Files')
        request = recvData(conn)
    conn.close()
    print('Connection Closed')


def sendFile(conn, response):
    fb = open('./Data/' + response, 'rb')
    fb_read = fb.read(4096)
    while (fb_read):
        sendData(conn, fb_read)
        fb_read = fb.read(4096)
    fb.close()


def sendData(conn, response):
    try:
        conn.sendall(response)
    except error as e:
        print('Error sending data:', e)
        exit(1)
    
    
def recvData(conn):
    try:
        request = conn.recv(4096) # may change to a function to receive data
    except error as e:
        print('Error receiving data:', e)
        exit(1)
    return request

def socketinit(host, port):
    try :
        s = socket(AF_INET, SOCK_STREAM)
    except error as e:
        print('Error creating server socket:', e)
        exit(1)
    try :
        s.bind((host, port))
    except error as e:
        print('Error in binding host and port:', e)

    return s

def get_ip():
    try :
        s = socket(AF_INET, SOCK_DGRAM)
    except error as e:
        print('Error creating server socket:', e)
        exit(1)
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
    port = 9641      # Port to listen on 

    print(host)

    s = socketinit(host, port)

    s.listen(5) # max client = 5


    while True:
        # Initial time in milliseconds before accepting a connection
        print('Server listening....')


        conn, addr = s.accept()
        conn.settimeout(None) #time to connect to server (before file transfer)
        s.settimeout(10) # idle timeout = 0
        print('Got connection from', addr)
        request = recvData(conn)
        request = request.decode('utf-8')
    
        print(request)
        sendData(conn, b'HTTP/1.0 200 OK\n')
        sendData(conn, b'Content-Type: text/html\n')
        sendData(conn, b'\n')
        path = './Data/' #may be changed to be an input from user
        lststr = ''
        for entry in scandir(path):
            if entry.is_file() == 1:
                lststr += entry.name + '|?!~' #separating condition for split
        lststr = lststr[:len(lststr)-len('|?!~')]
        lst = lststr.split('|?!~')
        lst.append("all")
        sendData(conn, b"""
        <html>
        <head>
        </head>
        <body>
        <h1>Hello World</h1>
        <form>
        <select id="mySelect">
        """)
        for i in lst:
            sendData(conn, b"""<option>""")
            j = str(i)
            sendData(conn, j.encode('utf-8'))
            sendData(conn, b"""</option>""")
        sendData(conn, b"""
        </select>
        </form>
        <p>There are <span id="demo">0</span> options in the list.</p>
        <script>
        document.getElementById("demo").innerHTML =
        document.getElementById("mySelect").length - 1;
        </script>
        <p>Choose the files that you want to transfer</p>
        </body>
        </html>
        """)
        print('Done Sending')
        Persistentrequest(conn)
