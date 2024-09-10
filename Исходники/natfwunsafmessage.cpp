// -----------------------------------------------------------------------------
// CNATFWUNSAFMessage::EncodeL
// 1. Encode the UNSAF message normally.
// 2. Create a MESSAGE-INTEGRITY attribute. This updates also the header's
//    length field to include the MESSAGE-INTEGRITY before computing the hash.
// 3. Encode it to the last attribute of the UNSAF message.
// 4. Create a FINGERPRINT attribute. This updates also the header's
//    length field to include the FINGERPRINT before computing the hash.
// 5. Encode it to the last attribute of the UNSAF message.
// -----------------------------------------------------------------------------
//
EXPORT_C CBufBase* CNATFWUNSAFMessage::EncodeL(
    const TDesC8& aSharedSecret,
    TBool aUseFingerprint) const
{
    CBufBase* msg = EncodeL();
    CleanupStack::PushL(msg);
    if ( aSharedSecret.Length() )
    {
        //Long term credentials need be used if there's a REALM attribute
        CNATFWUNSAFMessageIntegrityAttribute* msgIntegrity =
            CNATFWUNSAFMessageIntegrityAttribute::NewLC(aSharedSecret, *msg,
                    HasAttribute( CNATFWUNSAFAttribute::ERealm ));

        HBufC8* encodedMsgIntegrity = msgIntegrity->EncodeL();
        CleanupStack::PushL(encodedMsgIntegrity);
        msg->InsertL(msg->Size(), *encodedMsgIntegrity);
        CleanupStack::PopAndDestroy(encodedMsgIntegrity);
        CleanupStack::PopAndDestroy(msgIntegrity);
    }
    if ( aUseFingerprint )
    {
        CNATFWUNSAFFingerprintAttribute* fingerprint =
            CNATFWUNSAFFingerprintAttribute::NewLC(*msg);

        HBufC8* encodedFingerprint = fingerprint->EncodeL();
        CleanupStack::PushL(encodedFingerprint);
        msg->InsertL(msg->Size(), *encodedFingerprint);
        CleanupStack::PopAndDestroy(encodedFingerprint);
        CleanupStack::PopAndDestroy(fingerprint);
    }

    CleanupStack::Pop(msg);
    msg->Compress();

    return msg;
}