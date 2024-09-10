int
plat_dir_create(wchar_t *path)
{
    // return((int)CreateDirectory(path, NULL));
    return((int)SHCreateDirectory(hwndMain, path));
}