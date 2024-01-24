#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
void black() {
	printf("\033[0;30m");
} 
void red () {
  	printf("\033[1;31m");
}
void green() {
	printf("\033[0;32m");
} 
void yellow() {
  	printf("\033[1;33m");
}
void blue() {
	printf("\033[0;34m");
} 
void purple() {
	printf("\033[0;35m");
} 
void cyan() {
	printf("\033[0;36m");
} 
void white() {
	printf("\033[0;37m");
} 
void reset () {
  	printf("\033[0m");
}
int DONE = 1;
void * color[3]={
	blue,
	purple,
	cyan
};
char * readline(int fd){
	size_t ct = 0;
	char *ptr = malloc(0x400);
	memset(ptr,0,0x400);
	while(ct < 0x400 && ptr[ct-1]!='\n')
	{
		size_t res = read(fd,ptr+ct,1);
		if(res!=1)
		{
			DONE = 0;
			break;
		}
		ct+=1;
	}
	return ptr;
}
void colorize_file(char *file_name){
	
	int fd = open(file_name,0);
	if(fd<0)
		puts("open err");
	else{
		char *s=0;
		while((s=readline(fd),DONE))
		{
			// printf("%p\n",s);
			int r = rand() % 3;
			void (*chosen)() = color[r];
			chosen();
			printf("%s",s);
			// reset();
		}
	}	
	close(fd);
}
int main () {
  	srand(time(NULL));
  	colorize_file("/Users/n132/conf/prompt");
	printf("\n");
  	return 0;
}