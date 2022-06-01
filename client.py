import socket
import threading
import os
import sys
import random
import string

socket_client = socket.socket()
host = socket.gethostname()
port = #nadopisati
socket_client.connect((host, port))

poruka = 'Igra_traje'
while poruka != 'Kraj':
    poruka = socket_client.recv(1024).decode('utf-8')
    print(poruka)
    rijec = 'Unos'
    flag = poruka.find(rijec)
    flag2 = poruka.find('Kraj')
    if flag2 != -1:
        break
    if flag != -1:
        odgovor = input()
        socket_client.send(odgovor.encode())
    flag = -1
    flag2 = -1

socket_client.close()
