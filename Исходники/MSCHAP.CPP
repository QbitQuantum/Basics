inline void CPppMsChap::MakeDesKey(const TDesC8& aMsChapKey, 
				TDes8& aDesKey)
/**
   Creates a DES key by inserting the parity bits.  The DES algorithm
   takes as input a 64-bit stream where the 8th, 16th, 24th, etc. bits
   are parity bits ignored by the encrypting algorithm.
   @param aMsChapKey [in] A key used by MS-CHAP for DES encryption. (7
   octets).
   @param aDesKey [out] A DES key (8 octets).
   @internalComponent
*/
	{
	ASSERT(aMsChapKey.Length() == KPppMsChapDESKeySize);
	ASSERT(aDesKey.Length() == KPppDESKeySize);

// RFC 2433, RFC 2759: "Use the DES encryption algorithm [4] in ECB
// mode [10] to encrypt Clear into Cypher such that Cypher can only be
// decrypted back to Clear by providing Key.  Note that the DES
// algorithm takes as input a 64-bit stream where the 8th, 16th, 24th,
// etc.  bits are parity bits ignored by the encrypting algorithm.
// Unless you write your own DES to accept 56-bit input without
// parity, you will need to insert the parity bits yourself."

	TUint8* pdk = const_cast<TUint8*>(aDesKey.Ptr());
	const TUint8* pmk = aMsChapKey.Ptr();
	TUint16 high, low;
	TUint8 i = 0;
    do
		{
		high = *(pmk + i/8);
		low = *(pmk + i/8 + 1);
		*(pdk + i/7) = static_cast<TUint8>(
			((high << 8 | low) >> (8 - i%8)) & 0xfe);
		i += 7;
		}
	while (i < 49);

	*(pdk + 7) = static_cast<TUint8>(*(pmk + 6) << 1 & 0xfe);

	ASSERT(aDesKey.Length() == KPppDESKeySize);
	}