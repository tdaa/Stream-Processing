#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <signal.h>

char* aux;
char* args;
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
  char all[1024];
  char* prev = "";
  int i=0;
  while(i<argc){
    if(i == index) {
      prev = strcat(c, " ");
      strcat(all, prev);
    }
    else{
    prev = strcat(argv[i], " ");
    strcat(all, prev);
    }
    i++;
  }
  args = strdup(all);
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
  int r;
  escrever1(buf, size, col);
  concat(argv+1, argc-1, aux, indice);
  r = execlp(argv[0], argv[0], args, buf);
  escrever2(buf, size, r);
}

int main(int argc, char** argv){

  if (argc < 3) {
      perror("missing arguments");
      exit(-1);
  }

  searchFor(argv+1, argc-1);

  int r;
  char buf[1024];

  while((r=readln(0,&buf,1024))>0){
    spawn(buf, r, argv+1, argc-1);
  }
  return 0;
}
