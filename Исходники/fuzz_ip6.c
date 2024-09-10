int main(int argc, char *argv[]) {
  unsigned char *pkt = NULL, *pkt_bak, *mcast6, *someaddr6 = NULL;
  unsigned char *dst6, *src6 = NULL, *mac = NULL, *routers[2], string[64] = "icmp6 and dst ";
  int rawmode = 0, test_start = 0, fragment = 0, alert = 0, sroute = 0;
  int do_type = DO_PING, do_alive = 1, hopbyhop = 0, destination = 0, jumbo = 0;
  int pkt_len = 0, offset = 0, test_current = 0, i, j, k, do_fuzz = 1, test_ptr = 0;
  int test_end = TEST_MAX, ping = NEVER, frag_offset = 0, header = 0, no_send = 1;
  int test_pos = 0, test_cnt = 0, do_it, extend = 0, mtu = 1500, size = 64, wait = 0;
  char *interface, fuzzbuf[256], *srcmac, *dns, *route6, *real_dst6 = NULL;
  unsigned char buf[256], buf2[100], buf3[16];
  unsigned short int *sip;
  pcap_t *p;
  thc_ipv6_hdr *hdr;

  if (argc < 3 || strncmp(argv[1], "-h", 2) == 0)
    help(argv[0]);

  while ((i = getopt(argc, argv, "123456789rxt:T:p:FSDHRIJan:")) >= 0) {
    switch (i) {
    case '1':
      do_type = DO_PING;
      break;
    case '2':
      do_type = DO_NEIGHSOL;
      break;
    case '3':
      do_type = DO_NEIGHADV;
      break;
    case '4':
      do_type = DO_RA;
      break;
    case '5':
      do_type = DO_MLD_REP;
      break;
    case '6':
      do_type = DO_MLD_DONE;
      break;
    case '7':
      do_type = DO_MLD_QUERY;
      wait = 0xff0000;
      break;
    case '8':
      do_type = DO_MLD2_REPORT;
      break;
    case '9':
      do_type = DO_MLD2_QUERY;
      wait = 0xff0000;
      break;
    case 'r':
      thc_ipv6_rawmode(1);
      rawmode = 1;
      test_pos -= 14;
      offset -= 14;
      break;
    case 't':
      test_start = atoi(optarg);
      break;
    case 'T':
      test_end = test_start = atoi(optarg);
      break;
    case 'p':
      ping = atoi(optarg);
      break;
    case 'a':
      do_alive = 0;
      break;
    case 'S':
      sroute = 1;
      break;
    case 'n':
      no_send = atoi(optarg);
      break;
    case 'F':
      fragment = 1;
      break;
    case 'R':
      alert = 1;
      break;
    case 'D':
      destination = 1;
      break;
    case 'H':
      hopbyhop = 1;
      break;
    case 'J':
      jumbo = 1;
      break;
    case 'I':
      header = 1;
      break;
    case 'x':
      extend = 1;
      break;
    }
  }
  if (argc - optind < 2) {
    fprintf(stderr, "ERROR: not enough options, interface and target address are required!\n");
    exit(-1);
  }
  interface = argv[optind];
  if (rawmode == 0 && (srcmac = thc_get_own_mac(interface)) == NULL) {
    fprintf(stderr, "ERROR: %s is not a valid interface which has a MAC, use raw mode?\n", interface);
    exit(-1);
  }
  if (no_send < 1) {
    fprintf(stderr, "ERROR: -n number must be between one and 2 billion\n");
    exit(-1);
  }
  if (do_type != DO_PING) {
    mcast6 = thc_resolve6(argv[optind + 1]);
    if (do_type == DO_NEIGHSOL) {
      dst6 = thc_resolve6("ff02::0001:ff00:0000");
      memcpy(dst6 + 13, mcast6 + 13, 3);
    } else
      dst6 = thc_resolve6("ff02::1");
  } else {
    dst6 = thc_resolve6(argv[optind + 1]);
  }
  if (argv[optind + 1] != NULL)
    real_dst6 = thc_resolve6(argv[optind + 1]);

  if (interface == NULL || argv[optind + 1] == NULL) {
    printf("Error: interface and target-ipv6-address are mandatory command line options\n");
    exit(-1);
  }
  if (ping < 1 || test_end < test_start) {
    printf("dont f**k up the command line options!\n");
    exit(-1);
  }
  if (argv[optind + 2] != NULL)
    someaddr6 = thc_resolve6(argv[optind + 2]);
  if (argc - optind > 3) {
    printf("Error: too many command line options\n");
    exit(-1);
  }
  if ((mac = thc_get_mac(interface, src6, dst6)) == NULL) {
    fprintf(stderr, "ERROR: Can not resolve mac address for %s\n", argv[2]);
    exit(-1);
  }
  if (rawmode)
    srcmac = mac;

  if (do_type == DO_PING)
    src6 = thc_get_own_ipv6(interface, dst6, PREFER_GLOBAL);
  else
    src6 = thc_get_own_ipv6(interface, dst6, PREFER_LINK);
  strcat(string, thc_ipv62notation(src6));
  if (sroute) {
    if (someaddr6 != NULL)
      routers[0] = someaddr6;
    else
      routers[0] = dst6;
    routers[1] = NULL;
  }
  setvbuf(stdout, NULL, _IONBF, 0);
  memset(buf, 0, sizeof(buf));
  memset(buf2, 0, sizeof(buf2));
  dns = thc_resolve6("FF02::FB");
  route6 = thc_resolve6("2a01::");

  if ((p = thc_pcap_init(interface, string)) == NULL) {
    fprintf(stderr, "Error: could not capture on interface %s with string %s\n", interface, string);
    exit(-1);
  }
  // ping before to check if it works
  if (do_alive)
    if (check_alive(p, interface, src6, real_dst6) == 0) {
      fprintf(stderr, "Error: target %s is not alive via direct ping6!\n", argv[optind + 1]);
      exit(-1);
    }
  // generate basic packet
  strcpy(fuzzbuf, fuzztype_ether);
  if ((pkt = thc_create_ipv6(interface, PREFER_GLOBAL, &pkt_len, src6, dst6, 0, 0, 0, 0, 0)) == NULL)
    return -1;
  if (header)
    strcat(fuzzbuf, fuzztype_ip6);
  else
    strcat(fuzzbuf, fuzztype_ip6no);

  if (alert || hopbyhop || jumbo) {
    memset(buf2, 0, sizeof(buf2));
    i = 0;

    if (alert) {
      buf2[i++] = 5;
      buf2[i++] = 2;
      i += 2;
      strcat(fuzzbuf, ".F.F");
    }

    if (jumbo) {
      buf2[i++] = 0xc2;
      buf2[i++] = 4;
      buf2[i++] = 'J';          // lookup code
      buf2[i++] = 'J';
      buf2[i++] = 'J';
      buf2[i++] = 'J';
      strcat(fuzzbuf, ".FBBBB");
    }

    if (hopbyhop) {
      memset(buf3, 0, sizeof(buf3));
      buf3[0] = 'X';
      buf3[1] = '.';
      for (j = 0; j < 10; j++) {
        buf2[i++] = 1;          // PadN, length
        buf2[i++] = j;
        if (j > 0) {
          memset(buf2 + i, 0xaa, j);
          buf3[2 + j] = '.';
          i += j;
        }
        strcat(fuzzbuf, buf3);  // always: X... for every new option
      }
    }

    if (thc_add_hdr_hopbyhop(pkt, &pkt_len, buf2, i) < 0)
      return -1;

    i += 2;
    if (i % 8 > 0)
      i = ((i / 8) + 1) * 8;

    offset += i;
  }

  if (sroute) {
    if (thc_add_hdr_route(pkt, &pkt_len, routers, 1) < 0)
      return -1;
    else {
      strcat(fuzzbuf, "FFFFBBBB................");
      offset += 24;
    }
  }

  if (fragment) {
    frag_offset = offset;
    if (thc_add_hdr_fragment(pkt, &pkt_len, 0, 0, 0) < 0)
      return -1;
    else {
      strcat(fuzzbuf, "FFWW..");
      offset += 8;
    }
  }

  if (destination) {
    memset(buf2, 0, sizeof(buf2));
    memset(buf3, 0, sizeof(buf3));
    buf3[0] = 'X';
    buf3[1] = '.';
    i = 0;
    for (j = 0; j < 10; j++) {
      buf2[i++] = 1;            // PadN, length
      buf2[i++] = j;
      if (j > 0) {
        memset(buf2 + i, 0xaa, j);
        buf3[2 + j] = '.';
        i += j;
      }
      strcat(fuzzbuf, buf3);    // always: X... for every new option
    }

    if (thc_add_hdr_dst(pkt, &pkt_len, buf2, i) < 0)
      return -1;

    i += 2;
    if (i % 8 > 0)
      i = ((i / 8) + 1) * 8;

    offset += i;
  }

  memset(buf, 0, sizeof(buf));
  if (header)
    strcat(fuzzbuf, fuzztype_icmp6);
  else
    strcat(fuzzbuf, fuzztype_icmp6no);
  switch (do_type) {
  case DO_PING:
    if (thc_add_icmp6(pkt, &pkt_len, ICMP6_PINGREQUEST, 0, test_current, (unsigned char *) &buf, 16, 0) < 0)
      return -1;
    strcat(fuzzbuf, fuzztype_icmp6ping);
    break;

  case DO_NEIGHSOL:
    if (someaddr6 != NULL)
      memcpy(buf, someaddr6, 16);
    else
      memcpy(buf, mcast6, 16);
    buf[16] = 1;
    buf[17] = 1;
    memcpy(buf + 18, srcmac, 6);
    if (thc_add_icmp6(pkt, &pkt_len, ICMP6_NEIGHBORSOL, 0, 0, (unsigned char *) &buf, 24, 0) < 0)
      return -1;
    strcat(fuzzbuf, fuzztype_icmp6ns);
    break;

  case DO_NEIGHADV:
    if (someaddr6 != NULL)
      memcpy(buf, someaddr6, 16);
    else
      memcpy(buf, src6, 16);
    buf[16] = 2;
    buf[17] = 1;
    memcpy(buf + 18, srcmac, 6);
    if (thc_add_icmp6(pkt, &pkt_len, ICMP6_NEIGHBORADV, 0, 0xe0000000, (unsigned char *) &buf, 24, 0) < 0)
      return -1;
    strcat(fuzzbuf, fuzztype_icmp6na);
    break;

  case DO_RA:
    //  buf[3] = 250; // 0-3: reachable timer
    buf[6] = 4;                 // 4-7: retrans timer
    // option mtu
    buf[8] = 5;
    buf[9] = 1;
    buf[12] = mtu / 16777216;

    buf[14] = (mtu % 65536) / 256;
    buf[15] = mtu % 256;
    // option prefix
    buf[16] = 3;
    buf[17] = 4;
    buf[18] = size;             // prefix length
    buf[19] = 128 + 64;
    memset(&buf[20], 17, 4);
    memset(&buf[24], 4, 4);
    if (someaddr6 != NULL)
      memcpy(&buf[32], someaddr6, 16);
    else
      memcpy(&buf[32], route6, 16);

    i = 48;
    // mac address option
    buf[i++] = 1;
    buf[i++] = 1;
    memcpy(buf + i, srcmac, 6);
    i += 6;

    // default route routing option
    buf[i++] = 0x18;            // routing entry option type
    buf[i++] = 0x03;            // length 3 == 24 bytes
    buf[i++] = 0x00;            // prefix length
    buf[i++] = 0x08;            // priority, highest of course
    i += 2;                     // 52-53 unknown
    buf[i++] = 0x11;            // lifetime, word
    buf[i++] = 0x11;            // lifetime, word
    i += 16;                    // 56-71 address, all zeros for default

    // dns option
    buf[i++] = 0x19;            // dns option type
    buf[i++] = 0x03;            // length
    i += 2;                     // 74-75 reserved
    memset(buf + i, 1, 4);      // validity time
    i += 4;
    if (someaddr6 != NULL)
      memcpy(buf + i, someaddr6, 16);   // dns server
    else
      memcpy(buf + i, dns, 16); // dns server
    i += 16;

    if (thc_add_icmp6(pkt, &pkt_len, ICMP6_ROUTERADV, 0, 0xff080800, buf, i, 0) < 0)
      return -1;
    strcat(fuzzbuf, fuzztype_icmp6ra);
    break;

  case DO_MLD_QUERY:
  case DO_MLD_DONE:
  case DO_MLD_REP:
    buf[0] = 0xff;
    buf[1] = 0x02;
    buf[15] = 0x05;
    if (someaddr6 != NULL)
      memcpy(buf, someaddr6, 16);
    if (thc_add_icmp6(pkt, &pkt_len, do_type, 0, wait, buf, 16, 0) < 0)
      return -1;
    strcat(fuzzbuf, fuzztype_icmp6mld);
    break;
  case DO_MLD2_QUERY:
    buf[0] = 0xff;
    buf[1] = 0x02;
    buf[15] = 0x05;
    if (someaddr6 != NULL)
      memcpy(buf, someaddr6, 16);
    buf[16] = 7;
    buf[17] = 120;
    buf[19] = 3;
    memcpy(buf + 20, dst6, 16);
    memcpy(buf + 36, buf, 16);
    if (thc_add_icmp6(pkt, &pkt_len, DO_MLD_QUERY, 0, wait, buf, 68, 0) < 0)
      return -1;
    strcat(fuzzbuf, fuzztype_icmp6mld2que);
    break;
  case DO_MLD2_REPORT:
    for (i = 0; i < 3; i++) {
      buf[0 + 68 * i] = 1 + i * 2 - i / 2;      //include new++, generates 1, 3 and 4
      buf[3 + 68 * i] = 3;      //3 sources
      buf[4 + 68 * i] = 0xff;
      buf[5 + 68 * i] = 0x02;
      buf[18 + 68 * i] = 0x82 + i % 256;
      buf[19 + 68 * i] = 0xff;
      memcpy(buf + 20 + 68 * i, src6, 16);
      buf[36 + 68 * i] = 0xfe;
      buf[37 + 68 * i] = 0x80;
      buf[46 + 68 * i] = 0xf0;
      if (someaddr6 != NULL)
        memcpy(buf + 52 + 68 * i, someaddr6, 16);
    }

    if (thc_add_icmp6(pkt, &pkt_len, do_type, 0, 3, buf, 208, 0) < 0)
      return -1;
    strcat(fuzzbuf, fuzztype_icmp6mld2rep);
    break;

  default:
    fprintf(stderr, "ERROR: Mode not implemented yet!\n");
    exit(-1);
  }

  if (thc_generate_pkt(interface, srcmac, mac, pkt, &pkt_len) < 0)
    return -1;
  hdr = (thc_ipv6_hdr *) pkt;

  if (jumbo) {
    i = 0;
    j = 1;
    while (i < hdr->pkt_len + 4 && j) {
      if (hdr->pkt[i] == 'J')
        if (memcmp(&hdr->pkt[i], "JJJJ", 4) == 0)
          j = 0;
      i++;
    }
    if (j) {
      fprintf(stderr, "ERROR: fuckup, cant find my own marker?!\n");
      exit(-1);
    } else
      i--;
    hdr->pkt[i] = 0;
    hdr->pkt[i + 1] = 0;
    hdr->pkt[i + 2] = hdr->pkt[4 + 14 - 14 * rawmode];
    hdr->pkt[i + 3] = hdr->pkt[5 + 14 - 14 * rawmode];
    hdr->pkt[4 + 14 - 14 * rawmode] = 0;
    hdr->pkt[5 + 14 - 14 * rawmode] = 0;
  }

  if (extend)
    for (i = 0; i < strlen(fuzzbuf); i++)
      if (fuzzbuf[i] == 'B' || fuzzbuf[i] == 'F')
        fuzzbuf[i] = 'X';

  // backup of generated packet
  pkt_bak = malloc(hdr->pkt_len);
  memcpy(pkt_bak, hdr->pkt, hdr->pkt_len);

  printf("Fuzzing packet, starting at fuzz case %d, ending at fuzz case %d, every packet sent denoted by a dot:\n", test_start, test_end);
//printf("buf(%d): %s\n", strlen(fuzzbuf), fuzzbuf);
  while (do_fuzz) {
    if (test_cnt == 0)
      while (fuzzbuf[test_ptr] == '.') {
        test_ptr++;
        test_pos++;
      }

    if (fuzzbuf[test_ptr] == 0)
      do_fuzz = 0;

    test_cnt++;
    do_it = 1;

//printf("[%s] pos[%d]=%c -> %d | pkt[%d] | %d (%d=>%d)| ", /*fuzzbuf*/"", test_ptr, fuzzbuf[test_ptr], test_cnt, test_pos, test_current, test_start, test_end);

    switch (fuzzbuf[test_ptr]) {
    case 0:
      break;
    case 'X':
      if (test_cnt <= COUNT_EXTEND) {
        if (pkt_bak[test_pos] != extends[test_cnt - 1])
          hdr->pkt[test_pos] = extends[test_cnt - 1];
        else
          do_it = 0;
      } else {
        test_cnt = 0;
        test_ptr++;
        test_pos++;
      }
      break;
    case 'B':
      if (test_cnt <= COUNT_BYTE) {
        if (pkt_bak[test_pos] != bytes[test_cnt - 1])
          hdr->pkt[test_pos] = bytes[test_cnt - 1];
        else
          do_it = 0;
      } else {
        i = 0;
        while (i < COUNT_BYTE && do_it) {
          if (bytes[i] == pkt_bak[test_pos])
            do_it = 0;
          i++;
        }
        if (do_it)
          hdr->pkt[test_pos] = hdr->pkt[test_pos] ^ xors[test_cnt - COUNT_BYTE - 1];
      }
      if (test_cnt == COUNT_BYTE + COUNT_XOR) {
        test_cnt = 0;
        test_ptr++;
        test_pos++;
      }
      break;
    case 'F':
      if (test_cnt <= COUNT_FLAG) {
        if (pkt_bak[test_pos] != flags[test_cnt - 1])
          hdr->pkt[test_pos] = flags[test_cnt - 1];
        else
          do_it = 0;
      } else {
        i = 0;
        while (i < COUNT_FLAG && do_it) {
          if (bytes[i] == pkt_bak[test_pos])    // yes, bytes[] is the right one even for flags
            do_it = 0;
          i++;
        }
        if (do_it)
          hdr->pkt[test_pos] = hdr->pkt[test_pos] ^ xors[test_cnt - COUNT_BYTE - 1];
      }
      if (test_cnt == COUNT_FLAG + COUNT_XOR) {
        test_cnt = 0;
        test_ptr++;
        test_pos++;
      }
      break;
    case 'W':
      sip = (unsigned short int *) &pkt_bak[test_pos];
      if (test_cnt <= COUNT_WORD) {
        if (*sip != words[test_cnt - 1])
          memcpy((char *) &hdr->pkt[test_pos], (char *) &words[test_cnt - 1], 2);
        else
          do_it = 0;
      } else {
        i = 0;
        while (i < COUNT_WORD && do_it) {
          if (words[i] == *sip)
            do_it = 0;
          i++;
        }
        if (do_it) {
          i = *sip ^ xors[test_cnt - COUNT_WORD - 1];
          sip = (unsigned short int *) &hdr->pkt[test_pos];
          *sip = i % 65536;
        }
      }
      if (test_cnt == COUNT_WORD + COUNT_XOR) {
        test_cnt = 0;
        test_ptr++;
        test_pos += 2;
      }
      break;
    default:
      fprintf(stderr, "This character should not be in the fuzz string, shoot the programmer: %c(%d) position %d string %s\n", fuzzbuf[test_ptr], fuzzbuf[test_ptr], test_ptr,
              fuzzbuf);
      exit(-1);
      break;
    }

    if (do_it && do_fuzz) {
      if (test_current >= test_start && test_current <= test_end && do_fuzz) {
        // fill icmp id+seq and unique buffer with test case number
        if (fragment)
          memcpy(hdr->pkt + frag_offset + 58, (char *) &test_current, 4);
        switch (do_type) {
        case DO_PING:
          for (i = 0; i < 4 + 1; i++)
            memcpy(hdr->pkt + offset + 58 + i * 4, (char *) &test_current, 4);
          break;
        case DO_NEIGHSOL:
        case DO_NEIGHADV:
          break;                // do nothing for these
        case DO_RA:
          memcpy(hdr->pkt + offset + 0x62, (char *) &test_current, 4);  // prefix update
          memcpy(hdr->pkt + offset + 0x7e, hdr->pkt + offset + 0x5e, 16);       // routing update
          if (rawmode == 0)
            memcpy(hdr->pkt + 8, (char *) &test_current, 4);    // srcmac update
          memcpy(hdr->pkt + offset + 0x72, (char *) &test_current, 4);  // srcmac update
          memcpy(hdr->pkt + 0x10 + 14 - 14 * rawmode, (char *) &test_current, 4);       // srcip update
          memcpy(hdr->original_src, hdr->pkt + 8 + 14 - 14 * rawmode, 16);      // srcip update for checksum
          break;
        case DO_MLD_QUERY:
        case DO_MLD_DONE:
        case DO_MLD_REP:
        case DO_MLD2_QUERY:
          memcpy(hdr->pkt + offset + 0x4a, (char *) &test_current, 4);
          break;
        case DO_MLD2_REPORT:   //??? XXX TODO CHECK
          memcpy(hdr->pkt + offset + 0x4d, (char *) &test_current, 4);
          memcpy(hdr->pkt + offset + 0x4d + 68, (char *) &test_current, 4);
          memcpy(hdr->pkt + offset + 0x4d + 136, (char *) &test_current, 4);
          break;
        default:
          fprintf(stderr, "ERROR!!!\n");
          exit(-1);
        }

        // regenerate checksum
        if (do_type == do_type) {       // maybe for later non-icmp stuff
          hdr->pkt[offset + 56] = 0;
          hdr->pkt[offset + 57] = 0;
          i = checksum_pseudo_header(hdr->original_src, hdr->final_dst, NXT_ICMP6, &hdr->pkt[offset + 54], hdr->pkt_len - offset - 54);
          hdr->pkt[offset + 56] = i / 256;
          hdr->pkt[offset + 57] = i % 256;
        }
        // send packet
        for (k = 0; k < no_send; k++) {
          if (thc_send_pkt(interface, pkt, &pkt_len) < 0)
            return -1;
          usleep(1);
        }
        printf(".");
        usleep(250);
        // if ping, check ping again
        if ((test_current - test_start) % ping == 0 && test_current != 0 && test_start != test_current)
          if (check_alive(p, interface, src6, real_dst6) == 0) {
            i = ((((test_current - test_start) / ping) - 1) * ping) + test_start + 1;
            printf("\nResult: target %s crashed during fuzzing, offending test case no. could be %d to %d\n", argv[optind + 1], i < 0 ? 0 : i, test_current);
            exit(-1);
          }
      }
//else printf("NOT SENT - NOT IN TEST LIST\n");
      // reset to basic packet
      memcpy(hdr->pkt, pkt_bak, hdr->pkt_len);
      test_current++;
    }
//else printf("NOT SENT!\n");
  }

  printf("\n");
  // ping afterwards to check if it worked
  if (do_alive) {
    if (check_alive(p, interface, src6, real_dst6) == 0)
      printf("Result: target %s is NOT alive via direct ping6 - good work! (position: %d)\n", argv[optind + 1], test_pos);
    else
      printf("Result: target %s is still alive via direct ping6, better luck next time.\n", argv[optind + 1]);
  }

  thc_pcap_close(p);
  return 0;
}