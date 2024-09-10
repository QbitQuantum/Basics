void Scope::deprecation10378(Loc loc, Dsymbol *sold, Dsymbol *snew)
{
    // Bugzilla 15857
    //
    // The overloadset found via the new lookup rules is either
    // equal or a subset of the overloadset found via the old
    // lookup rules, so it suffices to compare the dimension to
    // check for equality.
    OverloadSet *osold = NULL;
    OverloadSet *osnew = NULL;
    if (sold && (osold = sold->isOverloadSet()) != NULL &&
        snew && (osnew = snew->isOverloadSet()) != NULL &&
        osold->a.dim == osnew->a.dim)
        return;

    OutBuffer buf;
    buf.writestring("local import search method found ");
    if (osold)
        buf.printf("%s %s (%d overloads)", sold->kind(), sold->toPrettyChars(), (int)osold->a.dim);
    else if (sold)
        buf.printf("%s %s", sold->kind(), sold->toPrettyChars());
    else
        buf.writestring("nothing");
    buf.writestring(" instead of ");
    if (osnew)
        buf.printf("%s %s (%d overloads)", snew->kind(), snew->toPrettyChars(), (int)osnew->a.dim);
    else if (snew)
        buf.printf("%s %s", snew->kind(), snew->toPrettyChars());
    else
        buf.writestring("nothing");

    deprecation(loc, "%s", buf.peekString());
}