otError Dtls::Send(Message &aMessage, uint16_t aLength)
{
    otError error = OT_ERROR_NONE;
    uint8_t buffer[kApplicationDataMaxLength];

    VerifyOrExit(aLength <= kApplicationDataMaxLength, error = OT_ERROR_NO_BUFS);

    // Store message specific sub type.
    if (aMessage.GetSubType() != Message::kSubTypeNone)
    {
        mMessageSubType = aMessage.GetSubType();
    }

    aMessage.Read(0, aLength, buffer);

    SuccessOrExit(error = MapError(mbedtls_ssl_write(&mSsl, buffer, aLength)));

    aMessage.Free();

exit:
    return error;
}