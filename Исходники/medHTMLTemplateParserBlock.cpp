//----------------------------------------------------------------------------
medHTMLTemplateParserBlock::HTMLTemplateSubstitution medHTMLTemplateParserBlock::GetSubstitution( wxString name )
//----------------------------------------------------------------------------
{
    HTMLTemplateSubstitution retValue;
    int retPos;
    //get the position of the substitution
    retPos=SubstitutionPos(&name);
    if (retPos>=0)
    {
        retValue=m_SubstitutionTable[retPos];
    }
    else
    {
        mafLogMessage("HTML Template ERROR: Substitution: \"%s\" not found",name.ToAscii());
    }

    return retValue;
}