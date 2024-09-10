void UmlState::importIt(FileIn & in, Token & token, UmlItem * where)
{
    where = where->container(aState, token, in);

    if (where != 0) {
        bool machine = ((token.xmiType() == "uml:StateMachine") ||
                        (token.valueOf("issubmachinestate") == "true") ||
                        (token.what() == "ownedstatemachine")); // andromda emf
        WrapperStr s = token.valueOf("name");

        if (s.isEmpty()) {
            static unsigned n = 0;

            s.sprintf((machine) ? "anonymous_state_machine_%u"
                      : "anonymous_state_%u",
                      ++n);
        }

        UmlState * st = create(where, s);

        if (st == 0)
            in.error((machine) ? "cannot create state machine '"
                     : "cannot create state '"
                     + s + "' in '" + where->name() + "'");

        st->addItem(token.xmiId(), in);

        if (token.valueOf("isactive") == "true")
            st->set_isActive(TRUE);

        WrapperStr ref = token.valueOf("submachine");
        WrapperStr spec = token.valueOf("specification");

        if (! token.closed()) {
            WrapperStr k = token.what();
            const char * kstr = k;

            while (in.read(), !token.close(kstr)) {
                s = token.what();

                if ((s == "entry") || (s == "doactivity") || (s == "exit"))
                    st->importActivity(in, token);
                else if (s == "specification") {
                    spec = token.xmiIdref();

                    if (! token.closed())
                        in.finish(s);
                }
                else
                    st->UmlItem::import(in, token);
            }
        }

        if (machine)
            st->set_Stereotype("machine");

        if (! ref.isEmpty()) {
            QMap<WrapperStr, UmlItem *>::Iterator it = All.find(ref);

            if (it == All.end())
                UnresolvedWithContext::add(st, ref, 4);
            else if ((*it)->kind() == aState)
                st->set_Reference((UmlState *) *it);
        }

        if (! spec.isEmpty()) {
            QMap<WrapperStr, UmlItem *>::Iterator it = All.find(spec);

            if (it == All.end())
                UnresolvedWithContext::add(st, spec, 3);
            else if ((*it)->kind() == anOperation)
                st->set_Specification((UmlOperation *) *it);
        }

        st->unload(TRUE, FALSE);
    }
}