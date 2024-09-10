void InsetLayout::readArgument(Lexer & lex)
{
    Layout::latexarg arg;
    arg.mandatory = false;
    bool error = false;
    bool finished = false;
    arg.font = inherit_font;
    arg.labelfont = inherit_font;
    string nr;
    lex >> nr;
    while (!finished && lex.isOK() && !error) {
        lex.next();
        string const tok = support::ascii_lowercase(lex.getString());

        if (tok.empty()) {
            continue;
        } else if (tok == "endargument") {
            finished = true;
        } else if (tok == "labelstring") {
            lex.next();
            arg.labelstring = lex.getDocString();
        } else if (tok == "menustring") {
            lex.next();
            arg.menustring = lex.getDocString();
        } else if (tok == "mandatory") {
            lex.next();
            arg.mandatory = lex.getBool();
        } else if (tok == "leftdelim") {
            lex.next();
            arg.ldelim = lex.getDocString();
            arg.ldelim = support::subst(arg.ldelim,
                                        from_ascii("<br/>"), from_ascii("\n"));
        } else if (tok == "rightdelim") {
            lex.next();
            arg.rdelim = lex.getDocString();
            arg.rdelim = support::subst(arg.rdelim,
                                        from_ascii("<br/>"), from_ascii("\n"));
        } else if (tok == "presetarg") {
            lex.next();
            arg.presetarg = lex.getDocString();
        } else if (tok == "tooltip") {
            lex.next();
            arg.tooltip = lex.getDocString();
        } else if (tok == "requires") {
            lex.next();
            arg.requires = lex.getString();
        } else if (tok == "decoration") {
            lex.next();
            arg.decoration = lex.getString();
        } else if (tok == "font") {
            arg.font = lyxRead(lex, arg.font);
        } else if (tok == "labelfont") {
            arg.labelfont = lyxRead(lex, arg.labelfont);
        } else {
            lex.printError("Unknown tag");
            error = true;
        }
    }
    if (arg.labelstring.empty())
        LYXERR0("Incomplete Argument definition!");
    else
        latexargs_[nr] = arg;
}