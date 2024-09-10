NamedList& NamedList::clearParam(const String& name, char childSep)
{
    XDebug(DebugInfo,"NamedList::clearParam(\"%s\",'%.1s')",
	name.c_str(),&childSep);
    String tmp;
    if (childSep)
	tmp << name << childSep;
    ObjList *p = &m_params;
    while (p) {
        NamedString *s = static_cast<NamedString *>(p->get());
        if (s && ((s->name() == name) || s->name().startsWith(tmp)))
            p->remove();
	else
	    p = p->next();
    }
    return *this;
}