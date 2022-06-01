import socket
import random
import sys

server_socket = socket.socket()
host = socket.gethostname()
port = #nadopisati
server_socket.bind((host, port))
server_socket.listen(5) # maksimalni broj klijenata u redu cekanja


print ('Server ceka na konekciju...')

while 1:
	(conn, address) = server_socket.accept()

	poruka1 = 'Dobrodosli u igricu pogadjanja rijeci!'
	conn.send(poruka1.encode()) #ovom naredbom Å¡aljemo poruku klijentu
	poruka2 = 'Imate ukupno 5 pokusaja da pokusate pogoditi rijec!'
	conn.send(poruka2.encode())

	brojac = 0
	trenutna_rijec = 'voce'
	trenutna_velicina_rijeci = 0
	with open('plodovi.txt', 'r') as dictionary:
		tekst = dictionary.read()
		tekst = tekst.split()
		trenutna_rijec = random.choice(tekst)
		trenutna_velicina_rijeci = len(trenutna_rijec)
	rijec_vidljiva_korisniku = trenutna_rijec
	rijec_vidljiva_korisniku_lista = list(rijec_vidljiva_korisniku)
	print(rijec_vidljiva_korisniku)
	for i in range (0, trenutna_velicina_rijeci, 1):
		rijec_vidljiva_korisniku_lista[i] = '_ '
	rijec_vidljiva_korisniku = ''.join(rijec_vidljiva_korisniku_lista)
	poruka3 = 'Trazena rijec: ' + rijec_vidljiva_korisniku
	conn.send(poruka3.encode())
    
	pogodeno = 0
  #Ovdje nadodajte kod 
  #:hint: sa naredbom conn.recv dobijete odgovor od klijenta, njega morate ili spremiti (ako je slovo) ili usporediti sa traÅ¾enom rijeci (ako je unesena odmah rijec, inace se podrazumijeva da je slovo uneseno)

			

server_socket.close()
sys.exit()
