ExpOperation* ExpEvaluator::popOpcode()
{
    ObjList* l = &m_opcodes;
    for (ObjList* p = l; p; p = p->next()) {
	if (p->get())
	    l = p;
    }
    return static_cast<ExpOperation*>(l->remove(false));
}