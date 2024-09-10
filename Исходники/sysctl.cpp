/**
@Status Caveat
@Notes Only HW_AVAILCPU is supported
*/
extern "C" int sysctl(const int* name, u_int namelen, void* oldp, size_t* oldlenp, const void* newp, size_t newlen) {
    if (namelen < 2 || name == nullptr) {
        errno = EINVAL;
        return -1;
    }

    if (namelen != 2 ||
        name[0] != CTL_HW ||
        name[1] != HW_AVAILCPU) {

        UNIMPLEMENTED_WITH_MSG("sysctl only supports querying HW_AVAILCPU");
        errno = EOPNOTSUPP;
        return -1;
    }

    if (*oldlenp < sizeof(int)) {
        *oldlenp = sizeof(int);
        errno = ENOMEM;
        return -1;
    }

    SYSTEM_INFO systemInfo;
    GetNativeSystemInfo(&systemInfo);

    *static_cast<int*>(oldp) = systemInfo.dwNumberOfProcessors;
    *oldlenp = sizeof(int);

    return 0;
}