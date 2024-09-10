int CpduPlayerLoggedOut::sendPlayerLoggedOut(SOCKET sd,
                                             const char* username)
{
  pdu_playerloggedin pdu;
  memset(&pdu, 0, sizeof(pdu));
  
  strncpy(pdu.username, username, PDU_STRINGSIZE);  
  memcpy(value_ + PDU_HEADERSIZE, &pdu, sizeof(pdu));
  
  return sendTo(sd);
}