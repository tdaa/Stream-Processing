#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <signal.h>

ssize_t readln(int fildes, void *buf, size_t nbyte){
	char c;
	ssize_t i;
	for (i = 0; read(fildes, &c, 1) == 1 && i<nbyte && c != '\n';){
        ((char*)buf)[i] = c;
        i++;
	}
	return i;
}


int main(int argc, char **argv){
    if(argc != 2 ){
        printf("please give 1 arg\n");
        _exit(-1);
    }
    else{
        char c;
        int i=0, iarg = 0, r;
        char buf[4096];
        i = readln(0, buf,4096);
        buf[i] = ':';
        strcat(buf, argv[1]);
        i=0;
        while(r = write(1, &buf[i], 1)>0 && buf[i]){
            i++;
        }
        return 0;
    }
}
