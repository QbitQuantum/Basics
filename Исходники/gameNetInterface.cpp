static void handlePing(Game *game, const Address &remoteAddress, Socket &socket, BitStream *stream, S32 clientId)
{
   TNLAssert(game->isServer(), "Expected this to be a server!");

   Nonce clientNonce;
   clientNonce.read(stream);

   U32 protocolVersion;
   stream->read(&protocolVersion);

   if(protocolVersion != CS_PROTOCOL_VERSION)   // Ignore pings from incompatible versions
      return;

   U32 clientIdentityToken = computeSimpleToken(clientNonce);
   PacketStream pingResponse;

   pingResponse.write(U8(GameNetInterface::PingResponse));
   clientNonce.write(&pingResponse);
   pingResponse.write(clientIdentityToken);

   pingResponse.write(clientId);  // older 019 ignore this or won't read this

   pingResponse.sendto(socket, remoteAddress);
}