// -----------------------------------------------------------------------------
// CSdpConnectionField::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CSdpConnectionField::ConstructL(
    const TInetAddr& aAddress,
    TInt aTTL,
    TUint aNumOfAddress )
	{
    __ASSERT_ALWAYS( IsValidAddress(aAddress, aTTL, aNumOfAddress) == KErrNone,
                     User::Leave( KErrSdpCodecConnectionField ) );

    iPool = SdpCodecStringPool::StringPoolL();
    TBuf<KMaxIPDesLength> addr;
    //If aAddress is IPv4-Mapped IPv6,the result of Output is IPv4
    aAddress.Output( addr );

    // Copy address
    iAddress = HBufC8::NewL( addr.Length() );
    iAddress->Des().Copy( addr );

    // TTL
    iTTL = aTTL;
    // Num of addresses
    iNumOfAddress = aNumOfAddress;
    // Network type
    iNetType = iPool.StringF( SdpCodecStringConstants::ENetType,
                              SdpCodecStringConstants::Table ).Copy();
    // Address type
	if ( UriUtils::HostType( addr ) == UriUtils::EIPv4Host )
		{
		//addresstype for IPv4
			iAddressType = iPool.StringF( SdpCodecStringConstants::EAddressTypeIP4,
                                      SdpCodecStringConstants::Table ).Copy();
			}
	else if ( UriUtils::HostType( addr ) == UriUtils::EIPv6Host )
			{
			//addresstype IPv6
			iAddressType = iPool.StringF( SdpCodecStringConstants::EAddressType,
                                      SdpCodecStringConstants::Table ).Copy();
			}
	else
		{
		User::Leave(KErrArgument);
		}

	__TEST_INVARIANT;
	}