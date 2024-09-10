void
ASTCiNumberNode::addExpectedAttributes(ExpectedAttributes& attributes, 
                                     XMLInputStream& stream)
{
  ASTBase::addExpectedAttributes(attributes, stream);

  SBMLNamespaces * sbmlns = stream.getSBMLNamespaces();
  if (sbmlns != NULL)
  {
    if (sbmlns->getLevel() > 2)
    {
      attributes.add("definitionURL");
    }
    else if (sbmlns->getLevel() == 2 && sbmlns->getVersion() == 5)
    {
      attributes.add("definitionURL");
    }
  }
}