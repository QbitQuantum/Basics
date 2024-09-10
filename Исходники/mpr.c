static void test_WNetGetUniversalName(void)
{
    DWORD ret;
    char buffer[1024];
    DWORD drive_type, info_size, fail_size;
    char driveA[] = "A:\\";
    char driveandpathA[] = "A:\\file.txt";
    WCHAR driveW[] = {'A',':','\\',0};

    for(; *driveA <= 'Z'; ++*driveA,  ++*driveandpathA, ++*driveW){
        drive_type = GetDriveTypeW(driveW);

        info_size = sizeof(buffer);
        ret = WNetGetUniversalNameA(driveA, UNIVERSAL_NAME_INFO_LEVEL,
                buffer, &info_size);

        if(drive_type == DRIVE_REMOTE)
            ok(ret == WN_NO_ERROR, "WNetGetUniversalNameA failed: %08x\n", ret);
        else
            /* WN_NO_NET_OR_BAD_PATH (DRIVE_FIXED) returned from the virtual drive (usual Q:)
               created by the microsoft application virtualization client */
            ok((ret == WN_NOT_CONNECTED) || (ret == WN_NO_NET_OR_BAD_PATH),
                "WNetGetUniversalNameA(%s, ...) returned %u (drive_type: %u)\n",
                driveA, ret, drive_type);

        ok(info_size == sizeof(buffer), "Got wrong size: %u\n", info_size);

        fail_size = 0;
        ret = WNetGetUniversalNameA(driveA, UNIVERSAL_NAME_INFO_LEVEL,
                buffer, &fail_size);
        if(drive_type == DRIVE_REMOTE)
            todo_wine ok(ret == WN_BAD_VALUE || ret == WN_MORE_DATA, "WNetGetUniversalNameA failed: %08x\n", ret);
        else
            ok(ret == WN_NOT_CONNECTED || ret == WN_NO_NET_OR_BAD_PATH,
                "(%s) WNetGetUniversalNameW gave wrong error: %u\n", driveA, ret);

        fail_size = ARRAY_SIZE(driveA) - 1;
        ret = WNetGetUniversalNameA(driveA, UNIVERSAL_NAME_INFO_LEVEL,
                buffer, &fail_size);
        if(drive_type == DRIVE_REMOTE)
            ok(ret == WN_MORE_DATA, "WNetGetUniversalNameA failed: %08x\n", ret);

        ret = WNetGetUniversalNameA(driveandpathA, UNIVERSAL_NAME_INFO_LEVEL,
                buffer, &info_size);
        if(drive_type == DRIVE_REMOTE)
            todo_wine ok(ret == WN_NO_ERROR, "WNetGetUniversalNameA failed: %08x\n", ret);

        info_size = sizeof(buffer);
        ret = WNetGetUniversalNameW(driveW, UNIVERSAL_NAME_INFO_LEVEL,
                buffer, &info_size);

        if(drive_type == DRIVE_REMOTE)
            ok(ret == WN_NO_ERROR, "WNetGetUniversalNameW failed: %08x\n", ret);
        else
            ok((ret == WN_NOT_CONNECTED) || (ret == WN_NO_NET_OR_BAD_PATH),
                "WNetGetUniversalNameW(%s, ...) returned %u (drive_type: %u)\n",
                wine_dbgstr_w(driveW), ret, drive_type);
        if(drive_type != DRIVE_REMOTE)
            ok(info_size == sizeof(buffer), "Got wrong size: %u\n", info_size);
    }
}