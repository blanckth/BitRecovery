#include "times.h"

int format_time(time_t t, char* buf, size_t bufsize){
    struct tm *lt = localtime(&t);
     //printf("Application Started at Local time: %d-%02d-%02d %02d:%02d:%02d\n",
     //       local_time->tm_year + 1900, // Year is since 1900
     //       local_time->tm_mon + 1,   // Month is 0-11
     //       local_time->tm_mday,
     //       local_time->tm_hour,
     //       local_time->tm_min,
     //       local_time->tm_sec);
    if (lt == NULL) {
        strncpy(buf, "Invalid time", bufsize);
        printf("Error converting time\n");
        return 1;}
    strftime(buf, bufsize, "%Y-%m-%d %H:%M:%S", lt);
    return 0;
}