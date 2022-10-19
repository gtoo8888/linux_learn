#ifndef __WARP_H_
#define __WARP_H_

// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <string.h>
// #include <errno.h>

void perr_exit(const char *s);
struct sockaddr
int Accept(int fd,struct sockaddr *sa,socklen_t *salenptr);
int Bind(int fd,const struct sockaddr * sa,socklen_t salen);
int Connect(int fd,const struct sockaddr *sa,socklen_t salen);
int Listen(int fd,int backlong);
int Socket(int family,int type,int protocol);
ssize_t Read(int fd,void *ptr,size_t nbytes);
ssize_t Write(int fd,const void *ptr,size_t nbytes);
int Close(int fd);
ssize_t Readn(int fd,void *vptr,size_t n);
ssize_t Writen(int fd,void *vptr,size_t n);
static ssize_t my_read(int fd,char *ptr);
ssize_t Readline(int fd,void *vptr,size_t maxlen);
int tcp4bind(short port,const char *IP);


#endif /* __WARP_H_ */
