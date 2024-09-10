// static
bool LegacySymmetric::Encrypt(
    const LegacySymmetric& theKey,
    const String& strPlaintext,
    String& strOutput,
    const String& pstrDisplay,
    bool bBookends,
    const OTPassword* pAlreadyHavePW)
{
    if (!theKey.IsGenerated()) {
        LogDetail(OT_METHOD)(__FUNCTION__)(
            ": Failure: theKey.IsGenerated() was false. (The calling "
            "code probably should have checked that key already...).")
            .Flush();
        return false;
    }

    if (!strPlaintext.Exists()) {
        LogDetail(OT_METHOD)(__FUNCTION__)(
            ": Plaintext is empty. Please supply. (Failure).")
            .Flush();
        return false;
    }

    // By this point, we know we have a plaintext and a symmetric Key.
    //
    std::unique_ptr<OTPassword> pPassUserInput;

    if (nullptr == pAlreadyHavePW) {
        const char* szDisplay = "Password-protecting a plaintext.";
        const auto strDisplay = String::Factory(
            (!pstrDisplay.Exists()) ? szDisplay : pstrDisplay.Get());

        pPassUserInput.reset(
            GetPassphraseFromUser(strDisplay));  // bAskTwice=false
                                                 // by default.
    } else
        pPassUserInput.reset(new OTPassword(*pAlreadyHavePW));

    auto ascOutput = Armored::Factory();
    bool bSuccess = false;

    if (nullptr != pPassUserInput)  // Success retrieving the passphrase from
                                    // the user. (Now let's encrypt...)
    {
        OTEnvelope theEnvelope;

        if (theEnvelope.Encrypt(
                strPlaintext,
                const_cast<LegacySymmetric&>(theKey),
                *pPassUserInput) &&
            theEnvelope.GetCiphertext(ascOutput)) {
            bSuccess = true;

            if (bBookends) {
                return ascOutput->WriteArmoredString(
                    strOutput,
                    "SYMMETRIC MSG",  // todo hardcoding.
                    false);           // bEscaped=false
            } else {
                strOutput.Set(ascOutput->Get());
            }
        } else {
            LogDetail(OT_METHOD)(__FUNCTION__)(
                ": Failed trying to encrypt. (Sorry).")
                .Flush();
        }
    } else
        LogDetail(OT_METHOD)(__FUNCTION__)(
            ": Sorry, unable to retrieve passphrase from user. (Failure).")
            .Flush();

    return bSuccess;
}