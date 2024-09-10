void CPppMsChap2::ChallengeHashL(const TDesC8& aPeerChallenge,
                                 const TDesC8& aAuthenticatorChallenge,
                                 const TDesC8& aUserName,
                                 TDes8& aChallengeHash)
/**
   Computes the hash of the Peer Challenge, Authenticator Challenge
   and username using SHA-1.
   @param aPeerChallenge [in] The Peer Challenge (16 octets).
   @param aAuthenticatorChallenge [in] The Authenticator Challenge (16
   octets).
   @param aUserName [in] The Microsoft Windows NT username (0 to 256
   char).
   @param aChallengeHash [out] The hash of the peer challenge,
   authenticator challenge and username, computed using SHA-1 (8
   octets).
   @note This function implements the ChallengeHash routine specified
   in RFC 2759.
   @internalComponent
*/
{
    ASSERT(aPeerChallenge.Length() ==
           KPppMsChap2PeerChallengeSize);
    ASSERT(aAuthenticatorChallenge.Length() ==
           KPppMsChap2AuthenticatorChallengeSize);
    ASSERT(aUserName.Length() <= KPppMsChapMaxNTUserNameLength);
    ASSERT(aChallengeHash.Length()==KPppMsChap2ChallengeHashSize);

    CSHA1* sha1 = CSHA1::NewL();
    CleanupStack::PushL(sha1);

// RFC 2759: "Only the user name (as presented by the peer and
// excluding any prepended domain name)"
    TPtrC8 userName(aUserName);
    TInt i = aUserName.Locate('\\');
    if (i >= 0 && i < userName.Length() - 1)
        userName.Set(aUserName.Mid(i + 1));
    else if (i >= userName.Length() - 1)
        User::Leave(KErrGeneral);


    sha1->Update(aPeerChallenge);
    sha1->Update(aAuthenticatorChallenge);

    aChallengeHash.Copy(sha1->Final(userName).Ptr(),
                        KPppMsChap2ChallengeHashSize);


    CleanupStack::PopAndDestroy(sha1);

    ASSERT(aChallengeHash.Length()==KPppMsChap2ChallengeHashSize);
}