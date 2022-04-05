# client: client.o wrap.o
# 	gcc client.o wrap.o -o client -Wall -lpthread

# pthread: 01-mult-process.c warp.c warp.h
# 	gcc -o pthread 01-mult-process.c warp.c


process : 01-mult-process.o
	gcc 01-mult-process.o -o process

01-mult-process.o : 01-mult-process.c 
	gcc -c 01-mult-process.c 





clean: 
	-rm -rf process pthread a.out 01-mult-process.o warp.h.gch
