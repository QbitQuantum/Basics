int main(int argc, char** argv)
{
    const char* progname = basename(strdup(argv[0]));
    if (argc <= 1)
        return usage(progname);

    // special case -- if the first arg is "--init.d", then we just build symlinks
    if (strcmp(argv[1], "--init.d") == 0)
    {
        std::list<char*> ns_args;
        for (int i = 1; i < argc; ++i)
            ns_args.push_back(argv[i]);
        int ret = create_symlinks_and_metadata(progname, ns_args);
        return ret;
    }

    // Search **backwards** from the end of the commandline for --
    //     from end to 1st -- is the environment args (env_args)
    //     up to 2nd -- is the with namespace args (ns_args)
    //     rest is the command args (exec_args)
    // This also means you need to push to **front**, not **back**.
    std::list<char*> env_args, ns_args, exec_args;
    int i = argc - 1; // start at 1 since 0 is progname
    while (i > 0 && strcmp(argv[i], "--") != 0)
        env_args.push_front(argv[i--]);
    i--; // skip --
    while (i > 0 && strcmp(argv[i], "--") != 0)
        ns_args.push_front(argv[i--]);
    if (ns_args.size() == 0) // must at least have mount name
        return usage(progname);
    i--; // skip --
    while (i > 0)
        exec_args.push_front(argv[i--]);
    exec_args.push_back(NULL); // execvp requires final argument be NULL

    // detach from our parent's namespace
    CHECK(unshare(CLONE_NEWNS) == 0, "%s: unshare failed: %m\n", progname);

    // umount the old /with (this mount is now private for us)
    // the MNT_DETACH is needed if some joker set getcwd() to /with.
    int ret = umount2(WITH_MOUNTPOINT, MNT_DETACH);
    CHECK(ret >= 0, "%s: umount2 tmpfs " WITH_MOUNTPOINT " failed: %m\n", progname);

    // after the -- is mount_name target1=src1 target2=src2 -- env
    char* mount_name = ns_args.front();
    assert(mount_name);
    ret = mount(mount_name, "/with", "tmpfs", 0, NULL);
    CHECK(ret >= 0, "%s: mount tmpfs " WITH_MOUNTPOINT " failed: %m\n", progname);

    // build out the symlinks from the namespace
    ret = create_symlinks_and_metadata(progname, ns_args);
    if (ret != 0)  // CHECKs are performed in the function
        return ret;

    // write env metadata
    FILE* fd = fopen(WITH_MOUNTPOINT "/.env", "w");
    CHECK(fd >= 0, "%s: unable to write env metadata: %m\n%s\n", progname, WITH_MOUNTPOINT "/.env");
    for (std::list<char*>::const_iterator it = env_args.begin(), end = env_args.end(); it != end; ++it)
        fprintf(fd, "%s\n", *it);
    fclose(fd);

    // drop setuid
    int uid = getuid(), gid = getgid();
    CHECK(setresuid(uid, uid, uid) >= 0 && setresgid(gid, gid, gid) >= 0,
        "%s: setresuid/setresgid failed: %m\n", progname);

    // now that we've dropped privileges, install the environment
    // that was passed on the commandline.
    clearenv();
    for (std::list<char*>::const_iterator it = env_args.begin(), end = env_args.end(); it != end; ++it)
    {
        char* env_var = *it;
        assert(env_var);
        putenv(env_var);
    }

    // we need to copy exec_args to a vector so it's laid out like an array
    std::vector<char*> exec_args_as_array(exec_args.begin(), exec_args.end());
    CHECK(execvp(exec_args_as_array[0], &exec_args_as_array[0]) != -1, "%s: cannot exec %s: %m\n", progname, exec_args_as_array[0]);
    return 1;
}