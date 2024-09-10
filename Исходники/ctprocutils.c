DWORD
CTGetPidOfCmdLine(
    PCSTR programName,
    PCSTR programFilename,
    PCSTR cmdLine,
    uid_t owner,
    pid_t *pid,
    size_t *count
    )
{
    DWORD ceError = ERROR_NOT_SUPPORTED;
    size_t fillCount = 0;
    size_t foundCount = 0;
    struct stat findStat;
#if HAVE_DECL_PSTAT_GETPROC
    //HPUX should have this
    struct pst_status mystatus;
    struct pst_status status[10];
    int inBuffer;
    int i;
#endif
#ifdef HAVE_STRUCT_PSINFO
    //Solaris and AIX should have this
    DIR *dir = NULL;
    struct dirent *dirEntry = NULL;
    PSTR filePath = NULL;
    struct psinfo infoStruct;
    FILE *infoFile = NULL;
    struct stat compareStat;
    BOOLEAN bFileExists;
#endif
#if defined(HAVE_KVM_GETPROCS) && HAVE_DECL_KERN_PROC_PATHNAME
    //FreeBSD has this
    char pathBuffer[MAXPATHLEN];
    size_t len;
    int unfilteredCount;
    kvm_t *kd = NULL;
    struct kinfo_proc *procs;
    int i;
    struct kinfo_proc *pos;
    int sysctlName[4] = {
        CTL_KERN,
        KERN_PROC,
        KERN_PROC_PATHNAME,
        0 };
#endif

    if(count)
    {
        fillCount = *count;
        *count = 0;
    }
    else if(pid != NULL)
        fillCount = 1;

    if(programFilename != NULL)
    {
        while(stat(programFilename, &findStat) < 0)
        {
            if(errno == EINTR)
                continue;
            GCE(ceError = LwMapErrnoToLwError(errno));
        }
    }
    
#if HAVE_DECL_PSTAT_GETPROC
    //First get the process info for this process
    inBuffer = pstat_getproc(&mystatus, sizeof(mystatus), 0,
            getpid());
    if(inBuffer != 1)
        GCE(ceError = LwMapErrnoToLwError(errno));

    //Now look at all processes
    inBuffer = pstat_getproc(status, sizeof(status[0]),
            sizeof(status)/sizeof(status[0]), 0);
    if(inBuffer < 0)
        GCE(ceError = LwMapErrnoToLwError(errno));
    while(inBuffer > 0)
    {
        for(i = 0; i < inBuffer; i++)
        {
            if(memcmp(&mystatus.pst_rdir, &status[i].pst_rdir,
                        sizeof(mystatus.pst_rdir)))
            {
                /* This process has a different root directory (it is being run
                   via a chroot). Let's not count this process as a match. */
                continue;
            }
            if (owner != (uid_t)-1 && owner != status[i].pst_euid)
            {
                continue;
            }
            if (programName != NULL && strcmp(status[i].pst_ucomm, programName))
            {
                continue;
            }
            if (cmdLine != NULL && strcmp(status[i].pst_cmd, cmdLine))
            {
                continue;
            }
            if(programFilename != NULL && (
                    status[i].pst_text.psf_fileid != findStat.st_ino ||
                    status[i].pst_text.psf_fsid.psfs_id != findStat.st_dev ||
                    status[i].pst_text.psf_fsid.psfs_type != findStat.st_fstype
                    ))
            {
                continue;
            }
 
            //This is a match
            if(foundCount < fillCount)
                pid[foundCount] = status[i].pst_pid;
            foundCount++;
        }
        //Continue looking at the process list where we left off
        inBuffer = pstat_getproc(status, sizeof(status[0]),
                sizeof(status)/sizeof(status[0]),
                status[inBuffer - 1].pst_idx + 1);
        if(inBuffer < 0)
            GCE(ceError = LwMapErrnoToLwError(errno));
    }
    ceError = ERROR_SUCCESS;
#endif

#ifdef HAVE_STRUCT_PSINFO
    if ((dir = opendir("/proc")) == NULL) {
        GCE(ceError = LwMapErrnoToLwError(errno));
    }

    while(1)
    {
        errno = 0;
        dirEntry = readdir(dir);
        if(dirEntry == NULL)
        {
            if(errno != 0)
                GCE(ceError = LwMapErrnoToLwError(errno));
            else
            {
                //No error here. We simply read the last entry
                break;
            }
        }
        if(dirEntry->d_name[0] == '.')
            continue;
        // On AIX, there is a /proc/sys which does not contain a psinfo
        if(!isdigit((int)dirEntry->d_name[0]))
            continue;
        CT_SAFE_FREE_STRING(filePath);
        GCE(ceError = CTAllocateStringPrintf(&filePath, "/proc/%s/psinfo",
                    dirEntry->d_name));
        GCE(ceError = CTCheckFileOrLinkExists(filePath, &bFileExists));
        if(!bFileExists)
        {
            // On AIX 6.1, a defunct process can lack a psinfo file.
            continue;
        }
        GCE(ceError = CTSafeCloseFile(&infoFile));
        GCE(ceError = CTOpenFile(filePath, "r", &infoFile));
        if(fread(&infoStruct, sizeof(infoStruct), 1, infoFile) != 1)
        {
            GCE(ceError = LwMapErrnoToLwError(errno));
        }

        if (owner != (uid_t)-1 && owner != infoStruct.pr_euid)
        {
            continue;
        }
        if (programName != NULL && strcmp(infoStruct.pr_fname, programName))
        {
            continue;
        }
        if (cmdLine != NULL && strcmp(infoStruct.pr_psargs, cmdLine))
        {
            continue;
        }
        if(programFilename != NULL)
        {
            CT_SAFE_FREE_STRING(filePath);
            GCE(ceError = CTAllocateStringPrintf(&filePath,
                        "/proc/%s/object/a.out",
                        dirEntry->d_name));

            while(stat(filePath, &compareStat) < 0)
            {
                if(errno == EINTR)
                    continue;
                if(errno == ENOENT || errno == ENOTDIR)
                {
                    //This process wasn't executed from a file?
                    goto not_match;
                }
                GCE(ceError = LwMapErrnoToLwError(errno));
            }
            if(findStat.st_ino != compareStat.st_ino)
                continue;
            if(findStat.st_dev != compareStat.st_dev)
                continue;
            if(findStat.st_rdev != compareStat.st_rdev)
                continue;
        }
 
        //This is a match
        if(foundCount < fillCount)
            pid[foundCount] = infoStruct.pr_pid;
        foundCount++;
not_match:
        ;
    }
#endif

#if defined(HAVE_KVM_GETPROCS) && HAVE_DECL_KERN_PROC_PATHNAME
    kd = kvm_open(NULL, "/dev/null", NULL, O_RDONLY, NULL);
    if (kd == NULL)
        GCE(ceError = DWORD_ACCESS_DENIED);

    procs = kvm_getprocs(kd, KERN_PROC_PROC, 0, &unfilteredCount);
    if (procs == NULL)
        GCE(ceError = DWORD_ACCESS_DENIED);

    pos = procs;
    for(i = 0; i < unfilteredCount; i++,
        pos = (struct kinfo_proc *)((char *)pos + pos->ki_structsize))
    {
        if (owner != (uid_t)-1 && owner != pos->ki_uid)
        {
            continue;
        }
        if (programName != NULL && strcmp(pos->ki_comm, programName))
        {
            continue;
        }
        if (cmdLine != NULL)
        {
            char **args = kvm_getargv(kd, pos, 0);
            char **argPos = args;
            PCSTR cmdLinePos = cmdLine;

            while (*cmdLinePos != '\0')
            {
                if (argPos == NULL || *argPos == NULL)
                    break;

                if (strncmp(cmdLinePos, *argPos, strlen(*argPos)))
                    break;

                cmdLinePos += strlen(*argPos);
                argPos++;

                if(cmdLinePos[0] == ' ')
                    cmdLinePos++;
            }

            if(*cmdLinePos != '\0' || (argPos != NULL && *argPos != NULL))
            {
                //not a match
                continue;
            }
        }
        if (programFilename != NULL)
        {
            pathBuffer[0] = '\0';
            if (pos->ki_textvp != NULL)
            {
                sysctlName[3] = pos->ki_pid;
                len = sizeof(pathBuffer);
                if( sysctl(sysctlName, 4, pathBuffer, &len, NULL, 0) < 0)
                {
		    /* If the executable path does not exist
		       (e.g. because the file was deleted after
		       the program started), move on */
		    if (errno == ENOENT)
			continue;
                    GCE(ceError = LwMapErrnoToLwError(errno));
                }
            }
            if(strcmp(programFilename, pathBuffer))
                continue;
        }

        //This is a match
        if(foundCount < fillCount)
            pid[foundCount] = pos->ki_pid;
        foundCount++;
    }
    ceError = ERROR_SUCCESS;
#endif

    if(count)
        *count = foundCount;
    else if(!ceError && foundCount == 0)
        ceError = ERROR_PROC_NOT_FOUND;

cleanup:
#ifdef HAVE_STRUCT_PSINFO
    if(dir != NULL)
        closedir(dir);
    CT_SAFE_FREE_STRING(filePath);
    CTSafeCloseFile(&infoFile);
#endif
#if defined(HAVE_KVM_GETPROCS) && HAVE_DECL_KERN_PROC_PATHNAME
    if(kd != NULL)
    {
        kvm_close(kd);
    }
#endif

    return ceError;
}