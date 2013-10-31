#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <sys/time.h>
#include <fcntl.h>

int main(){
	int nread;
	char buffer[80];
	int filedesc = open("df",O_RDONLY);
	if(filedesc <0)
		return 1;
	
	nread=read(filedesc, buffer, 80);

	if(nread == -1)
		printf("read error!");

	unsigned long maj, min=0;
	int i;
	for(i=0; i<4; i++){
		maj |= ( (unsigned long)buffer[i] << (i*8) );
	}
	for(i=4; i<8; i++){
		min |= ( (unsigned long)buffer[i] << (i*8) );
	}
	
	printf("maj=%lu, min=%lu \n", maj, min);
	close(filedesc);
}
