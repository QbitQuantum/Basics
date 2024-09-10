/** @cond doxygenLibsbmlInternal */
void TextGlyph::readAttributes (const XMLAttributes& attributes,
                                const ExpectedAttributes& expectedAttributes)
{
	const unsigned int sbmlLevel   = getLevel  ();
	const unsigned int sbmlVersion = getVersion();

	unsigned int numErrs;

	/* look to see whether an unknown attribute error was logged
	 * during the read of the listOfTextGlyphs - which will have
	 * happened immediately prior to this read
	*/

  bool loSubGlyphs = false;
  if (getParentSBMLObject() != NULL
    && getParentSBMLObject()->getElementName() == "listOfSubGlyphs")
  {
    loSubGlyphs = true;
  }

	if (getErrorLog() != NULL &&
	    static_cast<ListOfTextGlyphs*>(getParentSBMLObject())->size() < 2)
	{
		numErrs = getErrorLog()->getNumErrors();
		for (int n = numErrs-1; n >= 0; n--)
		{
			if (getErrorLog()->getError(n)->getErrorId() == UnknownPackageAttribute)
			{
				const std::string details =
				      getErrorLog()->getError(n)->getMessage();
				getErrorLog()->remove(UnknownPackageAttribute);
        if (loSubGlyphs == true)
        {
				  getErrorLog()->logPackageError("layout", 
                                    LayoutLOSubGlyphAllowedAttribs,
				            getPackageVersion(), sbmlLevel, sbmlVersion, details);
        }
        else
        {
				  getErrorLog()->logPackageError("layout", 
                                    LayoutLOTextGlyphAllowedAttributes,
				            getPackageVersion(), sbmlLevel, sbmlVersion, details);
        }
			}
			else if (getErrorLog()->getError(n)->getErrorId() == UnknownCoreAttribute)
			{
				const std::string details =
				           getErrorLog()->getError(n)->getMessage();
				getErrorLog()->remove(UnknownCoreAttribute);
        if (loSubGlyphs == true)
        {
				  getErrorLog()->logPackageError("layout", 
                                    LayoutLOSubGlyphAllowedAttribs,
				            getPackageVersion(), sbmlLevel, sbmlVersion, details);
        }
        else
        {
				  getErrorLog()->logPackageError("layout", 
                                    LayoutLOTextGlyphAllowedAttributes,
				            getPackageVersion(), sbmlLevel, sbmlVersion, details);
        }
			}
		}
	}

	GraphicalObject::readAttributes(attributes, expectedAttributes);

	// look to see whether an unknown attribute error was logged
	if (getErrorLog() != NULL)
	{
		numErrs = getErrorLog()->getNumErrors();
		for (int n = numErrs-1; n >= 0; n--)
		{
			if (getErrorLog()->getError(n)->getErrorId() == UnknownPackageAttribute)
			{
				const std::string details =
				                  getErrorLog()->getError(n)->getMessage();
				getErrorLog()->remove(UnknownPackageAttribute);
				getErrorLog()->logPackageError("layout", LayoutTGAllowedAttributes,
				               getPackageVersion(), sbmlLevel, sbmlVersion, details);
			}
			else if (getErrorLog()->getError(n)->getErrorId() == UnknownCoreAttribute)
			{
				const std::string details =
				                  getErrorLog()->getError(n)->getMessage();
				getErrorLog()->remove(UnknownCoreAttribute);
				getErrorLog()->logPackageError("layout", LayoutTGAllowedCoreAttributes,
				               getPackageVersion(), sbmlLevel, sbmlVersion, details);
			}
		}
	}

	bool assigned = false;

	//
	// graphicalObject SIdRef   ( use = "optional" )
	//
	assigned = attributes.readInto("graphicalObject", mGraphicalObject);

	if (assigned == true && getErrorLog() != NULL)
	{
		// check string is not empty and correct syntax

		if (mGraphicalObject.empty() == true)
		{
			logEmptyString(mGraphicalObject, getLevel(), getVersion(), "<TextGlyph>");
		}
		else if (SyntaxChecker::isValidSBMLSId(mGraphicalObject) == false)
		{
			getErrorLog()->logPackageError("layout", LayoutTGGraphicalObjectSyntax,
				             getPackageVersion(), sbmlLevel, sbmlVersion);
		}
	}

	//
	// text string   ( use = "optional" )
	//
	assigned = attributes.readInto("text", mText);

	if (assigned == true && getErrorLog() != NULL)
	{
		// check string is not empty

		if (mText.empty() == true)
		{
			logEmptyString(mText, getLevel(), getVersion(), "<TextGlyph>");
		}
	}

	//
	// originOfText SIdRef   ( use = "optional" )
	//
	assigned = attributes.readInto("originOfText", mOriginOfText);

	if (assigned == true && getErrorLog() != NULL)
	{
		// check string is not empty and correct syntax

		if (mOriginOfText.empty() == true)
		{
			logEmptyString(mOriginOfText, getLevel(), getVersion(), "<TextGlyph>");
		}
		else if (SyntaxChecker::isValidSBMLSId(mOriginOfText) == false)
		{
			getErrorLog()->logPackageError("layout", LayoutTGOriginOfTextSyntax,
				             getPackageVersion(), sbmlLevel, sbmlVersion);
		}
	}

}