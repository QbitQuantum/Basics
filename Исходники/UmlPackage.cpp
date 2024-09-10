void UmlPackage::importIt(FileIn & in, Token & token, UmlItem * where)
{
    while (where->kind() != aPackage)
        where = where->parent();

    WrapperStr s = token.valueOf("name");

    if (s.isEmpty()) {
        static unsigned n = 0;

        s.sprintf("anonymous %u", ++n);
    }

    UmlPackage * pack = create((UmlPackage *) where, s);

    if (pack == 0)
        in.error("cannot create package '" + s + "' in '" + where->name() + "'");

    bool profile =
        (token.what() == "uml:profile") || (token.xmiType() == "uml:Profile");

    if (profile) {
        pack->set_Stereotype("profile");
        pack->set_PropertyValue("xmiId", token.xmiId());
        NumberOf -= 1;
        NumberOfProfile += 1;

        if (!(s = token.valueOf("metamodelreference")).isEmpty())
            pack->set_PropertyValue("metamodelReference", s);

        if (!(s = token.valueOf("metaclassreference")).isEmpty())
            pack->set_PropertyValue("metaclassReference", s);
    }

    s = token.xmiId();

    if (!s.isEmpty()) {
        pack->addItem(s, in);

        if (! token.closed()) {
            WrapperStr k = token.what();
            const char * kstr = k;

            if (profile) {
                while (in.read(), !token.close(kstr)) {
                    if ((token.what() == "packagedelement") &&
                        (token.xmiType() == "uml:Extension")) {
                        if (! token.closed())
                            in.finish(token.what());
                    }
                    else if (token.what() == "packageimport")
                        pack->packageImport(in, token);
                    else
                        pack->UmlItem::import(in, token);
                }

                updateProfiles();
            }
            else
                while (in.read(), !token.close(kstr))
                    pack->UmlItem::import(in, token);
        }
    }
    else if (! token.valueOf("href", s))
        in.error("xmi:id is missing"); // doesn't return
    else {
        in.warning("bypass external package " + s);

        if (! token.closed())
            in.finish(token.what());
    }

    pack->unload(TRUE, FALSE);
}