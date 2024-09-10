int tBigDir() {
    int retC, retD, fi, retS;
    char fname[50];
    struct VFS_File_Stat s;

    retC = Create_Directory("/d/bigdir");
    if (retC == EEXIST) {
        Delete("/d/bigdir", false);
        retC = Create_Directory("/d/bigdir");
    }
    if (retC != 0) {
        Print("couldn't create /d/bigdir: %d\n", retC);
        return -1;
    }

    for (fi = 0; fi < 100; fi++) {
        int fd;

        snprintf(fname, 50, "/d/bigdir/%04dabcdefghijklmnopqrstuvwxyz%04d",
                 fi, fi);
        Print((fi % 25 == 0) ? ":" : ".");
        fd = Open(fname, O_WRITE | O_CREATE);
        if (fd < 0) {
            Print("bad open/creat at %d\n", fi);
            return -1;
        }
        if (Close(fd) < 0) {
            Print("failed to close");
            return -1;
        }
        retS = Stat(fname, &s);
        if (retS < 0) {
            Print("bad stat at %d\n", fi);
            return -1;
        }
    }

    snprintf(fname, 50, "/d/bigdir/%04dabcdefghijklmnopqrstuvwxyz%04d", fi,
             fi);
    retS = Stat(fname, &s);
    if (retS == 0) {
        Print("bad extra stat at %d\n", fi);
        return -1;
    }

    for (fi = 0; fi < 100; fi++) {
        snprintf(fname, 50, "/d/bigdir/%04dabcdefghijklmnopqrstuvwxyz%04d",
                 fi, fi);
        Print((fi % 25 == 0) ? ":" : ".");
        (void)Delete(fname, false);
        retS = Stat(fname, &s);
        if (retS == 0) {
            return -1;
        }
    }

    retD = Delete("/d/bigdir", false);
    if (retD != 0) {
        Print("failed to remove /d/bigdir: %d", retD);
        return retD;
    }

    return 0;
}