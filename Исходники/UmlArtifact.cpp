void UmlArtifact::importIt(FileIn & in, Token & token, UmlItem * where)
{
    where = where->container(anArtifact, token, in);

    if (where == 0)
        return;

    WrapperStr s = token.valueOf("name");

    if (s.isEmpty()) {
        static unsigned n = 0;

        s.sprintf("anonymous_artifact_%u", ++n);
    }

    UmlArtifact * artifact = create((UmlDeploymentView *) where, s);

    if (artifact == 0)
        in.error("cannot create artifact '" + s +
                 "' in '" + where->name() + "'");

    artifact->addItem(token.xmiId(), in);

    if (! token.closed()) {
        WrapperStr k = token.what();
        const char * kstr = k;

        while (in.read(), !token.close(kstr)) {
            if (token.what() == "manifestation")
                Manifestation::import(in, token, artifact);
            else
                artifact->UmlItem::import(in, token);
        }
    }

    artifact->unload(TRUE, FALSE);
}