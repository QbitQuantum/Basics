/**	获得只读文件的句柄。注意只适合于只读文件！
 *	快速访问文件，用FileMapping方式对大文件的访问
 *	将会最为快捷。
 *	顺序访问数据
 */
FILEMAPHANDLE FileMapOpen(const TCHAR *file_name)
{
    FILEMAPHANDLE handle;

    handle = (FILEMAPHANDLE) malloc(sizeof(FILEMAPDATA));
    if (!handle)
        return 0;

    //打开文件
    handle->h_file = CreateFile(file_name, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    if (handle->h_file == INVALID_HANDLE_VALUE)
    {
        free(handle);
        return 0;
    }

    handle->length = 0;
    GetFileSizeEx(handle->h_file, (PLARGE_INTEGER)&handle->length);

    //创建映射
    handle->h_map = CreateFileMapping(handle->h_file, 0, PAGE_READONLY,	0, 0, 0);
    if (!handle->h_map)
    {
        CloseHandle(handle->h_file);
        free(handle);

        return 0;
    }

    SYSTEM_INFO sys_info;
    GetSystemInfo(&sys_info);

    handle->granularity = (int)sys_info.dwAllocationGranularity;
    handle->offset		= 0;
    handle->view		= 0;

    return handle;
}