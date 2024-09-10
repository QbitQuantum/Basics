//---------------------------------------------------------------
// CNativeMmsUtility::resolvedByContentIdL
// @see header
//---------------------------------------------------------------
TBool CNativeMmsUtility::resolvedByContentIdL(const TPtrC8& contentidptr,
                                              const CUri16& targeturi)
{
#ifdef _DEBUG_TRACES_
    qDebug() << " Enter CNativeMmsUtility::resolvedByContentIdL";
#endif

    TBool result = EFalse;
    TUriParser8 parser;
    CUri16* contIdUri = NULL;
    HBufC8* contentId = NULL;

    //get content-id uri
    if (contentidptr.Length())
    {
        //Copy string to 8-bit descriptor
        contentId = HBufC8::NewLC(contentidptr.Length());

        if (contentId->Find(KCidLeftAngle) == 0
                && contentId->Find(KCidRightAngle) == contentId->Length() - 1)
        {
            // When comparing against cid, remove "<" and ">"
            contentId->Des().Copy(contentidptr.Mid(1, contentidptr.Length() - 2));
        }
        else
        {
            contentId->Des().Copy(contentidptr);
        }

        parser.Parse(*contentId);
        contIdUri = UriUtils::ConvertToDisplayFormL(parser);
        CleanupStack::PushL(contIdUri);
    }

    //compare content-id against the target uri
    if ( (contentidptr.Length())
            && (targeturi.Uri().UriDes().CompareF(contIdUri->Uri().UriDes())
                    == 0))
    {
#ifdef _DEBUG_TRACES_
		qDebug() << " Exit CNativeMmsUtility::resolvedByContentIdL";
#endif

        result = ETrue;
    }

    //do some cleanup
    if (contentId)
    {
        CleanupStack::PopAndDestroy(2, contentId); // contentId, contIdUri
    }

#ifdef _DEBUG_TRACES_
		qDebug() << " Exit CNativeMmsUtility::resolvedByContentIdL";
#endif

    return result;
}