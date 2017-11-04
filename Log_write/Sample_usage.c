/* Program to how to use log_write */

#include<stdio.h>

int main()
{
	log_error("Program Execution started."); // This writes as error flag

	printf("Hello, World!\n");

	log_info("Program Endes Successfully."); // This writes as info flag

	return 0;
}
