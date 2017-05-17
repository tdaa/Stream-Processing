#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <signal.h>
<<<<<<< HEAD
#include <limits.h>
#include <sys/wait.h>
#include "readln.h"
#include "concat.h"
#include "processInput.h"

void escrever(char* buf, char* execResult, int sizeBuf){
  char* final;
  buf[sizeBuf-1] = ':';
  final = concat(buf, execResult);
  memset(execResult, 0, strlen(execResult));
  write(1, final, sizeBuf+strlen(execResult)+1);
  printf("\n");
}

void spawn(char* buf, char* copy, char** argv, int sizeBuf){
  int status;
  char execResult[4];
  char* final;
  pid_t p;
  p = fork();
  if(!p){
    execvp(argv[1], &argv[1]);
    _exit(-1);
  }
  else{
    wait(&status);
    sprintf(execResult, "%d", WEXITSTATUS(status));
    escrever(buf, execResult, sizeBuf);
  }
}

void searchFor(char** args, int argc, char** input){
  int i=1, coluna;
  char *c;
  while(i<argc){
    c = args[i];
    if(*c == '$') {
      c++;
      coluna = *c - '0';
      args[i] = input[coluna-1];
    }
    i++;
  }
}

int main(int argc, char** argv){
=======

char* aux;
char args[4096] = {""};
int col;
int indice;

ssize_t readln(int fildes, void *buf, int nbytes){
 	char c;
 	ssize_t i;
 	for (i = 0; read(fildes, &c, 1) == 1 && c != '\n' && c!= '\0' && i < nbytes;i++){
         ((char*)buf)[i] = c;
 	}
 	return i;
 }

 void searchFor(char** argv, int argc){
   int i=0, flag=0, coluna;
   char *c;
   char* s = argv[i];
   while(i<argc && !flag){
     c = argv[i];
     if(*c == '$') {
       flag=1;
       c++;
       coluna = *c - '0';
     }
     else{
       i++;
       c = argv[i];
     }
   }
   indice = i;
   col = coluna;
 }

void concat(char** argv, int argc, char* c, int index){
  char* prev;
  int i=0;
  while(i < argc){
    if(i == index) {
      prev = strcat(c, " ");
      strcat(args, prev);
      prev = NULL;
    }
    else{
    prev = strcat(argv[i], " ");
    strcat(args, prev);
    prev = NULL;
    }
    i++;
  }
  free(prev);
}

void escrever1(void *buf, int size, int coluna){
  int i=0, flag=0, nPontos=0, j=0;
  int w;
  char c;
  char s[10];
  c = ((char*)buf)[i];
  while(i<size && !flag){
    c = ((char*)buf)[i];

    if(nPontos == coluna-1) {
      flag=1;
      while(c!=':'){
        s[j] = c;
        i++;
        j++;
        c = ((char*)buf)[i];
      }
      s[j]='\0';
    }
    else{
      if(c==':') nPontos++;
    }

    i++;
  }

aux = strdup(s);
}


void escrever2(void *buf, int size, int r){
  int i=0;
  int w;
  char c;
  c = ((char*)buf)[i];
  while ((w=(write(1,&c,1)))>0 && i<size){
      i++;
      c = ((char*)buf)[i];
  }
  char copy[10];
  sprintf(copy, "%d", r);
  int len = strlen(copy);

  c = ':';
  write(1,&c,1);

  i=0;
  c = copy[i];
  while ((w=(write(1,&c,1)))>0 && i<len && copy!=NULL){
      i++;
      c = copy[i];
  }
  c = '\n';
  write(1,&c,1);
}

void spawn(char* buf, int size, char** argv, int argc){
  int r, i;
  escrever1(buf, size, col);
  concat(argv+1, argc-1, aux, indice-1);
  for(i=0; args[i]!='\0'; i++);
  i--;
  args[i] = '\0';
  char *s = strcat(strcat(argv[0], " ") , args);
  r = execvp(argv[0], &s);
  escrever2(buf, size, r);
}

int main(int argc, char** argv){

>>>>>>> fad8f617ac2f10052f082dc3d64ab82030baa0df
  if (argc < 3) {
      perror("missing arguments");
      exit(-1);
  }
<<<<<<< HEAD
  int r;
  char buf[PIPE_BUF], copy[PIPE_BUF], *input[PIPE_BUF];
  while((r=readln(0, buf,1024))>0){
    strncpy(copy, buf, r);
    processInput(input, copy, ":");
    searchFor(argv, argc, input);
    spawn(buf, copy, argv, r);
    memset(buf, 0, r);
    memset(copy, 0, r);
=======

  searchFor(argv+1, argc-1);
  int r;
  char buf[1024];

  while((r=readln(0, buf,1024))>0){
    spawn(buf, r, argv+1, argc-1);
>>>>>>> fad8f617ac2f10052f082dc3d64ab82030baa0df
  }
  return 0;
}
