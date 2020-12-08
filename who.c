//my who program
#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

// #define SHOWHOST

void showtime(long timeval){
    //display time
    // char* c;
    // c = ctime(&timeval);
    // printf("%s", c);
    //%[符号][宽度][.精度]类型 
    //宽度：不够这么宽空格填充

    struct tm *cp;
    cp = localtime(&timeval);
    printf("%8d-%d-%02d", cp->tm_year+1900, cp->tm_mon+1, cp->tm_mday);
    printf(" %2d:%2d", cp->tm_hour, cp->tm_min);
}

void show_info(struct utmp* utbufp){
    if(utbufp->ut_type != USER_PROCESS)
        return; //过滤非用户
    printf("% -8.8s", utbufp->ut_name); //logname
    printf(" ");
    printf("% -8.8s", utbufp->ut_line); //the tty
    printf(" ");
    showtime(utbufp->ut_time); //display time
    printf(" (%s)",utbufp->ut_line); //just identical to original "who"
#ifdef SHOWHOST
    if(utbufp->ut_host[0] != '\0')
        printf("(%s)", utbufp->ut_host); //host
#endif
    printf("\n");
}


int main(){
    struct utmp current_record;
    int utmpfd;
    int reclen = sizeof(current_record);

    if((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1){
        perror(UTMP_FILE);
        exit(1);
    }

    while (read(utmpfd, &current_record, reclen) == reclen)
    {
        show_info(&current_record);
    }
    close(utmpfd);
    return 0;
    
}