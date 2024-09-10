Result
CheckIssuerIndependentProperties(TrustDomain& trustDomain,
                                 const BackCert& cert,
                                 Time time,
                                 KeyUsage requiredKeyUsageIfPresent,
                                 KeyPurposeId requiredEKUIfPresent,
                                 const CertPolicyId& requiredPolicy,
                                 unsigned int subCACount,
                                 /*out*/ TrustLevel& trustLevel)
{
  Result rv;

  const EndEntityOrCA endEntityOrCA = cert.endEntityOrCA;

  // Check the cert's trust first, because we want to minimize the amount of
  // processing we do on a distrusted cert, in case it is trying to exploit
  // some bug in our processing.
  rv = trustDomain.GetCertTrust(endEntityOrCA, requiredPolicy, cert.GetDER(),
                                trustLevel);
  if (rv != Success) {
    return rv;
  }

  if (trustLevel == TrustLevel::TrustAnchor &&
      endEntityOrCA == EndEntityOrCA::MustBeEndEntity &&
      requiredEKUIfPresent == KeyPurposeId::id_kp_OCSPSigning) {
    // OCSP signer certificates can never be trust anchors, especially
    // since we don't support designated OCSP responders. All of the checks
    // below that are dependent on trustLevel rely on this overriding of the
    // trust level for OCSP signers.
    trustLevel = TrustLevel::InheritsTrust;
  }

  switch (trustLevel) {
    case TrustLevel::InheritsTrust:
      rv = CheckSignatureAlgorithm(trustDomain, endEntityOrCA,
                                   cert.GetSignedData(), cert.GetSignature());
      if (rv != Success) {
        return rv;
      }
      break;

    case TrustLevel::TrustAnchor:
      // We don't even bother checking signatureAlgorithm or signature for
      // syntactic validity for trust anchors, because we don't use those
      // fields for anything, and because the trust anchor might be signed
      // with a signature algorithm we don't actually support.
      break;

    case TrustLevel::ActivelyDistrusted:
      return Result::ERROR_UNTRUSTED_CERT;
  }

  // Check the SPKI early, because it is one of the most selective properties
  // of the certificate due to SHA-1 deprecation and the deprecation of
  // certificates with keys weaker than RSA 2048.
  Reader spki(cert.GetSubjectPublicKeyInfo());
  rv = der::Nested(spki, der::SEQUENCE, [&](Reader& r) {
    return CheckSubjectPublicKeyInfo(r, trustDomain, endEntityOrCA);
  });
  if (rv != Success) {
    return rv;
  }
  rv = der::End(spki);
  if (rv != Success) {
    return rv;
  }

  // 4.2.1.1. Authority Key Identifier is ignored (see bug 965136).

  // 4.2.1.2. Subject Key Identifier is ignored (see bug 965136).

  // 4.2.1.3. Key Usage
  rv = CheckKeyUsage(endEntityOrCA, cert.GetKeyUsage(),
                     requiredKeyUsageIfPresent);
  if (rv != Success) {
    return rv;
  }

  // 4.2.1.4. Certificate Policies
  rv = CheckCertificatePolicies(endEntityOrCA, cert.GetCertificatePolicies(),
                                cert.GetInhibitAnyPolicy(), trustLevel,
                                requiredPolicy);
  if (rv != Success) {
    return rv;
  }

  // 4.2.1.5. Policy Mappings are not supported; see the documentation about
  //          policy enforcement in pkix.h.

  // 4.2.1.6. Subject Alternative Name dealt with during name constraint
  //          checking and during name verification (CERT_VerifyCertName).

  // 4.2.1.7. Issuer Alternative Name is not something that needs checking.

  // 4.2.1.8. Subject Directory Attributes is not something that needs
  //          checking.

  // 4.2.1.9. Basic Constraints.
  rv = CheckBasicConstraints(endEntityOrCA, cert.GetBasicConstraints(),
                             cert.GetVersion(), trustLevel, subCACount);
  if (rv != Success) {
    return rv;
  }

  // 4.2.1.10. Name Constraints is dealt with in during path building.

  // 4.2.1.11. Policy Constraints are implicitly supported; see the
  //           documentation about policy enforcement in pkix.h.

  // 4.2.1.12. Extended Key Usage
  rv = CheckExtendedKeyUsage(endEntityOrCA, cert.GetExtKeyUsage(),
                             requiredEKUIfPresent);
  if (rv != Success) {
    return rv;
  }

  // 4.2.1.13. CRL Distribution Points is not supported, though the
  //           TrustDomain's CheckRevocation method may parse it and process it
  //           on its own.

  // 4.2.1.14. Inhibit anyPolicy is implicitly supported; see the documentation
  //           about policy enforcement in pkix.h.

  // IMPORTANT: This check must come after the other checks in order for error
  // ranking to work correctly.
  Time notBefore(Time::uninitialized);
  Time notAfter(Time::uninitialized);
  rv = CheckValidity(cert.GetValidity(), time, &notBefore, &notAfter);
  if (rv != Success) {
    return rv;
  }

  rv = trustDomain.CheckValidityIsAcceptable(notBefore, notAfter, endEntityOrCA,
                                             requiredEKUIfPresent);
  if (rv != Success) {
    return rv;
  }

  return Success;
}