void syscallRequestExit(int returnValue)
{
	getCurrentProcess()->returnValue = returnValue;
	schedulerKillCurrentProcess();
}