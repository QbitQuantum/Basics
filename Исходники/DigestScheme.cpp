ECode DigestScheme::CreateMessageDigest(
    /* [in] */ const String& digAlg,
    /* [out] */ IMessageDigest** digest)
{
    VALIDATE_NOT_NULL(digest)
    // try {
    AutoPtr<IMessageDigestHelper> helper;
    CMessageDigestHelper::AcquireSingleton((IMessageDigestHelper**)&helper);
    ECode ec = helper->GetInstance(digAlg, digest);
    if (FAILED(ec)) {
        *digest = NULL;
        Logger::E("DigestScheme", "Unsupported algorithm in HTTP Digest authentication: %s", digAlg.string());
        return E_UNSUPPORTED_ALGORITHM_IN_HTTP_DIGEST_AUTHENTICATION;
    }
    return NOERROR;
    // } catch (Exception e) {
    //     throw new UnsupportedDigestAlgorithmException(
    //       "Unsupported algorithm in HTTP Digest authentication: "
    //        + digAlg);
    // }
}