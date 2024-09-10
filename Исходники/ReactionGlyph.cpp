/** @cond doxygenLibsbmlInternal */
void ReactionGlyph::readAttributes (const XMLAttributes& attributes,
                                    const ExpectedAttributes& expectedAttributes)
{
  const unsigned int sbmlLevel   = getLevel  ();
  const unsigned int sbmlVersion = getVersion();

  unsigned int numErrs;

  /* look to see whether an unknown attribute error was logged
  * during the read of the listOfReactionGlyphs - which will have
  * happened immediately prior to this read
  */

  bool loSubGlyphs = false;
  if (getParentSBMLObject() != NULL
    && getParentSBMLObject()->getElementName() == "listOfSubGlyphs")
  {
    loSubGlyphs = true;
  }

  if (getErrorLog() != NULL &&
    static_cast<ListOfReactionGlyphs*>(getParentSBMLObject())->size() < 2)
  {
    numErrs = getErrorLog()->getNumErrors();
    for (int n = (int)numErrs-1; n >= 0; n--)
    {
      if (getErrorLog()->getError((unsigned int)n)->getErrorId() == UnknownPackageAttribute)
      {
        const std::string details =
          getErrorLog()->getError((unsigned int)n)->getMessage();
        getErrorLog()->remove(UnknownPackageAttribute);
        if (loSubGlyphs == true)
        {
          getErrorLog()->logPackageError("layout", 
            LayoutLOSubGlyphAllowedAttribs,
            getPackageVersion(), sbmlLevel, sbmlVersion, details, getLine(), getColumn());
        }
        else
        {
          getErrorLog()->logPackageError("layout", 
            LayoutLORnGlyphAllowedAttributes,
            getPackageVersion(), sbmlLevel, sbmlVersion, details, getLine(), getColumn());
        }
      }
      else if (getErrorLog()->getError((unsigned int)n)->getErrorId() == UnknownCoreAttribute)
      {
        const std::string details =
          getErrorLog()->getError((unsigned int)n)->getMessage();
        getErrorLog()->remove(UnknownCoreAttribute);
        if (loSubGlyphs == true)
        {
          getErrorLog()->logPackageError("layout", 
            LayoutLOSubGlyphAllowedAttribs,
            getPackageVersion(), sbmlLevel, sbmlVersion, details, getLine(), getColumn());
        }
        else
        {
          getErrorLog()->logPackageError("layout", 
            LayoutLORnGlyphAllowedAttributes,
            getPackageVersion(), sbmlLevel, sbmlVersion, details, getLine(), getColumn());
        }
      }
    }
  }

  GraphicalObject::readAttributes(attributes, expectedAttributes);

  // look to see whether an unknown attribute error was logged
  if (getErrorLog() != NULL)
  {
    numErrs = getErrorLog()->getNumErrors();
    for (int n = (int)numErrs-1; n >= 0; n--)
    {
      if (getErrorLog()->getError((unsigned int)n)->getErrorId() == UnknownPackageAttribute)
      {
        const std::string details =
          getErrorLog()->getError((unsigned int)n)->getMessage();
        getErrorLog()->remove(UnknownPackageAttribute);
        getErrorLog()->logPackageError("layout", LayoutRGAllowedAttributes,
          getPackageVersion(), sbmlLevel, sbmlVersion, details, getLine(), getColumn());
      }
      else if (getErrorLog()->getError((unsigned int)n)->getErrorId() == UnknownCoreAttribute)
      {
        const std::string details =
          getErrorLog()->getError((unsigned int)n)->getMessage();
        getErrorLog()->remove(UnknownCoreAttribute);
        getErrorLog()->logPackageError("layout", LayoutRGAllowedCoreAttributes,
          getPackageVersion(), sbmlLevel, sbmlVersion, details, getLine(), getColumn());
      }
    }
  }

  bool assigned = false;

  //
  // reaction SIdRef   ( use = "optional" )
  //
  assigned = attributes.readInto("reaction", mReaction);

  if (assigned == true && getErrorLog() != NULL)
  {
    // check string is not empty and correct syntax

    if (mReaction.empty() == true)
    {
      logEmptyString(mReaction, getLevel(), getVersion(), "<ReactionGlyph>");
    }
    else if (SyntaxChecker::isValidSBMLSId(mReaction) == false)
    {
      getErrorLog()->logPackageError("layout", LayoutRGReactionSyntax,
        getPackageVersion(), sbmlLevel, sbmlVersion, "The reaction on the <" 
        + getElementName() + "> is '" + mReaction + "', which does not conform to the syntax.", getLine(), getColumn());
    }
  }

}