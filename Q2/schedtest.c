#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(void)
{  int pid;
    int priorities[3] = {5, 10, 15};
    set_priority(getpid(), 1);
    printf("Parent started with priority 1\n");
    for(int i = 0; i < 3; i++) {
        pid = fork();
        if(pid < 0) {
            printf("Fork failed\n");
            exit(1);
        }
        if(pid == 0) {
            volatile int count;
            for(count = 0; count < 10000000; count++);
            printf("Child with priority %d finished\n",
            priorities[i]);
            exit(0);
        }
        set_priority(pid, priorities[i]);
    }
    for(int i = 0; i < 3; i++) {
        wait(0);
    }
    printf("Done\n");
    exit(0);
}