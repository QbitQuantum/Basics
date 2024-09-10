pid_t spawnvex(const char *path, char *const argv[], char *const envv[], Spawnvex_t *vex) {
    int i;
    int op;
    unsigned int flags = 0;
    pid_t pid;
    int arg;
    int err;
    int fd;
    posix_spawnattr_t ax;
    posix_spawn_file_actions_t fx;
    Spawnvex_t *xev = NULL;
#if _lib_spawn_mode || _lib_spawn && _mem_pgroup_inheritance
    pid_t pgid;
    int arg;
    int j;
    int k;
    int m;
    int ic;
    int jc;
    Spawnvex_t *xev;
#if !_lib_spawn_mode
    int *map;
    int a;
    struct inheritance inherit;
#endif
#endif

    if (vex && vex->debug >= 0) {
        error(ERROR_OUTPUT, vex->debug, "spawnvex exe %4d %8d %p %4d \"%s\"", __LINE__, getpid(),
              vex, vex->cur, path);
    }
#if _lib_spawn_mode || _lib_spawn && _mem_pgroup_inheritance
    if (!envv) envv = environ;
    pid = -1;
    m = 0;
    if (vex) {
        vex->noexec = -1;
        vex->pgrp = -1;
        flags = vex->flags;
        if (!(xev = spawnvex_open(0))) goto bad;
        j = -1;
        for (i = 0; i < vex->cur;) {
            op = vex->op[i++].number;
            arg = vex->op[i++].number;
            if (op & 1) i += 2;
            op /= 2;
            if (op >= 0) {
                if (m < op) m = op + 1;
                if (m < arg) m = arg + 1;
            } else if (op == SPAWN_cwd)
                j = arg;
        }
        if (j >= 0) {
            if ((i = open(".", O_RDONLY)) < 0) goto bad;
            if ((i = save(i, &ic, m)) < 0) goto bad;
            if (spawnvex_add(xev, SPAWN_cwd, i, 0, 0) < 0 || restore(xev, i, -1, 0) < 0) {
                close(i);
                goto bad;
            }
            if (fchdir(j) < 0) goto bad;
            if ((i = save(j, &jc, m)) < 0) goto bad;
            if (restore(xev, i, j, jc) < 0) {
                close(i);
                goto bad;
            }
        }
    } else {
        flags = 0;
        xev = NULL;
    }
#if _lib_spawn_mode
    if (vex)
        for (i = 0; i < vex->cur;) {
            op = vex->op[i++].number;
            arg = vex->op[i++].number;
            if (op & 1) i += 2;
            switch (op /= 2) {
                case SPAWN_frame:
                    vex->frame = (unsigned int)arg;
                    break;
                case SPAWN_pgrp:
                    vex->pgrp = (pid_t)arg;
                    break;
                default:
                    if (op >= 0) {
                        if (arg < 0) {
                            if ((i = save(op, &ic, m)) < 0) {
                                if (i < -1) goto bad;
                            } else if (restore(xev, i, op, ic) < 0) {
                                close(i);
                                goto bad;
                            } else
                                close(op);
                        } else if (arg == op) {
                            if (spawnvex_add(xev, SPAWN_cloexec, arg, 0, 0) < 0) goto bad;
                            if (fcntl(arg, F_SETFD, 0) < 0) goto bad;
                        } else if ((j = save(arg, &jc, m)) < -1)
                            goto bad;
                        else {
                            close(arg);
                            if (fcntl(op, F_DUPFD, arg) >= 0) {
                                if ((i = save(op, &ic, m)) >= 0) {
                                    if (restore(xev, i, op, ic) >= 0) {
                                        close(op);
                                        if (j < 0 || restore(xev, j, arg, jc) >= 0) continue;
                                    }
                                    close(i);
                                }
                            }
                            if (j >= 0) {
                                fcntl(j, F_DUPFD, arg);
                                close(j);
                            }
                            goto bad;
                        }
                    }
                    break;
            }
        }
    pid = spawnve(vex && vex->pgrp >= 0 ? P_DETACH : P_NOWAIT, path, argv, envv);
#else
    inherit.flags = 0;
    map = 0;
    if (vex) {
        if (m) {
            map = calloc(1, m * sizeof(int));
            if (!map) goto bad;
            for (i = 0; i < m; i++) map[i] = i;
        }
        for (i = 0; i < vex->cur;) {
            op = vex->op[i++].number;
            a = i;
            arg = vex->op[i++].number;
            if (op & 1) i += 2;
            switch (op /= 2) {
                case SPAWN_noop:
                    break;
                case SPAWN_noexec:
                    break;
                case SPAWN_frame:
                    vex->frame = (unsigned int)arg;
                    break;
                case SPAWN_pgrp:
                    inherit.flags |= SPAWN_SETGROUP;
                    inherit.pgroup = arg ? arg : SPAWN_NEWPGROUP;
                    break;
                case SPAWN_sigdef:
                    inherit.flags |= SPAWN_SETSIGDEF;
                    sigemptyset(&inherit.sigdefault);
                    for (j = 1; j < 8 * sizeof(vex->op[a].number); j++)
                        if (vex->op[a].number & (1 << j)) sigaddset(&inherit.sigdefault, j);
                    break;
                case SPAWN_sigmask:
                    inherit.flags |= SPAWN_SETSIGMASK;
                    sigemptyset(&inherit.sigmask);
                    for (j = 1; j < 8 * sizeof(vex->op[a].number); j++)
                        if (vex->op[a].number & (1 << j)) sigaddset(&inherit.sigmask, j);
                    break;
                default:
                    if (op < 0) {
                        errno = EINVAL;
                        goto bad;
                    } else if (arg < 0)
                        map[op] = SPAWN_FDCLOSED;
                    else
                        map[op] = arg;
                    break;
            }
        }
    }
    pid = spawn(path, m, map, &inherit, (const char **)argv, (const char **)envv);
#endif
    if (pid >= 0 && vex) VEXINIT(vex);
bad:
    if (xev) {
        spawnvex_apply(xev, 0, SPAWN_FLUSH | SPAWN_NOCALL);
        spawnvex_close(xev);
    }
#if !_lib_spawn_mode
    if (map) free(map);
#endif
    return pid;

#else

#if _lib_spawnve
    if (!vex || !vex->cur && !vex->flags) return spawnve(path, argv, envv);
#endif
    if (vex && ((vex->set & (0
#if !_lib_posix_spawnattr_setfchdir
                             | VEXFLAG(SPAWN_cwd)
#endif
#if !_lib_posix_spawnattr_setsid
                             | VEXFLAG(SPAWN_sid)
#endif
#if !_lib_posix_spawnattr_setumask
                             | VEXFLAG(SPAWN_umask)
#endif
                                 ))
#if !_lib_posix_spawn
                || !(vex->flags & SPAWN_EXEC)
#endif
                    )) {
        int n;
        int m;
        Spawnvex_noexec_t nx;
        int msg[2];

        if (!envv) envv = environ;
        n = errno;
        if (pipe(msg) < 0) {
            msg[0] = msg[1] = -1;
        } else {
            (void)fcntl(msg[0], F_SETFD, FD_CLOEXEC);
            (void)fcntl(msg[1], F_SETFD, FD_CLOEXEC);
        }
        if (!(flags & SPAWN_FOREGROUND)) sigcritical(SIG_REG_EXEC | SIG_REG_PROC);
        pid = fork();
        if (pid == -1) {
            n = errno;
        } else if (!pid) {
            if (!(flags & SPAWN_FOREGROUND)) sigcritical(SIG_REG_POP);
            if (vex && (n = spawnvex_apply(vex, 0, SPAWN_FRAME | SPAWN_NOCALL))) {
                errno = n;
            } else {
                if (vex && vex->debug >= 0) {
                    error(ERROR_OUTPUT, vex->debug, "spawnvex exe %4d %8d %p %4d \"%s\"", __LINE__,
                          getpid(), vex, vex->cur, path);
                }
                execve(path, argv, envv);
                if (vex && vex->debug >= 0) {
                    error(ERROR_OUTPUT, vex->debug, "spawnvex exe %4d %8d %p %4d \"%s\" FAILED",
                          __LINE__, getpid(), vex, vex->cur, path);
                }
                if (vex && (i = vex->noexec) >= 0) {
                    nx.vex = vex;
                    nx.handle = vex->op[i + 3].handle;
                    nx.path = path;
                    nx.argv = argv;
                    nx.envv = envv;
#if _use_spawn_exec
                    /*
                     * setting SPAWN_EXEC here means that it is more efficient to
                     * exec(interpreter) on script than to fork() initialize and
                     * read script -- highly subjective, based on some ksh
                     * implementaions, and probably won't be set unless its a
                     * noticable win
                     */

                    nx.flags |= SPAWN_EXEC;
#endif
                    nx.msgfd = msg[1];
                    errno = (*vex->op[i + 2].callback)(&nx, SPAWN_noexec, errno);
                }
            }
            if (msg[1] != -1) {
                m = errno;
                write(msg[1], &m, sizeof(m));
            }
            _exit(errno == ENOENT ? EXIT_NOTFOUND : EXIT_NOEXEC);
        }
        if (msg[0] != -1) {
            close(msg[1]);
            if (pid != -1) {
                m = 0;
                while (read(msg[0], &m, sizeof(m)) == -1) {
                    if (errno != EINTR) {
                        m = errno;
                        break;
                    }
                }
                if (m) {
                    while (waitpid(pid, &n, 0) && errno == EINTR) {
                        ;
                    }
                    pid = -1;
                    n = m;
                }
            }
            close(msg[0]);
        }
        if (!(flags & SPAWN_FOREGROUND)) sigcritical(SIG_REG_POP);
        if (pid != -1 && vex) VEXINIT(vex);
        errno = n;
        return pid;
    }
    if (vex) {
        err = posix_spawnattr_init(&ax);
        if (err) goto nope;
        err = posix_spawn_file_actions_init(&fx);
        if (err) {
            posix_spawnattr_destroy(&ax);
            goto nope;
        }
        for (i = 0; i < vex->cur;) {
            op = vex->op[i++].number;
            arg = vex->op[i++].number;
            if (op & 1) i += 2;
            switch (op /= 2) {
                case SPAWN_noop:
                    break;
                case SPAWN_noexec:
                    break;
                case SPAWN_frame:
                    break;
#if _lib_posix_spawnattr_setfchdir
                case SPAWN_cwd:
                    err = posix_spawnattr_setfchdir(&ax, arg);
                    if (err) goto bad;
                    break;
#endif
                case SPAWN_pgrp:
                    err = posix_spawnattr_setpgroup(&ax, arg);
                    if (err) goto bad;
                    err = posix_spawnattr_setflags(&ax, POSIX_SPAWN_SETPGROUP);
                    if (err) goto bad;
                    break;
                case SPAWN_resetids:
                    err = posix_spawnattr_setflags(&ax, POSIX_SPAWN_RESETIDS);
                    if (err) goto bad;
                    break;
#if _lib_posix_spawnattr_setsid
                case SPAWN_sid:
                    err = posix_spawnattr_setsid(&ax, arg);
                    if (err) goto bad;
                    break;
#endif
                case SPAWN_sigdef:
                    break;
                case SPAWN_sigmask:
                    break;
#if _lib_posix_spawnattr_setumask
                case SPAWN_umask:
                    if (err = posix_spawnattr_setumask(&ax, arg)) goto bad;
                    break;
#endif
                default:
                    if (op < 0) {
                        err = EINVAL;
                        goto bad;
                    } else if (arg < 0) {
                        err = posix_spawn_file_actions_addclose(&fx, op);
                        if (err) goto bad;
                    } else if (arg == op) {
#ifdef F_DUPFD_CLOEXEC
                        if ((fd = fcntl(op, F_DUPFD_CLOEXEC, 0)) < 0)
#else
                        if ((fd = fcntl(op, F_DUPFD, 0)) < 0 ||
                            fcntl(fd, F_SETFD, FD_CLOEXEC) < 0 && (close(fd), 1))
#endif
                        {
                            err = errno;
                            goto bad;
                        }
                        if (!xev && !(xev = spawnvex_open(0))) goto bad;
                        spawnvex_add(xev, fd, -1, 0, 0);
                        err = posix_spawn_file_actions_adddup2(&fx, fd, op);
                        if (err) goto bad;
                    } else {
                        err = posix_spawn_file_actions_adddup2(&fx, op, arg);
                        if (err) goto bad;
                    }
                    break;
            }
        }

        // Ensure stdin, stdout, stderr are open in the child process.
        // See https://github.com/att/ast/issues/1117.
        for (int fd = 0; fd < 3; ++fd) {
            errno = 0;
            if (fcntl(fd, F_GETFD, NULL) == -1 || errno == EBADF) {
                err = posix_spawn_file_actions_addopen(&fx, fd, "/dev/null", O_RDWR, 0);
                if (err) goto bad;
            }
        }

        err = posix_spawn(&pid, path, &fx, &ax, argv, envv ? envv : environ);
        if (err) goto bad;
        posix_spawnattr_destroy(&ax);
        posix_spawn_file_actions_destroy(&fx);
        if (xev) {
            spawnvex_apply(xev, 0, SPAWN_NOCALL);
            spawnvex_close(xev);
        }
        if (vex->flags & SPAWN_CLEANUP) spawnvex_apply(vex, 0, SPAWN_FRAME | SPAWN_CLEANUP);
        VEXINIT(vex);
    } else {
        err = posix_spawn(&pid, path, NULL, NULL, argv, envv ? envv : environ);
        if (err) goto nope;
    }
    if (vex && vex->debug >= 0) {
        error(ERROR_OUTPUT, vex->debug, "spawnvex exe %4d %8d %p %4d \"%s\" %8d posix_spawn",
              __LINE__, getpid(), vex, vex->cur, path, pid);
    }
    return pid;
bad:
    posix_spawnattr_destroy(&ax);
    posix_spawn_file_actions_destroy(&fx);
    if (xev) {
        spawnvex_apply(xev, 0, SPAWN_NOCALL);
        spawnvex_close(xev);
    }
nope:
    errno = err;
    if (vex && vex->debug >= 0) {
        error(ERROR_OUTPUT, vex->debug, "spawnvex exe %4d %8d %p %4d \"%s\" %8d posix_spawn FAILED",
              __LINE__, getpid(), vex, vex->cur, path, -1);
    }
    return -1;
#endif
}