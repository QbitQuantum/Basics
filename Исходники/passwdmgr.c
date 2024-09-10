bool load_passwords(void)
{
    SceUID fd;
    char linebuf[LINEBUF], path[PATH_MAX];
    rc4_key *pkey;

    STRCPY_S(path, scene_appdir());
    STRCAT_S(path, "password.lst");

    if (is_encrypted(path)) {
        rc4_prepare_key((u8 *) CRYPT_KEY, sizeof(CRYPT_KEY) - 1, &g_key);
        pkey = &g_key;
    } else {
        pkey = NULL;
    }

    fd = sceIoOpen(path, PSP_O_RDONLY, 0);

    if (fd < 0) {
        return false;
    }

    if (pkey != NULL) {
        sceIoLseek(fd, 4, PSP_SEEK_SET);
    }

    linebuf[sizeof(linebuf) - 1] = '\0';

    while (read_lines(fd, linebuf, sizeof(linebuf) - 1, pkey) >= 0) {
        add_password(linebuf);
    }

    sceIoClose(fd);

    return true;
}