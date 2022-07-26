#ifdef __linux__
#include <sys/sysinfo.h>
#define nprocs() get_nprocs()
#elif _WIN32

    #if _WIN32_WINNT >= _WIN32_WINNT_WIN7
        #include <windows.h>
        #define nprocs() GetActiveProcessorCount(ALL_PROCESSOR_GROUPS)
    #elif
        #include <sysinfoapi.h>
        unsigned int nprocs(void) {
            SYSTEM_INFO info;

            GetSystemInfo(&info);
            if(info.dwNumberOfProcessors < 1) {
                return 4;
            }
            return info.dwNumberOfProcessors;
        }
    #endif

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
