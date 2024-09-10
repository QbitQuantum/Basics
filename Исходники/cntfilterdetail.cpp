/*
 * Returns the hash code(s) to use when matching the supplied phone number.  If the
 * number supplied has more actual phone digits (i.e. not including spaces) than
 * KLowerSevenDigits, a second hash is generated to hold the remaining most
 * significant phone digits. Removes the non-digit characters.

 * \param text Descriptor containing contacts phone number field.
 * \param lowerMatchlength Number of least significant phone digits to use.
 * \param upperMatchLength Number of most significant phone digits to use.
 * \param error Qt error code.
 * \return The hash code(s) to use when matching the supplied phone number.
 */
CntFilterDetail::TMatch CntFilterDetail::createPhoneMatchNumber(
                                            const TDesC& text, 
                                            TInt lowerMatchLength, 
                                            TInt upperMatchLength,
                                            QContactManager::Error* error)
{
    const TInt KBufLength = KCntMaxTextFieldLength+1;
    TBuf<KBufLength> buf;
    
    if (text.Length() <= KBufLength) {
        buf = text;
    }
    else {
        buf = text.Right(KBufLength);
    }
    TMatch::stripOutNonDigitChars(buf);
    
    TMatch phoneNumber;
    if (buf.Length() == 0) {
        *error = QContactManager::BadArgumentError;
        return phoneNumber;
    }
    
    // Generate a hash for the upper digits only if the phone number string is
    // large enough and more than 7 digits are to be matched.
    TInt phoneNumberlength = buf.Length();
    if ((phoneNumberlength > KLowerSevenDigits) && (upperMatchLength > 0)) {
        TPtrC upperPart = buf.Left(phoneNumberlength - KLowerSevenDigits);
        phoneNumber.iUpperDigits = TMatch::createHash(upperPart,
            upperMatchLength, phoneNumber.iNumUpperDigits);
    }
    // Generate a hash of the lower digits.
    phoneNumber.iLowerSevenDigits = TMatch::createHash(buf, 
            lowerMatchLength, phoneNumber.iNumLowerDigits);
    
    return phoneNumber;
}