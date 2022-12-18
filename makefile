# generate make file 
all:  Attacker ping

monitor: Attacker.c
	gcc -o Attacker Attacker.c -lpthread -Wall
	
ping: Monitor.c
	gcc -o Monitor Monitor.c -Wall

clean:
	rm -f Monitor Attacker
	