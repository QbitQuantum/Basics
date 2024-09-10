// -----------------------------------------------------------------------------
// CLandmarksModel::FormatListItemLC
// Formats a list item to the following format "X\tlandmarkName\t"
// where X = icon index
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
HBufC* CLandmarksModel::FormatListItemLC(CPosLandmark& aLandmark)
    {
    // Extract name
    TPtrC name;
    aLandmark.GetLandmarkName(name);
    // 10 extra chars for icon index and column separator
    const TInt KExtraChars = 10;
    HBufC* formattedNameBuf = HBufC::NewLC(name.Length() + KExtraChars);
    TPtr formattedNamePtr = formattedNameBuf->Des();

    // Extract icon info
    TPtrC mbmIconFile;
    TInt iconIndex, maskIndex;
    TInt res = aLandmark.GetIcon(mbmIconFile, iconIndex, maskIndex);

    // Format list item
    if (res == KErrNone)
        {
        // Create icon and append it to icon array. 
        TRAPD(err, AppendIconL(mbmIconFile, iconIndex, maskIndex));
        if (err == KErrNone)
            {
            // Append the array index where the icon is appended
            formattedNamePtr.AppendNum(iIconList->Count() - 1);
            }
        else
            {
            formattedNamePtr.AppendNum(KDefaultIconIndex);
            }
        }
    else // res == KErrNotFound
        {
        formattedNamePtr.AppendNum(KDefaultIconIndex);
        }
    formattedNamePtr.Append(KTab);
    formattedNamePtr.Append(name);

    return formattedNameBuf;
    }