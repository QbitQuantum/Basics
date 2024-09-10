/**
  Convert the IKE Header from Network order to Host order.

  @param[in, out]  Header    The pointer of the IKE_HEADER.

**/
VOID
IkeHdrNetToHost (
  IN OUT IKE_HEADER *Header
  )
{
  Header->InitiatorCookie = NTOHLL (Header->InitiatorCookie);
  Header->ResponderCookie = NTOHLL (Header->ResponderCookie);
  Header->MessageId       = NTOHL (Header->MessageId);
  Header->Length          = NTOHL (Header->Length);
}