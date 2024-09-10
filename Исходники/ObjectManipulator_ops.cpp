void ObjectManipulator::autorename(list<FWObject*> &obj_list,
                                   const string &objtype,
                                   const string &namesuffix)
{
    for (list<FWObject*>::iterator j=obj_list.begin(); j!=obj_list.end(); ++j)
    {
        FWObject *obj = *j;
        QString old_name = obj->getName().c_str();
        FWObject *parent = obj->getParent();
        QString name = getStandardName(parent, objtype, namesuffix);
        name = makeNameUnique(parent, name, objtype.c_str());
        if (name != old_name)
        {
            FWCmdChange* cmd = new FWCmdChangeName(m_project, obj);
            FWObject* new_state = cmd->getNewState();
            new_state->setName(string(name.toUtf8()));
            m_project->undoStack->push(cmd);
        }
    }
}