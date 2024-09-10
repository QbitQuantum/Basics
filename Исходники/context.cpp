TError TContext::CreateDaemonCgs() {
    DaemonCgs[memorySubsystem] = memorySubsystem->GetRootCgroup()->GetChild(PORTO_DAEMON_CGROUP);
    DaemonCgs[cpuacctSubsystem] = cpuacctSubsystem->GetRootCgroup()->GetChild(PORTO_DAEMON_CGROUP);

    for (auto cg : DaemonCgs) {
        TError error = cg.second->Create();
        if (error)
            return error;

        // portod-slave
        error = cg.second->Attach(GetPid());
        if (error)
            return error;

        // portod master
        error = cg.second->Attach(GetPPid());
        if (error)
            return error;
    }

    if (!config().daemon().debug()) {
        TError error = memorySubsystem->SetLimit(DaemonCgs[memorySubsystem], config().daemon().memory_limit());
        if (error)
            return error;
    }

    return TError::Success();
}