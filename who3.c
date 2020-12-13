// who with buffer

#include <stdio.h>
#include <sys/types.h>
#include <utmp.h>
#include <fcntl.h>
#include <time.h>

#define SHOWHOST

void show_info(struct utmp*);
void showtime(time_t);

int main(){
    struct utmp* utbufp;
    struct utmp* utmp_next();

    if(utmp_open(UTMP_FILE) == -1){
        perror(UTMP_FILE);
        exit(1);
    }
    while((utbufp = utmp_next()) != ((struct utmp*) NULL))
        show_info(utbufp);
    utmp_close();
    return 0;
}

//show info()...