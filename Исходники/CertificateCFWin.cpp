RetainPtr<CFDataRef> copyCertificateToData(PCCERT_CONTEXT certificate)
{
    static CFAllocatorRef certDealloc = createCertContextDeallocator();
    PCCERT_CONTEXT certificateCopy = CertDuplicateCertificateContext(certificate);
    return RetainPtr<CFDataRef>(AdoptCF, CFDataCreateWithBytesNoCopy(kCFAllocatorDefault, reinterpret_cast<const UInt8*>(certificateCopy), sizeof(*certificateCopy), certDealloc));
}