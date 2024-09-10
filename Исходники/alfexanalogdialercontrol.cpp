// ---------------------------------------------------------------------------
// AddNumberToDisplayPaneL
// ---------------------------------------------------------------------------
//
void CAlfExAnalogDialerControl::AddNumberToDisplayPaneL(TInt aNumber)
	{	
	if ( aNumber > 9 )
	    {
	    return;
	    }
    TBuf<8> number;        
    
    // aNumber is 0...9
    // Second parameter: number 10 must be changed to 0
    number.Format(KNumberDisplayTemplate, (aNumber+1)%10);
    if (iDisplayNumber.Length() + number.Length() <= KNumberDisplayBufferLength)
    	{
    	iDisplayNumber.Append(number);    
    	iDisplayPane->SetTextL(iDisplayNumber);
    	}
	}