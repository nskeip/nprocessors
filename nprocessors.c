#ifdef __linux__
#include <sys/sysinfo.h>
#define nprocs() get_nprocs()
#else
#define nprocs() 4
#endif
#include <stdio.h>

int main(void) {
  int n = nprocs();
  printf("Number of processors available: %d\n", n);
  return 0;
}
