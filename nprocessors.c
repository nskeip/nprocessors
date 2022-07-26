#ifdef __linux__
#include <sys/sysinfo.h>
#define nprocs() get_nprocs()
#elif _WIN32
#include <windows.h>
#define nprocs() GetActiveProcessorCount(ALL_PROCESSOR_GROUPS)
#elif __APPLE__

#include <sys/sysctl.h>

unsigned int nprocs(void) {
    int nm[2] = {CTL_HW, HW_AVAILCPU};
    size_t len = 4;
    uint32_t count;

    sysctl(nm, 2, &count, &len, NULL, 0);

    if (count < 1) {
        return 4;
    }
    return count;
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
