QCString DiagramItem::label() const
{
  QCString result;
  if (!templSpec.isEmpty())
  {
    // we use classDef->name() here and not diplayName() in order
    // to get the name used in the inheritance relation.
    QCString n = classDef->name();
    if (/*n.right(2)=="-g" ||*/ n.right(2)=="-p")
    {
      n = n.left(n.length()-2);
    }
    result=insertTemplateSpecifierInScope(n,templSpec);
  }
  else
  {
    result=classDef->displayName();
  }
  if (Config_getBool("HIDE_SCOPE_NAMES")) result=stripScope(result);
  return result;
}