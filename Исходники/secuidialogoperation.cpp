// ---------------------------------------------------------------------------
// CSecuiDialogOperation::ShowWarningNoteL()
// ---------------------------------------------------------------------------
//
void CSecuiDialogOperation::ShowWarningNoteL( const TDesC& aMessage )
    {
    CHbDeviceMessageBoxSymbian *note =
            CHbDeviceMessageBoxSymbian::NewL( CHbDeviceMessageBoxSymbian::EWarning );
    CleanupStack::PushL( note );
    note->SetTextL( aMessage );
    (void)note->ExecL();    // waits for response or timeout
    CleanupStack::PopAndDestroy( note );
    }