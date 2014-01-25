#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <sys/time.h>

void doSomething();
void reportTimeAndFaultCount();

int *ptr;
int i,a;
int arraysize = 99999999;
struct timeval c_time;
time_t c_sec;

unsigned long majpfaults, minpfaults;

int main(int argc, char *argv[])
{
    majpfaults = 99999999;
    minpfaults = 99999999;
    int retval = syscall(351, &majpfaults, &minpfaults);
    if( retval < 0)
    {
        perror("Mysystem calll returned with an error code.");
    }
    printf("My syscall's parameters: %p %p\n", &majpfaults, &minpfaults);
    printf("My system call returned %d.\n", retval);
    printf("Current values:  majpfaults=%lu minpfaults=%lu\n", majpfaults, minpfaults);

    printf("%d   %d",sizeof(*ptr),sizeof(int));
    ptr = (int*)malloc(arraysize * sizeof(*ptr));
    int j, maxAttempts = 10;
    printf("Try to do %d times.", maxAttempts);
    reportTimeAndFaultCount();
    for(j=0; j<maxAttempts; j++)
    {
        printf("=======START dosomething=========");
        doSomething();
        reportTimeAndFaultCount();
    }
    return 0;
}

void doSomething()
{
    for(i=0; i<arraysize; i++)
    {
        a = ptr[i];
    }
}

void reportTimeAndFaultCount(){
    int retval = syscall(351, &majpfaults, &minpfaults);
    if( retval < 0)
    {
        perror("Mysystem calll returned with an error code.");
    }
    printf("Current values:  majpfaults=%lu minpfaults=%lu\n", majpfaults, minpfaults);
    gettimeofday(&c_time, NULL);
    printf("current time > %lu\n", c_time.tv_sec);
}
