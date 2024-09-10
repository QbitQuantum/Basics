QString PlatformInfoScriptingInterface::getCPUBrand() {
#ifdef Q_OS_WIN
    int CPUInfo[4] = { -1 };
    unsigned   nExIds, i = 0;
    char CPUBrandString[0x40];
    // Get the information associated with each extended ID.
    __cpuid(CPUInfo, 0x80000000);
    nExIds = CPUInfo[0];

    for (i = 0x80000000; i <= nExIds; ++i) {
       __cpuid(CPUInfo, i);
        // Interpret CPU brand string
        if (i == 0x80000002) {
            memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
        } else if (i == 0x80000003) {
            memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
        } else if (i == 0x80000004) {
            memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
        }
    }

    return CPUBrandString;
#elif defined Q_OS_MAC
    FILE* stream = popen("sysctl -n machdep.cpu.brand_string", "r");
    
    std::ostringstream hostStream;
    while (!feof(stream) && !ferror(stream)) {
        char buf[128];
        int bytesRead = fread(buf, 1, 128, stream);
        hostStream.write(buf, bytesRead);
    }
    
    return QString::fromStdString(hostStream.str());
#else
    return QString("NO IMPLEMENTED");
#endif
}