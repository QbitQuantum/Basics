void NetInterface::sendArrangedConnectRequest(NetConnection *conn)
{
   TNLLogMessageV(LogNetInterface, ("Sending Arranged Connect Request"));
   PacketStream out;

   ConnectionParameters &theParams = conn->getConnectionParameters();

   out.write(U8(ArrangedConnectRequest));
   theParams.mNonce.write(&out);
   U32 encryptPos = out.getBytePosition();
   U32 innerEncryptPos = 0;

   out.setBytePosition(encryptPos);

   theParams.mServerNonce.write(&out);
   if(out.writeFlag(theParams.mUsingCrypto))
   {
      out.write(theParams.mPrivateKey->getPublicKey());
      innerEncryptPos = out.getBytePosition();
      out.setBytePosition(innerEncryptPos);
      out.write(SymmetricCipher::KeySize, theParams.mSymmetricKey);
   }
   out.writeFlag(theParams.mDebugObjectSizes);
   out.write(conn->getInitialSendSequence());
   conn->writeConnectRequest(&out);

   if(innerEncryptPos)
   {
      SymmetricCipher theCipher(theParams.mSharedSecret);
      out.hashAndEncrypt(NetConnection::MessageSignatureBytes, innerEncryptPos, &theCipher);
   }
   SymmetricCipher theCipher(theParams.mArrangedSecret);
   out.hashAndEncrypt(NetConnection::MessageSignatureBytes, encryptPos, &theCipher);

   conn->mConnectSendCount++;
   conn->mConnectLastSendTime = getCurrentTime();

   out.sendto(mSocket, conn->getNetAddress());
}