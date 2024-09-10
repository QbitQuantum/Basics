EXPORT_C TInt CDosExtensionBase::ExecuteMessageL(const RMessage2& aMessage)
{
    
    API_TRACE_( "[DOSSERVER] CDosExtensionBase::ExecuteMessageL(...)" );
	__ASSERT_DEBUG(aMessage.Function() == ECallFunction, 
		PanicClient(aMessage,EPanicIllegalFunction));

	TInt retVal(KErrNone);
	TBool parameterModifiedByDSY(EFalse);

	// Get data from RMessage
	TExtensionParPckg extPars;
	aMessage.ReadL(0, extPars);
	
	TInt dataLength(extPars().iParLength);
	if (dataLength >= 0)
	{
		HBufC8* dataBuffer = HBufC8::NewMaxLC( dataLength );
		TPtr8 dataPtr = dataBuffer->Des();
		aMessage.ReadL( 1, dataPtr );

		// Check autocomplete flag
		TUint autoCompl(aMessage.Int2());
		if (autoCompl == KAutoComplete)
		{
            COM_TRACE_4( "[DOSSERVER] MDosExtensionBaseDSY::CallFunctionL(0x%x,0x%x,0x%x,0x%x)"
                ,extPars().iFunc
                ,dataPtr.Ptr()
                ,dataPtr.Length()
                ,autoCompl );

			retVal = CallFunctionL(extPars().iFunc, const_cast<TUint8*>(dataPtr.Ptr()), dataPtr.Length(), parameterModifiedByDSY);

			if((retVal == KErrNone) && parameterModifiedByDSY)
			{
				// Write over client's parameters
				retVal = aMessage.Write(1, dataPtr);
			}
		}
		else
		{
			COM_TRACE_3( "[DOSSERVER] MDosExtensionBaseDSY::CallFunctionAndCompleteL(0x%x,0x%x,0x%x)"
                ,extPars().iFunc
                ,dataPtr.Ptr()
                ,dataPtr.Length() );
        
            CallFunctionAndCompleteL(extPars().iFunc, const_cast<TUint8*>(dataPtr.Ptr()), dataPtr.Length(), aMessage);
		}

		CleanupStack::PopAndDestroy(); // dataBuffer
	}
	else
	{
		// Client passed negative parameter length
		retVal = KErrGeneral;
	}

	return retVal;
}