#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(void)
{ char *p;
  int pid;
  p = sbrk(4096);
  if(p == (char*)-1){
    printf("sbrk failed\n");
    exit(1);
  }
  *p = 'A';
  printf("Initial value: %c\n", *p);
  printf("mprotect: %d\n", mprotect(p, 1));
  printf("Read after mprotect: %c\n", *p);
  pid = fork();
 if(pid < 0){
    printf("fork failed\n");
    exit(1);
  }
if(pid == 0){
    printf("Child trying to write\n");
    *p = 'B';
    printf("Child write unexpectedly succeeded\n");
    exit(0);
  }
  wait(0);
  printf("Parent sees after child: %c\n", *p);
  printf("munprotect: %d\n", munprotect(p, 1));
  *p = 'C';
  printf("After writing C: %c\n", *p);
  printf("Unaligned address: %d\n", mprotect(p + 1, 1));
  printf("Zero length: %d\n", mprotect(p, 0));
  printf("Beyond memory: %d\n", mprotect(p + 4096, 1));
  printf("Protection test completed\n");
  exit(0);
}
