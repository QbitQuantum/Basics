int
run_attr_tests(char *testfile)
{
    int ret = -1;
    char *res = NULL;
    struct stat buf;
    struct statfs sbuf;
    struct statvfs svbuf;

    assert(testfile);

    fprintf(stdout, "Testing chmod");
    ret = chmod(testfile, 0);
    check_err(ret, "chmod", 2);

    fprintf(stdout, "Testing chown");
    ret = chown(testfile, 0, 0);
    check_err(ret, "chown", 2);

    fprintf(stdout, "Testing link");
    ret = link(testfile, testfile);
    check_err(ret, "link", 2);

    fprintf(stdout, "Testing rename");
    ret = rename(testfile, testfile);
    check_err(ret, "rename", 2);

    fprintf(stdout, "Testing utimes");
    ret = utimes(testfile, NULL);
    check_err(ret, "utimes", 2);

    fprintf(stdout, "Testing utime");
    ret = utime(testfile, NULL);
    check_err(ret, "utime", 2);

    fprintf(stdout, "Testing unlink");
    ret = unlink(testfile);
    check_err(ret, "unlink", 2);

    fprintf(stdout, "Testing symlink");
    ret = symlink(testfile, testfile);
    check_err(ret, "symlink", 2);

    fprintf(stdout, "Testing readlink");
    ret = readlink(testfile, testfile, 0);
    check_err(ret, "readlink", 2);

    fprintf(stdout, "Testing realpath");
    ret = 0;
    res = realpath((const char *)testfile, testfile);
    if (!res)
        ret = -1;
    check_err(ret, "realpath", 2);

    fprintf(stdout, "Testing stat");
    ret = stat(testfile, &buf);
    check_err(ret, "stat", 1);

    fprintf(stdout, "Testing lstat");
    ret = lstat(testfile, &buf);
    check_err(ret, "lstat", 1);

    fprintf(stdout, "Testing statfs");
    ret = statfs(testfile, &sbuf);
    check_err(ret, "statfs", 2);

    fprintf(stdout, "Testing statvfs");
    ret = statvfs(testfile, &svbuf);
    check_err(ret, "statvfs", 1);

    fprintf(stdout, "Testing getxattr");
    ret = getxattr(testfile, NULL, NULL, 0);
    check_err(ret, "getxattr", 2);

    fprintf(stdout, "Testing lgetxattr");
    ret = lgetxattr(testfile, NULL, NULL, 0);
    check_err(ret, "lgetxattr", 1);

    fprintf(stdout, "Testing lchown");
    ret = lchown(testfile, 0, 0);
    check_err(ret, "lchown", 2);
    return 0;
}