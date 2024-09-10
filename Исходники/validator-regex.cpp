void
ValidatorRegex::checkPolicy(const Data& data,
                            int nSteps,
                            const OnDataValidated& onValidated,
                            const OnDataValidationFailed& onValidationFailed,
                            vector<shared_ptr<ValidationRequest> >& nextSteps)
{
  if (m_stepLimit == nSteps)
    return onValidationFailed(data.shared_from_this(),
                              "Maximum steps of validation reached: " +
                              data.getName().toUri());

  for (RuleList::iterator it = m_mustFailVerify.begin();
       it != m_mustFailVerify.end();
       it++)
    if ((*it)->satisfy(data))
      return onValidationFailed(data.shared_from_this(),
                                "Comply with mustFail policy: " +
                                data.getName().toUri());

  for (RuleList::iterator it = m_verifyPolicies.begin();
       it != m_verifyPolicies.end();
       it++)
    {
      if ((*it)->satisfy(data))
        {
          try
            {
              SignatureSha256WithRsa sig(data.getSignature());

              Name keyLocatorName = sig.getKeyLocator().getName();
              shared_ptr<const Certificate> trustedCert;
              if (m_trustAnchors.end() == m_trustAnchors.find(keyLocatorName))
                trustedCert = m_certificateCache->getCertificate(keyLocatorName);
              else
                trustedCert = m_trustAnchors[keyLocatorName];

              if (static_cast<bool>(trustedCert))
                {
                  if (verifySignature(data, sig, trustedCert->getPublicKeyInfo()))
                    return onValidated(data.shared_from_this());
                  else
                    return onValidationFailed(data.shared_from_this(),
                                              "Cannot verify signature: " +
                                              data.getName().toUri());
                }
              else
                {
                  // KeyLocator is not a trust anchor

                  OnDataValidated onKeyValidated =
                    bind(&ValidatorRegex::onCertificateValidated, this, _1,
                         data.shared_from_this(), onValidated, onValidationFailed);

                  OnDataValidationFailed onKeyValidationFailed =
                    bind(&ValidatorRegex::onCertificateValidationFailed, this, _1, _2,
                         data.shared_from_this(), onValidationFailed);

                  Interest interest(sig.getKeyLocator().getName());
                  shared_ptr<ValidationRequest> nextStep =
                    make_shared<ValidationRequest>(interest,
                                                   onKeyValidated,
                                                   onKeyValidationFailed,
                                                   3,
                                                   nSteps + 1);

                  nextSteps.push_back(nextStep);

                  return;
                }
            }
          catch (SignatureSha256WithRsa::Error& e)
            {
              return onValidationFailed(data.shared_from_this(),
                                        "Not SignatureSha256WithRsa signature: " +
                                        data.getName().toUri());
            }
          catch (KeyLocator::Error& e)
            {
              return onValidationFailed(data.shared_from_this(),
                                        "Key Locator is not a name: " +
                                        data.getName().toUri());
            }
        }
    }

  return onValidationFailed(data.shared_from_this(),
                            "No policy found for data: " + data.getName().toUri());
}