void C4AulScriptEngine::ReLink(C4DefList *rDefs)
{
	// unlink scripts
	UnLink();

	// unlink defs
	if (rDefs) rDefs->ResetIncludeDependencies();

	// re-link
	Link(rDefs);

	// display state
	LogF("C4AulScriptEngine linked - %d line%s, %d warning%s, %d error%s",
		lineCnt, (lineCnt != 1 ? "s" : ""), warnCnt, (warnCnt != 1 ? "s" : ""), errCnt, (errCnt != 1 ? "s" : ""));
}