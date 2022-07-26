#ifdef __linux__
#include <sys/sysinfo.h>
#define nprocs() get_nprocs()
#elif _WIN32
#include <sysinfoapi.h>
unsigned int nprocs(void) {
    SYSTEM_INFO info;
    GetSystemInfo(&info);
    if(info.dwNumberOfProcessors < 1) {
        return 4;
    }
    return info.dwNumberOfProcessors;
}
#else
#define nprocs() 4
#endif
#include <stdio.h>

int main(void) {
  unsigned int n = nprocs();
  printf("Number of processors available: %d\n", n);
  return 0;
}
