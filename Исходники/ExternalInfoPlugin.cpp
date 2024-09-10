void ExternalInfoPlugin::start ()
{
	terminate ();

	if (isBlank (command)) OUTPUT_AND_RETURN (tr ("No command specified"));

	QString commandProper;
	QString parameters;
	SkProcess::splitCommand (commandProper, parameters, command);

	QString resolved=resolveFilename (commandProper, Settings::instance ().pluginPaths);
	if (isBlank (resolved)) OUTPUT_AND_RETURN (tr ("Command not found"));
	if (!QFile::exists (resolved)) OUTPUT_AND_RETURN (tr ("Command does not exist"));

	if (!process->startAndWait (resolved+notr (" ")+parameters)) OUTPUT_AND_RETURN (tr ("Error: %1").arg (process->getProcess ()->errorString ()));
	outputText (tr ("Process started"));

	// Note that on Windows, we may have to add the interpreter explicitly.
}