#include <stdio.h>

#ifdef __linux__
#include <sys/sysinfo.h>
#elif _WIN32
    #if _WIN32_WINNT >= _WIN32_WINNT_WIN7
    #include <windows.h>
    #else
    #include <sysinfoapi.h>
    #endif
#elif __APPLE__
#include <sys/sysctl.h>
#endif

unsigned int nprocs(void) {
    #ifdef __linux__
        return get_nprocs();
    #elif _WIN32
        #if _WIN32_WINNT >= _WIN32_WINNT_WIN7
            return GetActiveProcessorCount(ALL_PROCESSOR_GROUPS);
        #else
            SYSTEM_INFO info;
            GetSystemInfo(&info);
            if(info.dwNumberOfProcessors < 1) {
                return 4;
            }
            return info.dwNumberOfProcessors;
        #endif
    #elif __APPLE__
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
        return 4;
    #endif
}

int main(void) {
    unsigned int n = nprocs();
    printf("Number of processors available: %d\n", n);
    return 0;
}
