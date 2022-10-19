# OBJSDIR = objs
# TARGET = process
# OBJS = 01-mult-process.o  warp.o

# src = ${wildcard *.c}


# all : server 

# server: 01-mult-process.o wrap.o
# 	gcc 01-mult-process.o wrap.o -o server -Wall

# client: client.o wrap.o
# 	gcc client.o wrap.o -o client -Wall

# %.o:%.c
# 	gcc -c $< -Wall

# ${TARGET} : ${OBJSDIR} 01-mult-process.o
# 	gcc -o ${TARGET} ${OBJSDIR}/*.o

# ${OBJS} : %.c:%.o
# 	gcc -o ${OBJSDIR}/$@  -c $<

# ${OBJSDIR}:
# 	mkdir ./$@

TARGET1 = server

# ${TARGET}: 01-mult-process.c 
# 	gcc 01-mult-process.c  -o ${TARGET} -Wall

TARGET2 = server_with_warp

${TARGET2}: 01-mult-process_with_warp.c warp.c warp.h
	gcc 01-mult-process_with_warp.c warp.c warp.h -o ${TARGET2} -Wall

clean: 
	rm -f ${TARGET1} ${TARGET2}  pthread a.out *.o 


# 01-mult-process.c warp.c warp.h 