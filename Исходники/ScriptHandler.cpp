void ScriptHandler::LogInfo::add(pstring what)
{
    if (what[0] == '*') what.remove(0, 1);
    what.toupper();
    replace_ascii(what, '/', '\\');    
    if (logged.find(what) == logged.end()) {
	logged.insert(what);
	ordered.push_back(&(*logged.find(what)));
    }
}