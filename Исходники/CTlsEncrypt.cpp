TInt CTlsEncrypt::DecryptAndVerifyL(const TDesC8& aInput,HBufC8*& aOutput,
                                    TInt64& aSeqNumber, TRecordProtocol& aType)
{

    if(!aInput.Length())
        return KErrBadDescriptor;

    TLSPROV_LOG2(_L("Before Decryption...RecordType: %d"),(TInt)aType)

    TLSPROV_LOG_HEX(aInput.Ptr(),aInput.Size() )


    TInt nAlloc = iCryptos.iDecryptor->MaxFinalOutputLength(aInput.Size()) + 24;
    if ( !aOutput || aOutput->Des().MaxLength() < nAlloc )
    {
        delete aOutput;
        aOutput = NULL;
        aOutput = HBufC8::NewL( nAlloc );
    }
    TPtr8 DecOutput = aOutput->Des();
    DecOutput.Zero();

    TRAP_IGNORE(iCryptos.iDecryptor->ProcessFinalL(aInput,DecOutput));

    TUint HashSize = KSetOfTLSCipherSuites[iCipherIndex].iHashSize;

    if(DecOutput.Length() < HashSize)
    {
        return KErrSSLAlertDecryptError;
    }

    //set ptr to MAC
    TPtrC8 ReceivedMac = DecOutput.Mid(DecOutput.Length()-HashSize,HashSize);
    //& set length to trim MAC
    DecOutput.SetLength( DecOutput.Length()-HashSize );

    TBuf8<64> CalculatedMac;

    ComputeMacL(CalculatedMac,DecOutput,ETrue,aSeqNumber,aType);

    TInt err = KErrBadMAC;
    if(ReceivedMac.Compare(CalculatedMac) == 0)
    {
        err = KErrNone;
    }
    else
    {
        TLSPROV_LOG(_L("Decryption: Received MAC error"))
        err =  KErrSSLAlertBadRecordMac;
    }

    TLSPROV_LOG(_L("After Decryption , no mac"))
    TLSPROV_LOG_HEX(aOutput->Ptr(),aOutput->Size() )

    return err;

}