/*
 * Class:     com_gemstone_gemfire_internal_SmHelper
 * Method:    _getSystemId
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_gemstone_gemfire_internal_SmHelper__1getSystemId
  (JNIEnv *env, jclass klass)
{
  unsigned char macAddr[6];
  const char* id;
  char idbuff[256];
#ifdef FLG_UNIX
#if defined(FLG_SOLARIS_UNIX)
  char provider[64];
  char serial[64];
#if 0
  const char* pNIC = "hme0";      // ethernet card device name
  // get mac-address
  memset(macAddr, 0, sizeof(macAddr));
  int fdesc = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
  if (fdesc != -1) {
    struct ifreq req;
    strcpy(req.ifr_name, pNIC);
    int err = ioctl(fdesc, SIOCGIFADDR, &req );
    if (err != -1) {
      memcpy(macAddr, req.ifr_addr.sa_data, sizeof(macAddr));
    }
    close(fdesc);
  }
#endif
  char name[MAXHOSTNAMELEN];

  memset(macAddr, 0, sizeof(macAddr));
  if (gethostname(name, sizeof(name)) == 0) {
    struct hostent *phost;
    struct hostent hostentBuf;
    char hbuf[512];
    int herr;
    phost = gethostbyname_r(name, &hostentBuf, hbuf, sizeof(hbuf), &herr);
    if (phost != 0) {
      int s;
      s = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
      if (s != -1) {
        char **paddrs;
        struct arpreq        ar;
        struct sockaddr_in * psa;
        paddrs = phost->h_addr_list;
        psa    = ( struct sockaddr_in * )&( ar.arp_pa );
        memset( &ar, 0, sizeof( struct arpreq ) );
        psa->sin_family = AF_INET;
        memcpy( &( psa->sin_addr ), *paddrs, sizeof( struct in_addr ) );
        if ( ioctl( s, SIOCGARP, &ar ) != -1 ) {
          int i;
          for (i = 0; i < 6; i++) {
            macAddr[i] = ar.arp_ha.sa_data[i];
          }
        }
        close(s);
      }
    }
  }

  sysinfo(SI_HW_PROVIDER, provider, 64);
  sysinfo(SI_HW_SERIAL, serial, 64);

  sprintf(idbuff, "%lx %s-%s %02x-%02x-%02x-%02x-%02x-%02x",
          gethostid(), provider, serial,
          macAddr[0], macAddr[1], macAddr[2],
          macAddr[3], macAddr[4], macAddr[5]);
#elif defined(FLG_OSX_UNIX)
  const char* pNIC = "en0";
  // get mac-address
  memset(macAddr, 0, sizeof(macAddr));
  size_t len;
  char *buf;
  struct if_msghdr        *ifm;
  struct sockaddr_dl      *sdl;

  int mib[6] = {CTL_NET, AF_ROUTE, 0, AF_LINK, NET_RT_IFLIST, 0};
  mib[5] = if_nametoindex(pNIC);
  UTL_ASSERT(mib[5] != 0);
  sysctl(mib, 6, NULL, &len, NULL, 0);
  buf = (char*)UtlMalloc(len, "OBTAIN MAC ADDRESS");
  sysctl(mib, 6, buf, &len, NULL, 0);
#ifdef X86_64
//The following code will have issues on 64bit Mac OS X
+++ error
#endif
  ifm = (struct if_msghdr *)buf;
  sdl = (struct sockaddr_dl *)(ifm + 1);
  memcpy(macAddr, (unsigned char *)LLADDR(sdl), sizeof(macAddr));
  sprintf(idbuff, "%02x-%02x-%02x-%02x-%02x-%02x",
          macAddr[0], macAddr[1], macAddr[2],
          macAddr[3], macAddr[4], macAddr[5]);
#else
  const char* pNIC = "eth0";
  // get mac-address
  memset(macAddr, 0, sizeof(macAddr));
  int fdesc = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
  if (fdesc != -1) {
    struct ifreq req;
    strcpy(req.ifr_name, pNIC);
    int err = ioctl(fdesc, SIOCGIFHWADDR, &req );
    if (err != -1) {
      int i;
      struct sockaddr* sa = (struct sockaddr *) &req.ifr_addr;
      for (i = 0; i < 6; i++) {
        macAddr[i] = sa->sa_data[i];
      }
    }
    close(fdesc);
  }
  sprintf(idbuff, "%02x-%02x-%02x-%02x-%02x-%02x",
          macAddr[0], macAddr[1], macAddr[2],
          macAddr[3], macAddr[4], macAddr[5]);
#endif
#else /* windows */
  DWORD serialNumber = 0;
  DWORD maxDirLength;
  DWORD flags;
  if (GetVolumeInformation("c:\\", NULL, 0, &serialNumber, &maxDirLength,
                           &flags, NULL, 0)) {
  }
  {
    int lana_num = -1;		/* LAN adapter number */

    struct ASTAT {
      ADAPTER_STATUS adapt;
      NAME_BUFFER NameBuff[30];
    } Adapter;
    NCB Ncb;

    {
      LANA_ENUM lenum;
      UCHAR uRetCode;
      int li = 0;

      memset(&Ncb,0,sizeof(Ncb));
      Ncb.ncb_command = NCBENUM;
      Ncb.ncb_buffer = (UCHAR*)&lenum;
      Ncb.ncb_length = sizeof(lenum);
      uRetCode = Netbios(&Ncb);
      if (uRetCode != 0) return JNI_FALSE;

      for (; li < lenum.length; li++) {
        lana_num = lenum.lana[li];
        /* prepare to get adapter status block */
        memset(&Ncb, 0, sizeof(Ncb));
        Ncb.ncb_command = NCBRESET;
        Ncb.ncb_lana_num = lana_num;
        if (Netbios(&Ncb) != NRC_GOODRET) continue;

        /* OK, lets go fetch ethernet address */
        memset(&Ncb, 0, sizeof(Ncb));
        Ncb.ncb_command = NCBASTAT;
        Ncb.ncb_lana_num = lana_num;
        strcpy((char *) Ncb.ncb_callname, "*");

        memset(&Adapter, 0, sizeof(Adapter));
        Ncb.ncb_buffer = (unsigned char *)&Adapter;
        Ncb.ncb_length = sizeof(Adapter);
        /* if unable to determine, exit false */
        if (Netbios(&Ncb) != 0) continue;

        /* if correct type, then see if its
           the one we want to check */
        if ((Adapter.adapt.adapter_type & 0xff) == 0xfe) {
          int i;
          for (i = 0; i < 6; i++) {
            macAddr[i] = Adapter.adapt.adapter_address[i];
          }
          break;
        }
      }
    }
  }
  sprintf(idbuff, "%lx %02x-%02x-%02x-%02x-%02x-%02x",
          serialNumber,
          macAddr[0], macAddr[1], macAddr[2],
          macAddr[3], macAddr[4], macAddr[5]);
#endif
  id = idbuff;
  return (*env)->NewStringUTF(env, id);
}