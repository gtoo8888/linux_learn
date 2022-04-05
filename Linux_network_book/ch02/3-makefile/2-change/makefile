DIRS = sub add .
src = ${wildcard ${DIRS}/*.c}

CFLAGS = -I add -I sub -O2
TARGET = cacu

${TARGET}: main.o add_float.o add_int.o sub_int.o sub_float.o
	gcc -o cacu bin/*.o 

add_int.o : add/add_int.c add/add.h
	gcc -c -o bin/add_int.o add/add_int.c

add_float.o : add/add_float.c add/add.h
	gcc -c -o bin/add_float.o add/add_float.c

sub_int.o : sub/sub_int.c sub/sub.h
	gcc -c -o bin/sub_int.o sub/sub_int.c

sub_float.o : sub/sub_float.c sub/sub.h
	gcc -c -o bin/sub_float.o sub/sub_float.c

# main.o:main.c add/add.h sub/sub.h
# 	# mkdir bin
# 	gcc -c -o bin/main.o main.c -I add -I sub 

main.o:%o:%c
	echo ${src}
	${CC} -c $< -o bin/$@ ${CFLAGS}


# clean:
# 	rm -f cacu add/add_int.o add/add_float.o \
# 				sub/sub_int.o sub/sub_float.o main.o

clean:
	# rm -r bin
	${RM} cacu */*.o *.o 
	


# 先执行第一句话，寻找cacu目标，依赖main.o目标
# 找到main.o目标后，执行他的命令，不论main.o在哪里，都是第一个被执行
# make clean 
# make 后面接的就是目标
# make main.o就执行一句话
# 只有make的话默认就是执行第一个命令，























