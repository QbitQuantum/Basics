TBool CTe_LbsIniFileReader::FindNextSection()
{
    _LIT(KSectionHeaderStart, "[");
    _LIT(KSectionHeaderEnd, "]");

    // Clear the previous section information.
    iSection.Set(KNullDesC);

    // Early check to see if we have already searched
    // to the end of the file.
    if (iSectionEnd == iPtr.Length())
    {
        return (EFalse);
    }

    // Begin searching from the end of the last section.
    TPtrC ptrSection = iPtr.Mid(iSectionEnd);

    // Search for the section header '[<text>]'.
    TInt sectionHeaderEnd(KErrNotFound);
    TInt sectionHeaderStart = ptrSection.Find(KSectionHeaderStart);
    if (sectionHeaderStart == KErrNotFound)
    {
        // No match, so no more sections in the file.
        iSectionEnd = iPtr.Length();
        return (EFalse);
    }
    else
    {
        sectionHeaderEnd = ptrSection.Find(KSectionHeaderEnd);
        if ((sectionHeaderEnd == KErrNotFound)
                || (sectionHeaderEnd < sectionHeaderStart))
        {
            // Parsing error - the section header was not closed properly
            iSectionEnd = iPtr.Length();
            return (EFalse);
        }
        else if (sectionHeaderEnd == ptrSection.Length())
        {
            // Parsing error - the section header ends at the end
            // of the file, so the section is empty!
            iSectionEnd = iPtr.Length();
            return (EFalse);
        }
    }
    iSection.Set(ptrSection.Mid(sectionHeaderEnd + 1));

    // Search for the start of the next section
    // - take this to be the end of the current section.
    TInt sectionEnd = iSection.Find(KSectionHeaderStart);
    if (sectionEnd != KErrNotFound)
    {
        iSection.Set(iSection.Left(sectionEnd));
        iSectionEnd += (sectionHeaderStart + sectionEnd + 1);
    }
    else
    {
        // No more sections after this one, so set the index to the end.
        iSectionEnd = iPtr.Length();
    }

    return (ETrue);
}