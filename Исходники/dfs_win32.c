static int dfs_win32_unlink(struct dfs_filesystem *fs, const char *path)
{
    int result;
    char *fp;
    fp = winpath_dirdup(WIN32_DIRDISK_ROOT, path);
    if (fp == RT_NULL)
    {
        rt_kprintf("out of memory.\n");
        return -DFS_STATUS_ENOMEM;
    }

    result = GetFileAttributes(fp);
    if (result == INVALID_FILE_ATTRIBUTES)
        goto __err;

    if (result & FILE_ATTRIBUTE_DIRECTORY)//winnt.h
    {
        if (RemoveDirectory(fp) == RT_FALSE)
            goto __err;
    }
    else //(result & FILE_ATTRIBUTE_NORMAL)
    {
        if (_unlink(fp) < 0)
            goto __err;
    }

    rt_free(fp);
    return 0;
__err:
    rt_free(fp);
    return win32_result_to_dfs(GetLastError());
}