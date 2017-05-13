#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int operando;

void escrever(void* buf, int size){
    int r;
    int i=0;
    char c;
    c = ((char*)buf)[i];
    while ((r=(write(1,&c,1)))>0 && i<size){
        i++;
        c = ((char*)buf)[i];
    }
    c = '\n';
    write(1,&c,1);
}

void operar(void* buf, int size, char* operation, int novo){
    int add=0;
    int i=0;
    if((strcmp(operation, "<"))==0){
        if(novo < operando){
            escrever(buf, size);
        }
    }
    if((strcmp(operation, "<="))==0){
        if(novo <= operando){
            escrever(buf, size);
        }
    }
    if((strcmp(operation, ">"))==0){
        if(novo > operando){
            escrever(buf, size);
        }
    }
    if((strcmp(operation, ">="))==0){
        if(novo >= operando){
            escrever(buf, size);
        }
    }
    if((strcmp(operation, "!="))==0){
        if(novo != operando){
            escrever(buf, size);
        }
    }
    if((strcmp(operation, "="))==0){
        if(novo == operando){
            escrever(buf, size);
        }
    }
}

void  window (void* buf, char* copia, int size, char* operation, int coluna){
    int c=1;
    int i;
    int produto;
    char* num;
    char t;
    for(num = strtok(copia, ":"); num != NULL && c<coluna; num = strtok(NULL, ":")){
        c++;
    }
    if (num==NULL){
        perror("missing columns");
        exit(-1);
    }
    else {
        produto = atoi(num);

        operar(buf, size, operation, produto);
    }
}

ssize_t readln(int fildes, void *buf, int nbytes){
 	char c;
 	ssize_t i;
 	for (i = 0; read(fildes, &c, 1) == 1 && c != '\n' && c!= '\0' && i < nbytes;i++){
         ((char*)buf)[i] = c;
 	}
 	return i;
 }

int main (int argc , char*argv[]) {
    if (argc != 4) {
        perror("missing arguments or too much arguments");
        exit(-1);
    }
    int c = atoi(argv[1]);
    int n = atoi(argv[3]);
    operando = n;

    int i=0;

    char buf[1024];
    char copia[1024];

 
    while ((i=readln(0,&buf, 1024))>0){
        strcpy(copia, buf);
        window(&buf, copia, i, argv[2], c);
    }

   return 0;
}