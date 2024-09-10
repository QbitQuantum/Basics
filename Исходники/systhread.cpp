void joinThreadGroup(SysThreadGroup *group)
{
	getCurrentThread()->joinGroup(group);
}