int makeconnect (char *mycall, char *conncall)
//**************************************************************************
//
//
//**************************************************************************
{
  lastfunc("makeconnect");
  unsigned int port;
  //unsigned int port_org;

  if (l2vorhanden)
  {
    strupr(conncall);
    strupr(mycall);
#ifdef _AX25K
#ifndef _AX25K_ONLY
    CRegEx reg;
    if (ax25k_isdefault() || reg.regex_match("ax.*:", conncall))
#endif
      return ax25k_connect(mycall, conncall);
#endif
#ifndef _AX25K_ONLY
    if (t->port)
    {
      trace(serious, "makeconn", "port busy");
      return NO;
    }
    for (port = 2; port < (unsigned) highestport; port++)
    {
  //    port_org = port;
  //    port = random_max(highestport-port_org)+port_org-1;
      if (portopen[port] == p_closed)
      {
        portopen[port] = p_linksetup;
        rxdafl[port] = rxcbuf[port] = 0;
        connport_tnc(port, mycall, conncall);
        while (portopen[port] == p_linksetup)
        {
          switch (linkstate_tnc(port))
          {
          case info_transfer:
          case rej_sent:
          case wait_ack:
            t->port = port;
            portopen[port] = p_connected;
            trace(report, "makeconn", "ok %s", conncall);
            break;
          case disconnected:
            portopen[port] = p_closed;
            trace(report, "makeconn", "fail %s", conncall);
            break;
          default:
            {
              wdelay(245);
              if (testabbruch())
              {
                portopen[port] = p_closed;
                discport_tnc(port);
                return NO;
              }
            }
          }
        }
        return (portopen[port] == p_connected);
      }
  //    port = port_org;
    }
    trace(report, "makeconn", "no port");
    return NO;
#endif
  }
  else
    return NO;
}