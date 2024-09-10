//
// Test for the canonical Apple CA certificate
//
bool isAppleCA(SecCertificateRef cert)
{
	return verifyHash(cert, gAppleAnchorHash);
}