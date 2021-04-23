from socket import *
from sys import *
from os import scandir

class Server(object):
    def __init__(self):
        self.host = self.get_ip()
        self.port = 9641

    def get_ip(self):
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

    def socketinit(self, host, port):
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

    def sendData(self, conn, response):
        try:
            conn.sendall(response)
        except error as e:
            print('Error sending data:', e)
            exit(1)

    def recvData(self, conn):
        try:
            request = conn.recv(4096) # may change to a function to receive data
        except error as e:
            print('Error receiving data:', e)
            exit(1)
        return request

    def sendFile(self, conn, response):
        fb = open('./Data/' + response, 'rb')
        fb_read = fb.read(4096)
        while (fb_read):
            self.sendData(conn, fb_read)
            fb_read = fb.read(4096)
        fb.close()

    def nonPersistentrequest(self, conn):
        self.sendFile(conn, request)
        self.sendData(conn, b'END OF FILE CHECK')
        print('Done Sending Files')
        conn.close()
        print('Connection Closed')

    def Persistentrequest(self, conn):
        request = self.recvData(conn)
        while request:
            request = request.decode('utf-8')
            print('Sending', request)
            self.sendFile(conn, request)
            self.sendData(conn, b'END OF FILE CHECK')
            print('Done Sending Files')
            request = self.recvData(conn)
        conn.close()
        print('Connection Closed')



if __name__ == '__main__':

    server = Server()
    print(f'{server.host}')
    s = server.socketinit(server.host, server.port)
    s.listen(5)


    while True:
        # Initial time in milliseconds before accepting a connection
        print('Server listening....')


        conn, addr = s.accept()
        conn.settimeout(None) #time to connect to server (before file transfer)
        s.settimeout(10) # idle timeout = 10
        print('Got connection from', addr)
        request = server.recvData(conn)
        request = request.decode('utf-8')
        if request == 'Requesting Persistent connection...' or request == 'Requesting Non-persistent connection...':
            print(request)
            path = './Data/' #may be changed to be an input from user
            lststr = ''
            for entry in scandir(path):
                if entry.is_file() == 1:
                    lststr += entry.name + '|?!~' #separating condition for split
            lststr = lststr[:len(lststr)-len('|?!~')]
            lststr = lststr.encode('utf-8')
            server.sendData(conn, lststr)
            print('Done Sending')
            if request == 'Requesting Persistent connection...':
                server.Persistentrequest(conn)
            else:
                conn.close()
                print('Connection Closed')
        else:
            server.nonPersistentrequest(conn)