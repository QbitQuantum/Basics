abi_long do_openbsd_syscall(void *cpu_env, int num, abi_long arg1,
                            abi_long arg2, abi_long arg3, abi_long arg4,
                            abi_long arg5, abi_long arg6)
{
    abi_long ret;
    void *p;

#ifdef DEBUG
    gemu_log("openbsd syscall %d\n", num);
#endif
    if(do_strace)
        print_openbsd_syscall(num, arg1, arg2, arg3, arg4, arg5, arg6);

    switch(num) {
    case TARGET_OPENBSD_NR_exit:
#ifdef TARGET_GPROF
        _mcleanup();
#endif
        gdb_exit(cpu_env, arg1);
        /* XXX: should free thread stack and CPU env */
        _exit(arg1);
        ret = 0; /* avoid warning */
        break;
    case TARGET_OPENBSD_NR_read:
        if (!(p = lock_user(VERIFY_WRITE, arg2, arg3, 0)))
            goto efault;
        ret = get_errno(read(arg1, p, arg3));
        unlock_user(p, arg2, ret);
        break;
    case TARGET_OPENBSD_NR_write:
        if (!(p = lock_user(VERIFY_READ, arg2, arg3, 1)))
            goto efault;
        ret = get_errno(write(arg1, p, arg3));
        unlock_user(p, arg2, 0);
        break;
    case TARGET_OPENBSD_NR_open:
        if (!(p = lock_user_string(arg1)))
            goto efault;
        ret = get_errno(open(path(p),
                             target_to_host_bitmask(arg2, fcntl_flags_tbl),
                             arg3));
        unlock_user(p, arg1, 0);
        break;
    case TARGET_OPENBSD_NR_mmap:
        ret = get_errno(target_mmap(arg1, arg2, arg3,
                                    target_to_host_bitmask(arg4, mmap_flags_tbl),
                                    arg5,
                                    arg6));
        break;
    case TARGET_OPENBSD_NR_mprotect:
        ret = get_errno(target_mprotect(arg1, arg2, arg3));
        break;
    case TARGET_OPENBSD_NR_syscall:
    case TARGET_OPENBSD_NR___syscall:
        ret = do_openbsd_syscall(cpu_env,arg1 & 0xffff,arg2,arg3,arg4,arg5,arg6,0);
        break;
    default:
        ret = syscall(num, arg1, arg2, arg3, arg4, arg5, arg6);
        break;
    }
 fail:
#ifdef DEBUG
    gemu_log(" = %ld\n", ret);
#endif
    if (do_strace)
        print_openbsd_syscall_ret(num, ret);
    return ret;
 efault:
    ret = -TARGET_EFAULT;
    goto fail;
}