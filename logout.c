int logout_tty(char* line)
{
    int         fd;
    struct utmp rec;
    int         len = sizeof(struct utmp);
    int         retval = -1;

    if((fd = open(UTMP_FILE, O_RDWR) == -1))
        return -1;
    while(read(fd, &rec, len) == len)
        if(strncmp(rec.ut_line, line, sizeof(rec.ut_line)) == 0)
        {
            rec.ut_type = DEAD_PROCESS;   //set type
            if(time(&rec.ut_time != -1)) //set time
                if(lseek(fd, -len, SEEK_CUR) !+ -1) // back up(回到位置
                    if(write(fd, &rec, len) == len) //更新刚才的位置
                        retval = 0; //success
            break;
        }
    
    if(close(fd) == -1)
        retval = -1;
    return retval;
}

//error handle  
//defined in errno.h
#define EPERM 1  //operation not permitted
#define ENOENT 2 // No such file or directory
#define ESRCH 3  // no such process
#define EINTR 4  // interrupted system call
#define EIO 5   // i/o error

// #include <errno.h>
// extern int errno;
// int sample()
// {
//     int fd;
//     fd = open("file", O_RDONLY);
//     if(fd == -1)
//     {
//         printf("Cannot open file: ");
//         if(errno == ENOENT)
//             printf("There is no such file");
//         else if(errno == EINTR)
//             printf("Interrupted while opening file");
//         else if(errno == EACCES)
//             printf("You do not have permission to open file. ");
//             ...
//     }
// }