void UmlClass::importIt(FileIn & in, Token & token, UmlItem * where)
{
    where = where->container(aClass, token, in);	// can't be null

    WrapperStr s = token.valueOf("name");

    if (s.isEmpty()) {
        static unsigned n = 0;

        s.sprintf("anonymous_%u", ++n);
    }
    else
        s = legalName(s);

    UmlClass * cl = create(where, s);
    Association * assocclass = 0;
    bool stereotype = FALSE;

    if (cl == 0)
        in.error("cannot create classe '" + s +
                 "' in '" + where->name() + "'");

    cl->addItem(token.xmiId(), in);

    do
        where = where->parent();

    while (where->kind() != aPackage);

    if (where->stereotype() == "profile")
        cl->set_PropertyValue("xmiId", token.xmiId());

    if (token.xmiType() == "uml:Actor")
        cl->set_Stereotype("actor");
    else if (token.xmiType() == "uml:Interface")
        cl->set_Stereotype("interface");
    else if (token.xmiType() == "uml:Enumeration")
        cl->set_Stereotype("enum");
    else if (token.xmiType() == "uml:Stereotype") {
        cl->set_Stereotype("stereotype");
        NumberOf -= 1;
        NumberOfStereotype += 1;
        stereotype = TRUE;
    }
    else if (token.xmiType() == "uml:AssociationClass") {
        assocclass = &Association::get(token.xmiId(), token.valueOf("name"));
        assocclass->set_class_association();
    }

    cl->setVisibility(token.valueOf("visibility"));

    if (token.valueOf("isabstract") == "true")
        cl->set_isAbstract(TRUE);

    if (token.valueOf("isactive") == "true")
        cl->set_isActive(TRUE);

    if (! token.closed()) {
        WrapperStr k = token.what();
        const char * kstr = k;
        WrapperStr assocclass_ref1;
        WrapperStr assocclass_ref2;

        while (in.read(), !token.close(kstr)) {
            s = token.what();

            if ((s == "ownedtemplatesignature") &&
                ((token.xmiType() == "uml:TemplateSignature") ||
                 (token.xmiType() == "uml:RedefinableTemplateSignature")))
                cl->readFormal(in, token);
            else if ((s == "templatebinding") &&
                     (token.xmiType() == "uml:TemplateBinding")) {
                Binding::import(in, token, cl);
            }
            else if ((assocclass != 0) && (s == "memberend")) {
                if (assocclass_ref1.isEmpty())
                    assocclass_ref1 = token.xmiIdref();
                else
                    assocclass_ref2 = token.xmiIdref();

                if (! token.closed())
                    in.finish(s);
            }
            else if ((assocclass != 0) &&
                     (s == "ownedend") &&
                     (token.xmiType() == "uml:Property"))
                assocclass->import(in, token);
            else if (s == "ownedrule")
                cl->set_Constraint(UmlItem::readConstraint(in, token));
            else if (stereotype &&
                     (s == "icon") &&
                     (token.xmiType() == "uml:Image")) {
                WrapperStr path = token.valueOf("location");

                if (! path.isEmpty())
                    cl->set_PropertyValue("stereotypeIconPath", path);

                if (! token.closed())
                    in.finish(s);
            }
            else
                cl->UmlItem::import(in, token);
        }
    }

    cl->unload(TRUE, FALSE);
}