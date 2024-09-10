bool SerializedValidation::isValid (uint256 const& signingHash) const
{
    try
    {
        const ECDSA fullyCanonical = getFlags () & vfFullyCanonicalSig ?
                                            ECDSA::strict : ECDSA::not_strict;
        RippleAddress   raPublicKey = RippleAddress::createNodePublic (getFieldVL (sfSigningPubKey));
        return raPublicKey.isValid () &&
			raPublicKey.verifySignature(signingHash, getFieldVL(sfSignature));
    }
    catch (...)
    {
        Log (lsINFO) << "exception validating validation";
        return false;
    }
}