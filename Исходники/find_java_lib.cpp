// Explore the registry to find a suitable version of Java.
// Returns an int which is the version of Java found (e.g. 1006 for 1.6) and the
// matching path in outJavaPath.
// Returns 0 if nothing suitable was found.
static int exploreJavaRegistry(const char *entry, REGSAM access, CPath *outJavaPath) {

    // Let's visit HKEY_LOCAL_MACHINE\SOFTWARE\JavaSoft\Java Runtime Environment [CurrentVersion]
    CPath rootKey("SOFTWARE\\JavaSoft\\");
    rootKey.addPath(entry);

    int versionInt = 0;
    CString currentVersion;
    CPath subKey(rootKey);
    if (getRegValue(subKey.cstr(), "CurrentVersion", access, &currentVersion)) {
        // CurrentVersion should be something like "1.7".
        // We want to read HKEY_LOCAL_MACHINE\SOFTWARE\JavaSoft\Java Runtime Environment\1.7 [JavaHome]
        subKey.addPath(currentVersion);
        CPath javaHome;
        if (getRegValue(subKey.cstr(), "JavaHome", access, &javaHome)) {
            versionInt = checkBinPath(&javaHome);
            if (versionInt >= 0) {
                if (gIsDebug) {
                    fprintf(stderr,
                            "Java %d found via registry: %s\n",
                            versionInt, javaHome.cstr());
                }
                *outJavaPath = javaHome;
            }
            if (versionInt >= MIN_JAVA_VERSION) {
                // Heuristic: if the current version is good enough, stop here
                return versionInt;
            }
        }
    }

    // Try again, but this time look at all the versions available
    HKEY javaHomeKey;
    LSTATUS status = RegOpenKeyExA(
        HKEY_LOCAL_MACHINE,         // hKey
        "SOFTWARE\\JavaSoft",       // lpSubKey
        0,                          // ulOptions
        KEY_READ | access,          // samDesired
        &javaHomeKey);              // phkResult
    if (status == ERROR_SUCCESS) {
        char name[256];
        DWORD index = 0;
        CPath javaHome;
        for (LONG result = ERROR_SUCCESS; result == ERROR_SUCCESS; index++) {
            DWORD nameLen = 255;
            name[nameLen] = 0;
            result = RegEnumKeyExA(
                            javaHomeKey,  // hKey
                            index,        // dwIndex
                            name,         // lpName
                            &nameLen,     // lpcName
                            NULL,         // lpReserved
                            NULL,         // lpClass
                            NULL,         // lpcClass,
                            NULL);        // lpftLastWriteTime
            if (result == ERROR_SUCCESS && nameLen < 256) {
                name[nameLen] = 0;
                CPath subKey(rootKey);
                subKey.addPath(name);

                if (getRegValue(subKey.cstr(), "JavaHome", access, &javaHome)) {
                    int v = checkBinPath(&javaHome);
                    if (v > versionInt) {
                        if (gIsDebug) {
                            fprintf(stderr,
                                    "Java %d found via registry: %s\n",
                                    versionInt, javaHome.cstr());
                        }
                        *outJavaPath = javaHome;
                        versionInt = v;
                    }
                }
            }
        }

        RegCloseKey(javaHomeKey);
    }

    return 0;
}