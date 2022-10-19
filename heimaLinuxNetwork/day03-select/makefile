
ALLATRGET = ${TARGET1} ${TARGET2} ${TARGET3} ${TARGET4}

TARGET1 = 01-setsocket
# ${TARGET1}: 01-setsocket.c 
# 	gcc 01-setsocket.c  -o ${TARGET1} -Wall

TARGET2 = 02-select
# ${TARGET2}: 02-select.c 
# 	gcc 02-select.c  -o ${TARGET2} 

TARGET3 = 02-select
# ${TARGET3}: 02-select.c 
# 	gcc 02-select.c  -o ${TARGET3} 

TARGET4 = 04-epoll
${TARGET4}: 04-epoll
	gcc 04-epoll.c  -o ${TARGET4} 

clean: 
	rm -f ${ALLATRGET} a.out *.o 


# 01-mult-process.c warp.c warp.h 