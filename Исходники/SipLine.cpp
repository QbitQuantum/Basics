UtlBoolean SipLine::getPreferredContactUri(Url& preferredContactUri) const
{
    UtlString host ; 

    preferredContactUri = mPreferredContactUri ;
    preferredContactUri.getHostAddress(host) ;

    return (host.length() > 0) ;
}