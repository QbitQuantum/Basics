static void test_GetMappedFileName(void)
{
    HMODULE hMod = GetModuleHandleA(NULL);
    char szMapPath[MAX_PATH], szModPath[MAX_PATH], *szMapBaseName;
    DWORD ret;
    char *base;
    char temp_path[MAX_PATH], file_name[MAX_PATH], map_name[MAX_PATH], device_name[MAX_PATH], drive[3];
    WCHAR map_nameW[MAX_PATH], nt_map_name[MAX_PATH];
    HANDLE hfile, hmap;

    SetLastError(0xdeadbeef);
    ret = pGetMappedFileNameA(NULL, hMod, szMapPath, sizeof(szMapPath));
    ok(!ret, "GetMappedFileName should fail\n");
todo_wine
    ok(GetLastError() == ERROR_INVALID_HANDLE, "expected error=ERROR_INVALID_HANDLE but got %d\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = pGetMappedFileNameA(hpSR, hMod, szMapPath, sizeof(szMapPath));
    ok(!ret, "GetMappedFileName should fail\n");
todo_wine
    ok(GetLastError() == ERROR_ACCESS_DENIED, "expected error=ERROR_ACCESS_DENIED but got %d\n", GetLastError());

    SetLastError( 0xdeadbeef );
    ret = pGetMappedFileNameA(hpQI, hMod, szMapPath, sizeof(szMapPath));
todo_wine
    ok( ret || broken(GetLastError() == ERROR_UNEXP_NET_ERR), /* win2k */
        "GetMappedFileNameA failed with error %u\n", GetLastError() );
    if (ret)
    {
        ok(ret == strlen(szMapPath), "szMapPath=\"%s\" ret=%d\n", szMapPath, ret);
        todo_wine
        ok(szMapPath[0] == '\\', "szMapPath=\"%s\"\n", szMapPath);
        szMapBaseName = strrchr(szMapPath, '\\'); /* That's close enough for us */
        todo_wine
        ok(szMapBaseName && *szMapBaseName, "szMapPath=\"%s\"\n", szMapPath);
        if (szMapBaseName)
        {
            GetModuleFileNameA(NULL, szModPath, sizeof(szModPath));
            ok(!strcmp(strrchr(szModPath, '\\'), szMapBaseName),
               "szModPath=\"%s\" szMapBaseName=\"%s\"\n", szModPath, szMapBaseName);
        }
    }

    GetTempPathA(MAX_PATH, temp_path);
    GetTempFileNameA(temp_path, "map", 0, file_name);

    drive[0] = file_name[0];
    drive[1] = ':';
    drive[2] = 0;
    SetLastError(0xdeadbeef);
    ret = QueryDosDeviceA(drive, device_name, sizeof(device_name));
    ok(ret, "QueryDosDeviceA error %d\n", GetLastError());
    trace("%s -> %s\n", drive, device_name);

    SetLastError(0xdeadbeef);
    hfile = CreateFileA(file_name, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
    ok(hfile != INVALID_HANDLE_VALUE, "CreateFileA(%s) error %d\n", file_name, GetLastError());
    SetFilePointer(hfile, 0x4000, NULL, FILE_BEGIN);
    SetEndOfFile(hfile);

    SetLastError(0xdeadbeef);
    hmap = CreateFileMappingA(hfile, NULL, PAGE_READONLY | SEC_COMMIT, 0, 0, NULL);
    ok(hmap != 0, "CreateFileMappingA error %d\n", GetLastError());

    SetLastError(0xdeadbeef);
    base = MapViewOfFile(hmap, FILE_MAP_READ, 0, 0, 0);
    ok(base != NULL, "MapViewOfFile error %d\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = pGetMappedFileNameA(GetCurrentProcess(), base, map_name, 0);
    ok(!ret, "GetMappedFileName should fail\n");
todo_wine
    ok(GetLastError() == ERROR_INVALID_PARAMETER || GetLastError() == ERROR_INSUFFICIENT_BUFFER,
       "wrong error %d\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = pGetMappedFileNameA(GetCurrentProcess(), base, 0, sizeof(map_name));
    ok(!ret, "GetMappedFileName should fail\n");
todo_wine
    ok(GetLastError() == ERROR_INVALID_PARAMETER, "expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = pGetMappedFileNameA(GetCurrentProcess(), base, map_name, 1);
todo_wine
    ok(ret == 1, "GetMappedFileName error %d\n", GetLastError());
    ok(!map_name[0] || broken(map_name[0] == device_name[0]) /* before win2k */, "expected 0, got %c\n", map_name[0]);

    SetLastError(0xdeadbeef);
    ret = pGetMappedFileNameA(GetCurrentProcess(), base, map_name, sizeof(map_name));
todo_wine {
    ok(ret, "GetMappedFileName error %d\n", GetLastError());
    ok(ret > strlen(device_name), "map_name should be longer than device_name\n");
    ok(memcmp(map_name, device_name, strlen(device_name)) == 0, "map name does not start with a device name: %s\n", map_name);
}

    SetLastError(0xdeadbeef);
    ret = pGetMappedFileNameW(GetCurrentProcess(), base, map_nameW, sizeof(map_nameW)/sizeof(map_nameW[0]));
todo_wine {
    ok(ret, "GetMappedFileNameW error %d\n", GetLastError());
    ok(ret > strlen(device_name), "map_name should be longer than device_name\n");
}
    if (nt_get_mapped_file_name(GetCurrentProcess(), base, nt_map_name, sizeof(nt_map_name)/sizeof(nt_map_name[0])))
    {
        ok(memcmp(map_nameW, nt_map_name, lstrlenW(map_nameW)) == 0, "map name does not start with a device name: %s\n", map_name);
        WideCharToMultiByte(CP_ACP, 0, map_nameW, -1, map_name, MAX_PATH, NULL, NULL);
        ok(memcmp(map_name, device_name, strlen(device_name)) == 0, "map name does not start with a device name: %s\n", map_name);
    }

    SetLastError(0xdeadbeef);
    ret = pGetMappedFileNameA(GetCurrentProcess(), base + 0x2000, map_name, sizeof(map_name));
todo_wine {
    ok(ret, "GetMappedFileName error %d\n", GetLastError());
    ok(ret > strlen(device_name), "map_name should be longer than device_name\n");
    ok(memcmp(map_name, device_name, strlen(device_name)) == 0, "map name does not start with a device name: %s\n", map_name);
}

    SetLastError(0xdeadbeef);
    ret = pGetMappedFileNameA(GetCurrentProcess(), base + 0x4000, map_name, sizeof(map_name));
    ok(!ret, "GetMappedFileName should fail\n");
todo_wine
    ok(GetLastError() == ERROR_UNEXP_NET_ERR, "expected ERROR_UNEXP_NET_ERR, got %d\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = pGetMappedFileNameA(GetCurrentProcess(), NULL, map_name, sizeof(map_name));
    ok(!ret, "GetMappedFileName should fail\n");
todo_wine
    ok(GetLastError() == ERROR_UNEXP_NET_ERR, "expected ERROR_UNEXP_NET_ERR, got %d\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = pGetMappedFileNameA(0, base, map_name, sizeof(map_name));
    ok(!ret, "GetMappedFileName should fail\n");
todo_wine
    ok(GetLastError() == ERROR_INVALID_HANDLE, "expected ERROR_INVALID_HANDLE, got %d\n", GetLastError());

    UnmapViewOfFile(base);
    CloseHandle(hmap);
    CloseHandle(hfile);
    DeleteFileA(file_name);

    SetLastError(0xdeadbeef);
    hmap = CreateFileMappingA(INVALID_HANDLE_VALUE, NULL, PAGE_READONLY | SEC_COMMIT, 0, 4096, NULL);
    ok(hmap != 0, "CreateFileMappingA error %d\n", GetLastError());

    SetLastError(0xdeadbeef);
    base = MapViewOfFile(hmap, FILE_MAP_READ, 0, 0, 0);
    ok(base != NULL, "MapViewOfFile error %d\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = pGetMappedFileNameA(GetCurrentProcess(), base, map_name, sizeof(map_name));
    ok(!ret, "GetMappedFileName should fail\n");
todo_wine
    ok(GetLastError() == ERROR_FILE_INVALID, "expected ERROR_FILE_INVALID, got %d\n", GetLastError());

    UnmapViewOfFile(base);
    CloseHandle(hmap);
}