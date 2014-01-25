#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <sys/time.h>
#include <fcntl.h>

int main(){
	int nread;
	unsigned long pf_buf[2];
	int filedesc = open("df",O_RDONLY);
	if(filedesc <0){
		//perr();
		return 1;
	}
	
	nread=read(filedesc, pf_buf, 8);

	if(nread == -1)
		printf("read error!");

	
	printf("maj=%lu, min=%lu \n", pf_buf[0], pf_buf[1]);
	close(filedesc);
}
