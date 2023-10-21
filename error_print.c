#include<stdio.h>
#include<errno.h>

#include<led_dec.h>

void error_print(char message[], int return_num)
{
    printf("error: %s, message: %s, file: %s, line: %s , function : %s", strerror(errno), message, __file__, __line__, __function__);
    fflush(stdout);
    exit(return_num);
}

void error_exit(int return_num)
{
    printf("file: %s, line: %s , function : %s", __file__, __line__, __function__);
    fflush(stdout);
    exit(return_num);
}