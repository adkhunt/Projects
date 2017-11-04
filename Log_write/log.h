/*
 * User defined header file which helps to write
 * in the log file which is located in /var/log/gcc.log
 * in that header file info and error are allowed to write
 * and there is also time stamp which can help the time to
 * find your log easily
 */

/* #	 USAGE : Copy this file to the /usr/include folder
   # 		 And add #include <log.h> this line to the
   #		 /usr/include/stdio.h.

	# Note : Do all above in root (sudo) user
 */

#ifndef LOG
#define LOG

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<time.h>

/*
 * This function will helps to open the file and return 
 * the file descriptor to the /var/log/gcc.log file
 */

char* open_file()
{
int i, j, file_des = 0;
char *log_location = "/var/log/gcc.log";

	file_des = open(log_location, O_CREAT | O_RDWR | O_APPEND, 0644);

	return file_des;
}

/*
 * This function write the info part in the gcc.log file
 */

void log_info (char *log_message)
{
char buff[20];
struct tm *time_stamp;
static int file_des = -1;
int time_len, info_len;

	// This condition will check if file is not opened.

	if(file_des < 0)
		file_des = open_file();

	time_t now = time (0);
	time_stamp = gmtime (&now);

	strftime (buff, sizeof(buff), "%d-%m-%Y %H:%M:%S", time_stamp);

	for(time_len = 0 ; buff[time_len] ; ++time_len);
	for(info_len = 0 ; log_message[info_len] ; ++info_len);

	write(file_des, buff, time_len);	// This writes time stamp to file
	write(file_des, " : [INFO] : ",12);	// Writes if this is info of error
	write(file_des, log_message, info_len);	// Write the message which passed to fun
	write(file_des, "\n", 1);
}

/*
 * This function write the error part in the gcc.log file
 */

void log_error (char *log_message)
{
char buff[20];
struct tm *sTm;
static int file_des = -1;
int time_len, info_len;

	// Checks for file is opened or not

	if(file_des < 0)
		file_des = open_file();

	time_t now = time (0);	// This takes the system time
	sTm = gmtime (&now);

	strftime (buff, sizeof(buff), "%d-%m-%Y %H:%M:%S", sTm);

	for(time_len = 0 ; buff[time_len] ; ++time_len);	// Find the length of time_len
	for(info_len = 0 ; log_message[info_len] ; ++info_len);	// Find the length of info

	write(file_des, buff, time_len);
	write(file_des, " : [ERROR] : ",13);
	write(file_des, log_message, info_len);
	write(file_des, "\n", 1);
}

#endif
