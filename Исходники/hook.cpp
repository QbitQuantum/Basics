int hook::getSyscallNumber(trace::Tracee::Ptr tracee)
{
    // This function is a copy from strace (syscall.c), adopted to our needs.
    if(tracee->isSyscallBegin())
    {
        tracee->setSyscallBegin(false);
        return -1;
    }

    long syscallnum = -1;
    struct pt_regs regs;
    long ret = ptrace(PTRACE_GETREGS, tracee->getPid(), NULL, (void *)&regs);
    if(ret == -1)
    {
        util::logError("Failed to get registers, err %d: %s", errno,
                strerror(errno));
        throw std::system_error(errno, std::system_category());
    }

    // we are only interested in syscall entries
    if(regs.ARM_ip == 0)
    {
        tracee->setSyscallBegin(true);

        if (regs.ARM_cpsr & 0x20)
        {
            // Get the Thumb-mode system call number
            syscallnum = regs.ARM_r7;
        }
        else
        {
            //Get the ARM-mode system call number
            errno = 0;
            syscallnum = ptrace(PTRACE_PEEKTEXT, tracee->getPid(),
                    (void *)(regs.ARM_pc - 4), NULL);
            if(errno)
            {
                util::logError("Failed to get registers, err %d: %s", errno,
                        strerror(errno));
                throw std::system_error(errno, std::system_category());
            }

            if(syscallnum == 0xef000000)
            {
                syscallnum = regs.ARM_r7;
            }
            else
            {
                if ((syscallnum & 0x0ff00000) != 0x0f900000) {
                    util::logError("unknown syscall trap 0x%08lx\n",
                            syscallnum);
                    throw std::system_error(syscallnum,
                            std::generic_category());
                }

                // Fixup the syscall number
                syscallnum &= 0x000fffff;
            }
        }

        if(syscallnum & 0x0f0000)
        {
            // Handle ARM specific syscall
            syscallnum &= 0x0000ffff;
        }

        return syscallnum;
    }

    // signal syscall exit, we should never end here
    util::logError("Reached end of getSyscallNumber(), shouldn't happen");
    return -1;
}