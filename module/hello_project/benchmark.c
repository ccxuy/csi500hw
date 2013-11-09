#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <sys/time.h>
#include <fcntl.h>

void doSomething();
void reportTimeAndFaultCount(int j);
unsigned long getpf(int p);

int *ptr;
int i,a;
int arraysize = 323999999;
struct timeval c_time;
time_t c_sec;

//For file i/o
int nread;
int filedesc;
static unsigned long pf_buf[2];

static unsigned long old_maj=0, old_min=0;

unsigned long majpfaults, minpfaults;

int main(int argc, char *argv[])
{
    majpfaults = 99999999;
    minpfaults = 99999999;
    int j = 0, maxAttempts = 5;

    printf("========================\n");
    printf(" Benchmark Program\n");
    printf(" Author: Andrew Xu\n");
    printf("========================\n");
    printf(" Array size: %d\n", arraysize);
    printf(" Maximum attempt: %d\n", maxAttempts);
    printf("========================\n\n");

    /*
     * Allocate space for array
     *
     */
    time_t bt=0,et=0;
    printf("# %d run : malloc >\n", 0);
    gettimeofday(&c_time, NULL);
    printf("  Begin time > %lu\n", bt=c_time.tv_sec);
    getpf(0);
    printf("  Page fault count:  maj=%lu min=%lu\n", pf_buf[0], pf_buf[1]);
    
    old_maj=pf_buf[0];
    old_min=pf_buf[1];
    
    ptr = (int*)malloc(arraysize * sizeof(*ptr));
    for(i=0; i<arraysize; i++)
    {
	ptr[i] = i;
    }
    
    gettimeofday(&c_time, NULL);
    printf("  End time > %lu\n", et=c_time.tv_sec);
    getpf(0);
    printf("  Page fault count:  maj=%lu min=%lu\n", pf_buf[0], pf_buf[1]);
    
    printf("  Elapse : %lu s\n", et-bt);
    printf("  Page fault increase : maj=%lu, min=%lu\n", pf_buf[0]-old_maj, pf_buf[1]-old_min);

    for(j=0; j<maxAttempts; j++)
    {
        reportTimeAndFaultCount(j+1);
    }


    return 0;
}

void doSomething()
{
    for(i=0; i<arraysize; i++)
    {
        volatile a = ptr[i];
    }
}

void reportTimeAndFaultCount(int j){
    time_t bt=0,et=0;
    printf("# %d run >\n", j);
    gettimeofday(&c_time, NULL);
    printf("  Begin time > %lu\n", bt=c_time.tv_sec);
	
    getpf(0);
    printf("  Page fault count:  maj=%lu min=%lu\n", pf_buf[0], pf_buf[1]);
    
    old_maj=pf_buf[0];
    old_min=pf_buf[1];
        doSomething();
    gettimeofday(&c_time, NULL);
    printf("  End time > %lu\n", et=c_time.tv_sec);
    
    getpf(0);
    printf("  Page fault count:  maj=%lu min=%lu\n", pf_buf[0], pf_buf[1]);
    
    printf("  Elapse : %lu s\n", et-bt);
    printf("  Page fault increase : maj=%lu, min=%lu\n", pf_buf[0]-old_maj, pf_buf[1]-old_min);

}

unsigned long getpf(int p){
    unsigned long pf = 0;
    /*
     * Open device file.
     *
     */
	filedesc = open("df",O_RDONLY);
	if(filedesc <0){
		//perr();
		printf("FAILED to open device file.\n");
		return 1;
	}
    //printf(" > Device file ready.\n");

	/*
	 * Read from device file
	 */
	nread=read(filedesc, pf_buf, 8);
	if(nread == -1)
		printf("read error!");
    
    if(p=0){
        pf = pf_buf[0];
    }else{
        pf = pf_buf[1];
    }


    /*
     * Close device file.
     *
     */
	close(filedesc);
    return pf;
}
