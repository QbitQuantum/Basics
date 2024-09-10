void DocSets::writeToken(FTextStream &t,
                         const Definition *d,
                         const QCString &type,
                         const QCString &lang,
                         const char *scope,
                         const char *anchor,
                         const char *decl)
{
    t << "  <Token>" << endl;
    t << "    <TokenIdentifier>" << endl;
    QCString name = d->name();
    if (name.right(2)=="-p")  name=name.left(name.length()-2);
    t << "      <Name>" << convertToXML(name) << "</Name>" << endl;
    if (!lang.isEmpty())
    {
        t << "      <APILanguage>" << lang << "</APILanguage>" << endl;
    }
    if (!type.isEmpty())
    {
        t << "      <Type>" << type << "</Type>" << endl;
    }
    if (scope)
    {
        t << "      <Scope>" << convertToXML(scope) << "</Scope>" << endl;
    }
    t << "    </TokenIdentifier>" << endl;
    t << "    <Path>" << d->getOutputFileBase()
      << Doxygen::htmlFileExtension << "</Path>" << endl;
    if (anchor)
    {
        t << "    <Anchor>" << anchor << "</Anchor>" << endl;
    }
    QCString tooltip = d->briefDescriptionAsTooltip();
    if (!tooltip.isEmpty())
    {
        t << "    <Abstract>" << convertToXML(tooltip) << "</Abstract>" << endl;
    }
    if (decl)
    {
        t << "    <DeclaredIn>" << convertToXML(decl) << "</DeclaredIn>" << endl;
    }
    t << "  </Token>" << endl;
}