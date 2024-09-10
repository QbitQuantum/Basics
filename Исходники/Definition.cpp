void Definition::writePathFragment(OutputList &ol) const
{
  makeResident();
  if (m_impl->outerScope && m_impl->outerScope!=Doxygen::globalScope)
  {
    m_impl->outerScope->writePathFragment(ol);
  }
  ol.writeString("      <li class=\"navelem\">");
  if (isLinkable())
  {
    if (definitionType()==Definition::TypeGroup && ((const GroupDef*)this)->groupTitle())
    {
      ol.writeObjectLink(getReference(),getOutputFileBase(),0,((const GroupDef*)this)->groupTitle());
    }
    else if (definitionType()==Definition::TypePage && !((const PageDef*)this)->title().isEmpty())
    {
      ol.writeObjectLink(getReference(),getOutputFileBase(),0,((const PageDef*)this)->title());
    }
    else if (definitionType()==Definition::TypeClass)
    {
      QCString name = m_impl->localName;
      if (name.right(2)=="-p" || name.right(2)=="-g")
      {
        name = name.left(name.length()-2);
      }
      ol.writeObjectLink(getReference(),getOutputFileBase(),0,name);
    }
    else
    {
      ol.writeObjectLink(getReference(),getOutputFileBase(),0,m_impl->localName);
    }
  }
  else
  {
    ol.startBold();
    ol.docify(m_impl->localName);
    ol.endBold();
  }
  ol.writeString("      </li>\n");
}