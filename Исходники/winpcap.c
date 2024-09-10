/**
 * Initialise WinPcap and return our MAC address.
 */
int pkt_eth_init (mac_address *mac_addr)
{
  struct {
    PACKET_OID_DATA oidData;
    char            descr[512];
  } oid;
  const ADAPTER *adapter = NULL;
  DWORD thread_id;
  BOOL  is_up;

  if (_watt_is_win9x)  /**< \todo Support Win-9x too */
  {
    (*_printf) (_LANG("Win-NT or later reqired.\n"));
    _pkt_errno = PDERR_GEN_FAIL;
    return (WERR_ILL_DOSX);
  }

  if (!_watt_no_config || _watt_user_config_fn)
     parse_config_pass_1();

  _pkt_inf = calloc (sizeof(*_pkt_inf), 1);
  if (!_pkt_inf)
  {
    (*_printf) (_LANG("Failed to allocate WinPcap DRIVER data.\n"));
    _pkt_errno = PDERR_GEN_FAIL;
    return (WERR_NO_MEM);
  }

  if (debug_on >= 2 && dump_fname[0])
     dump_file = fopen_excl (ExpandVarStr(dump_fname), "w+t");

  if (!PacketInitModule(TRUE, dump_file))
  {
    (*_printf) (_LANG("Failed to initialise WinPcap.\n"));
    pkt_release();
    _pkt_errno = PDERR_NO_DRIVER;
    return (WERR_PKT_ERROR);
  }

  if (!_pktdrvrname[0] &&
      !find_adapter(_pktdrvrname,sizeof(_pktdrvrname)))
  {
    (*_printf) (_LANG("No WinPcap driver found.\n"));
    _pkt_errno = PDERR_NO_DRIVER;
    return (WERR_NO_DRIVER);
  }

  TCP_CONSOLE_MSG (2, ("device %s\n", _pktdrvrname));

  adapter = PacketOpenAdapter (_pktdrvrname);
  if (!adapter)
  {
    if (debug_on > 0)
       (*_printf) (_LANG("PacketOpenAdapter (\"%s\") failed; %s\n"),
                   _pktdrvrname, win_strerror(GetLastError()));
    pkt_release();
    return (WERR_NO_DRIVER);
  }

  _pkt_inf->adapter = adapter;
#if defined(USE_DYN_PACKET)
  _pkt_inf->adapter_info = NULL;
#else
  _pkt_inf->adapter_info = PacketFindAdInfo (_pktdrvrname);
#endif

  /* Query the NIC driver for the adapter description
   */
  memset (&oid, 0, sizeof(oid));
  oid.oidData.Oid    = OID_GEN_VENDOR_DESCRIPTION;
  oid.oidData.Length = sizeof(oid.descr);

  if (PacketRequest (adapter, FALSE, &oid.oidData))
     StrLcpy (_pktdrvr_descr, (char*)oid.oidData.Data, sizeof(_pktdrvr_descr));
  else
  {
    (*_printf) (_LANG("PacketRequest() failed; %s\n"),
                win_strerror(GetLastError()));
    pkt_release();
    return (WERR_PKT_ERROR);
  }

  if (!get_interface_type(&_pktdevclass))
  {
    pkt_release();
    return (WERR_PKT_ERROR);
  }

  if (get_connected_status(&is_up) && !is_up)
     (*_printf) (_LANG("Warning: the adapter %s is down\n"), _pktdrvrname);

  switch (_pktdevclass)
  {
    case PDCLASS_TOKEN:
         _pkt_ip_ofs = sizeof(tok_Header);
         break;
    case PDCLASS_ETHER:
         _pkt_ip_ofs = sizeof(eth_Header);
         break;
    case PDCLASS_FDDI:
         _pkt_ip_ofs = sizeof(fddi_Header);
         break;
    case PDCLASS_ARCNET:
         _pkt_ip_ofs = ARC_HDRLEN;
         break;
    default:
         pkt_release();
         (*_printf) (_LANG("WinPcap-ERROR: Unsupported driver class %dh\n"),
                     _pktdevclass);
         _pkt_errno = PDERR_NO_CLASS;
         return (WERR_PKT_ERROR);
  }

  if (!pkt_get_addr(mac_addr))  /* get our MAC address */
  {
    pkt_release();
    return (WERR_PKT_ERROR);
  }

  pktq_init (&_pkt_inf->pkt_queue,
             sizeof(_pkt_inf->rx_buf[0]),   /* RX_SIZE */
             DIM(_pkt_inf->rx_buf),         /* RX_BUFS */
             (char*)&_pkt_inf->rx_buf);

  _pkt_inf->npf_buf_size = RX_SIZE * pkt_num_rx_bufs;
  _pkt_inf->npf_buf = malloc (_pkt_inf->npf_buf_size);
  if (!_pkt_inf->npf_buf)
  {
    (*_printf) (_LANG("Failed to allocate %d byte Rx buffer.\n"),
                _pkt_inf->npf_buf_size);
    pkt_release();
    _pkt_errno = PDERR_GEN_FAIL;
    return (WERR_NO_MEM);
  }

  PacketSetMode (adapter, PACKET_MODE_CAPT);
  PacketSetBuff (adapter, _pkt_inf->npf_buf_size);
  PacketSetMinToCopy (adapter, ETH_MIN);

  /* PacketReceivePacket() blocks until something is received
   */
  PacketSetReadTimeout ((ADAPTER*)adapter, 0);

  /* Set Rx-mode forced via config.
   */
  if (_pkt_forced_rxmode != -1)
  {
    _pkt_forced_rxmode &= 0xFFFF;     /* clear bits not set via ARG_ATOX_W */
    if (_pkt_forced_rxmode == 0 ||    /* check illegal bit-values */
        (_pkt_forced_rxmode & 0x10) ||
        (_pkt_forced_rxmode & 0x40) ||
        (_pkt_forced_rxmode > 0x80))
     {
       TCP_CONSOLE_MSG (0, ("Illegal Rx-mode (0x%02X) specified\n",
                        _pkt_forced_rxmode));
       _pkt_forced_rxmode = -1;
     }
  }

  if (pkt_get_rcv_mode())
     _pkt_rxmode0 = _pkt_rxmode;

  if (_pkt_forced_rxmode != -1)
       pkt_set_rcv_mode (_pkt_forced_rxmode);
  else pkt_set_rcv_mode (RXMODE_DEFAULT);

#if 1
  _pkt_inf->recv_thread = CreateThread (NULL, 2048, pkt_recv_thread,
                                        NULL, 0, &thread_id);
#else
  _pkt_inf->recv_thread = _beginthreadex (NULL, 2048, pkt_recv_thread,
                                          NULL, 0, &thread_id);
#endif

  if (!_pkt_inf->recv_thread)
  {
    (*_printf) (_LANG("Failed to create receiver thread; %s\n"),
                win_strerror(GetLastError()));
    pkt_release();
    _pkt_errno = PDERR_GEN_FAIL;
    return (WERR_PKT_ERROR);
  }

  if (thr_realtime)
     SetThreadPriority (_pkt_inf->recv_thread,
                        THREAD_PRIORITY_TIME_CRITICAL);

  TCP_CONSOLE_MSG (2, ("capture thread-id %lu\n", thread_id));

#if defined(USE_DEBUG)
  if (debug_on >= 2)
  {
    (*_printf) ("link-details:\n");
    show_link_details();
  }
#endif
  return (0);
}