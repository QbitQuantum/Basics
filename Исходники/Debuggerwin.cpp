bool CDebuggerWin::CommandExecute(int argc, char **argv)
{
	if(argc<2)
	{
		LineOutput("Invalid number of arguments");
		return false;
	}
	else
	{
		spawnvp(_P_WAIT,argv[1],&argv[1]);
	}
	return true;
}