/* void browse (); */
NS_IMETHODIMP CBFBROWSE::Browse()
{
    Log(ToNewUnicode(NS_LITERAL_STRING("Browse Started")));
    if (!mCallback) return NS_ERROR_FAILURE;
    DNSServiceErrorType err = kDNSServiceErr_Unknown;
    err = DNSServiceBrowse(&mSdRef, 0, mInterfaceIndex, ToNewUTF8String(mRegistrationType), ToNewUTF8String(mRegistrationDomain), (DNSServiceBrowseReply) Callback, this);
    if (err != kDNSServiceErr_NoError) return NS_ERROR_FAILURE;
    StartTimer();
    return NS_OK;
}