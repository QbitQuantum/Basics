int
plfs_unlink(const char *path)
{
    debug_enter(__FUNCTION__,path);
    int ret;
    char stripped_path[PATH_MAX];
    stripPrefixPath(path, stripped_path);
    LogicalFileSystem *logicalfs = plfs_get_logical_fs(stripped_path);
    if (logicalfs == NULL) {
        ret = -EINVAL;
    } else {
        ret = logicalfs->unlink(stripped_path);
    }
    debug_exit(__FUNCTION__,path,ret);
    return ret;
}