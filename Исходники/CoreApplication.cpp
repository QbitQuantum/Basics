void CoreApplication::terminateCompilation ()
{
	debug("terminate compilation");
	QProcess* process = _compiler.getProcess();
	process->terminate();
}