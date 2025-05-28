#include "times.h"

int LocaltimeString(time_t* timer, char* time_string){
    struct tm *local = localtime(timer);
     //printf("Application Started at Local time: %d-%02d-%02d %02d:%02d:%02d\n",
     //       local_time->tm_year + 1900, // Year is since 1900
     //       local_time->tm_mon + 1,   // Month is 0-11
     //       local_time->tm_mday,
     //       local_time->tm_hour,
     //       local_time->tm_min,
     //       local_time->tm_sec);

    if (local == NULL) {
    printf("Error converting time\n");
    return 1;}
    strftime(time_string, sizeof(time_string), "%Y-%m-%d %H:%M:%S", local);
    return 0;
}