MachSyscall makeFromEvent(const EventSyscall * ev)
{
    Process::const_ptr proc = ev->getProcess();
    Architecture arch = proc->getArchitecture();
    OSType os = proc->getOS();
    Platform plat(arch,os);
    MachSyscall::SyscallIDPlatform syscallNumber = ev->getSyscallNumber();
#if !defined(os_windows)
    MachSyscall::SyscallName syscallName = MachSyscall::nameLookup(plat, syscallNumber);
#else
    MachSyscall::SyscallName syscallName = "Unknown";
#endif
    return MachSyscall(plat, syscallNumber, syscallName);
}