import xmlrpc.client

s = xmlrpc.client.ServerProxy('http://ip_adresa:port')


# Print list of available methods
print(s.system.listMethods())
