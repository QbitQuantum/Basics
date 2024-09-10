Time getProcessCPUTime(void)
{
    Time user, elapsed;
    getProcessTimes(&user,&elapsed);
    return user;
}