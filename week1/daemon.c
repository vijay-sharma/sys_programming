#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

int main() {
    pid_t pid, sid;
    FILE *fp= NULL;
    pid = fork();
    if (pid < 0) {
        printf("fork failed!\n");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        printf("pid of child process %d \n", pid);
        exit(EXIT_SUCCESS);
    }
    umask(0);
            
    /* Open any logs here */        

    sid = setsid();
    if (sid < 0) {
        /* Log the failure */
        exit(EXIT_FAILURE);
    }
    

    if ((chdir("/")) < 0) {
        /* Log the failure */
        exit(EXIT_FAILURE);
    }
    
    // Close  the standard file descriptors 
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    
    fp = fopen ("Log.txt", "w+");
    int count = 0;
    while (1) {
        fprintf(fp, "Daemon logging.\n");
        fflush(fp);
        sleep(1); 
        count += 1;
        if (count  > 15){
            fprintf(fp, "Daemon exiting.\n");
            break; 
        }
    }
    fclose(fp);
    exit(EXIT_SUCCESS);
}
