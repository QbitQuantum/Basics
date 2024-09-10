CLIPPER MAPISENDMAILC3( void )
{
    MapiRecipDesc orig ;
	MapiRecipDesc rcpt ;
	MapiFileDesc  file ;
	MapiMessage   mssg ;

	orig.ulReserved         = 0            ;  // Reserved
	orig.ulRecipClass       = MAPI_ORIG    ;  // Reciepient Class MAPI_TO MAPI_CC MAPI_BCC
    orig.lpszName           = _parc( 4 )   ;  // Originator's Name
    orig.lpszAddress        = _parc( 5 )   ;  // Originators Address
	orig.ulEIDSize          = 0            ;  // Count in bytes of size of pEntryID
	orig.lpEntryID          = NULL         ;  // System-specific Originator reference

	rcpt.ulReserved         = 0            ;  // Reserved
	rcpt.ulRecipClass       = MAPI_TO      ;  // Reciepient Class MAPI_TO MAPI_CC MAPI_BCC
    rcpt.lpszName           = _parc( 6 )   ;  // Reciepient's Name, e.g., [email protected]
    rcpt.lpszAddress        = _parc( 7 )   ;  // Reciepient's Address
	rcpt.ulEIDSize          = 0            ;  // Count in bytes of size of pEntryID
	rcpt.lpEntryID          = 0            ;  // System-specific Recipient reference

    if( _parinfo(0) >= 8 )
    {
    file.ulReserved         = 0            ;  // Reserved for future usage
	file.flFlags            = 0            ;  // Flags ?
	file.nPosition          = -1           ;  // Character of text to be replaced by attachment
    file.lpszPathName       = _parc( 8 )   ;  // Full Path Name with Extension of the attached file
    file.lpszPathName       = NULL         ;  // Full Path Name with Extension of the attached file
    file.lpszFileName       = NULL         ;  // Original File Name ( optional )
	file.lpFileType         = NULL         ;  // Attachment file type ( can be lpMapiFileTagExt )
    }

	mssg.ulReserved         = 0            ;  // Reserved
    mssg.lpszSubject        = _parc( 2 )   ;  // Message Subject
    mssg.lpszNoteText       = _parc( 3 )   ;  // Message Text
	mssg.lpszMessageType    = NULL         ;  // Message Class
	mssg.lpszDateReceived   = NULL         ;  // in yyyy/mm/dd hh:mm format
	mssg.lpszConversationID = NULL         ;  // Conversation thread ID
	mssg.flFlags            = 0            ;  // unread, return receipt
	mssg.lpOriginator       = &orig        ;  // Originator's descriptor
	mssg.nRecipCount        = 1            ;  // Number of receipients
	mssg.lpRecips           = &rcpt        ;  // Recipient descriptors

    if( _parinfo(0) >= 8 )
    {
    mssg.nFileCount         = 1            ;  // Number of file attachments
	mssg.lpFiles            = &file        ;  // Attachment descriptors
    }
    else
    {
    mssg.nFileCount         = 0            ;  // Number of file attachments
    mssg.lpFiles            = NULL         ;  // Attachment descriptors
    }

	// to send the mail direcly and without intervenstion
    //_retnl( (ULONG) MAPISendMail( 0, 0, &mssg, 0, 0 ) ) ;

	// to opem default mail client's dialog box
    _retnl( (ULONG) MAPISendMail( 0, 0, &mssg, 8, 0 ) ) ;
}