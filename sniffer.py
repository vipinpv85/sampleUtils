#Packet sniffer in python
#For Linux
 
import socket
 
#create an INET, raw socket
#s = socket.socket(socket.AF_INET, socket.SOCK_RAW, socket.IPPROTO_UDP)
#s = socket.socket(socket.AF_UNIX, socket.SOCK_RAW)

s = socket.socket(socket.AF_PACKET, socket.SOCK_RAW)
s.bind("eth0", socket.ETH_P_ALL)

#s = socket.socket(socket.AF_INET, socket.SOCK_RAW, socket.IPPROTO_IPIP)
#s = socket.socket(socket.AF_PACKET, socket.SOCK_RAW, socket.IPPROTO_UDP)
#s = socket.socket(socket.AF_PACKET, socket.SOCK_RAW)
 
# receive a packet
while True:
  #print s.recvfrom(65565)
  print s.recv(4096)
