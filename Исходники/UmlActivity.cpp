void UmlActivity::importIt(FileIn & in, Token & token, UmlItem * where)
{
    where = where->container(anActivity, token, in);

    if (where != 0) {
        WrapperStr s = token.valueOf("name");

        if (s.isEmpty()) {
            static unsigned n = 0;

            s.sprintf("anonymous_activity_%u", ++n);
        }

        UmlActivity * a = create((UmlClassView *) where, s);

        if (a == 0)
            in.error("cannot create activity '"
                     + s + "' in '" + where->name() + "'");

        a->addItem(token.xmiId(), in);

        if (token.valueOf("isreadonly") == "true")
            a->set_isReadOnly(TRUE);

        if (token.valueOf("issingleexecution") == "true")
            a->set_isSingleExecution(TRUE);

        if (token.valueOf("isactive") == "true")
            a->set_isActive(TRUE);

        WrapperStr spec = token.valueOf("specification");

        if (! token.closed()) {
            WrapperStr k = token.what();
            const char * kstr = k;

            while (in.read(), !token.close(kstr)) {
                s = token.what();

                if ((s == "precondition") || (s == "postcondition") ||
                    (s == "localprecondition") || (s == "localpostcondition"))
                    a->readCondition(in, token);
                else if (s == "ownedparameter")
                    a->readParameter(in, token);
                else if ((s == "node") &&
                         (token.xmiType() == "uml:ActivityParameterNode"))
                    a->readParameterNode(in, token);
                else if (s == "specification") {
                    spec = token.xmiIdref();

                    if (! token.closed())
                        in.finish(s);
                }
                else if (s == "ownedrule")
                    a->set_Constraint(UmlItem::readConstraint(in, token));
                else
                    a->UmlItem::import(in, token);
            }
        }

        if (! spec.isEmpty()) {
            QMap<WrapperStr, UmlItem *>::Iterator it = All.find(spec);

            if (it == All.end())
                Unresolved::addRef(a, spec);
            else if ((*it)->kind() == anOperation)
                a->set_Specification((UmlOperation *) *it);
        }

        a->unload(TRUE, FALSE);
    }
}