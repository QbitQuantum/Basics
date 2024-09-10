XPCGetProtocol::XPCGetProtocol(int _iProtocol)
{
#ifdef UNIX
        cIteratorFlag = 0;
#endif
        // Retrieves the protocol structure by number
        protocolPtr = getprotobynumber(_iProtocol);
        if (protocolPtr == NULL)
        {
              XPCException exceptObject("Could Not Get Protocol By Number");
              throw exceptObject;
              return;
        }
}