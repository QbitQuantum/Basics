// -----------------------------------------------------------------------------
// CFSMailMessage::AttachmentListL
// -----------------------------------------------------------------------------
EXPORT_C void CFSMailMessage::AttachmentListL(
    RPointerArray<CFSMailMessagePart>& aParts )
    {
    // First list all message parts
    AppendAttachmentsL( aParts );
    
    NM_FUNCTION;
    
    // special case, if single part content type is not given,
    // default type is text/plain
    if ( aParts.Count() == 1 && aParts[0]->GetContentType().Length() == 0)
        {
        aParts.ResetAndDestroy();
        }
    else
        {
        // find plain text body part from the list
        CFSMailMessagePart* txtPart = FindBodyPartL(KFSMailContentTypeTextPlain);
        CleanupStack::PushL( txtPart );
        if ( txtPart
          && txtPart->AttachmentNameL().Length() == 0 ) // real attachments have names
            {
            // remove plain text body part from attachment list
            for ( TInt ii = aParts.Count() - 1; ii >= 0; --ii )
                {
                if ( aParts[ii]->GetPartId() == txtPart->GetPartId() )
                    {
                    delete aParts[ii];
                    aParts.Remove(ii);
                    break;
                    }
                }
            }
        CleanupStack::PopAndDestroy( txtPart );

        // find  html body part from the list
        CFSMailMessagePart* htmlPart = FindBodyPartL(KFSMailContentTypeTextHtml);
        CleanupStack::PushL( htmlPart );
        if ( htmlPart
          && htmlPart->AttachmentNameL().Length() == 0 ) // real attachments have names
            {
            // remove html body part from attachment list
            for ( TInt ii = aParts.Count() - 1; ii >= 0; --ii )
                {
                if ( aParts[ii]->GetPartId() == htmlPart->GetPartId() )
                    {
                    delete aParts[ii];
                    aParts.Remove(ii);
                    break;
                    }
                }
            }
        CleanupStack::PopAndDestroy( htmlPart );
        }

    iMessageParts.ResetAndDestroy();
    iReadMessageParts = ETrue;
    }