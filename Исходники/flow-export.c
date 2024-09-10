/*
 * function: format0
 *
 * export flows in cflowd format
*/
int format0(struct ftio *ftio, struct options *opt)
{
  struct fts3rec_offsets fo;
  struct ftver ftv;
  struct fttime ftt;
  char *rec;
  uint32_t ui32, index, sysUpTime, unix_secs, unix_nsecs, First, Last;
  uint16_t ui16;
  uint8_t ui8;

  ftio_get_ver(ftio, &ftv);

  fts3rec_compute_offsets(&fo, &ftv);

  switch (ftv.d_version) {

    case 1:
      opt->cflowd_mask &= CF_INDEX_V1_MASK;
      break;

    case 5:
      opt->cflowd_mask &= CF_INDEX_V5_MASK;
      break;

    case 6:
      opt->cflowd_mask &= CF_INDEX_V6_MASK;
      break;

    case 7:
      opt->cflowd_mask &= CF_INDEX_V7_MASK;
      break;

    case 1005:
      opt->cflowd_mask &= CF_INDEX_V5_MASK;
      break;

    case 8:

      switch (ftv.agg_method) {

        case 1:
          opt->cflowd_mask &= CF_INDEX_V8_1_MASK;
          break;

        case 2:
          opt->cflowd_mask &= CF_INDEX_V8_2_MASK;
          break;

        case 3:
          opt->cflowd_mask &= CF_INDEX_V8_3_MASK;
          break;

        case 4:
          opt->cflowd_mask &= CF_INDEX_V8_4_MASK;
          break;

        case 5:
          opt->cflowd_mask &= CF_INDEX_V8_5_MASK;
          break;

        case 6:
          opt->cflowd_mask &= CF_INDEX_V8_6_MASK;
          break;

        case 7:
          opt->cflowd_mask &= CF_INDEX_V8_7_MASK;
          break;

        case 8:
          opt->cflowd_mask &= CF_INDEX_V8_8_MASK;
          break;

        case 9:
          opt->cflowd_mask &= CF_INDEX_V8_9_MASK;
          break;

        case 10:
          opt->cflowd_mask &= CF_INDEX_V8_10_MASK;
          break;

        case 11:
          opt->cflowd_mask &= CF_INDEX_V8_11_MASK;
          break;

        case 12:
          opt->cflowd_mask &= CF_INDEX_V8_12_MASK;
          break;

        case 13:
          opt->cflowd_mask &= CF_INDEX_V8_13_MASK;
          break;

        case 14:
          opt->cflowd_mask &= CF_INDEX_V8_14_MASK;
          break;

        default:
          fterr_warnx("Unsupported export version");
          return -1;

       } /* switch */
       break;

    default:
      fterr_warnx("Unsupported export version");
      return -1;


  } /* switch */

  /* index */
  index = opt->cflowd_mask;
  index = htonl(index);

  while ((rec = ftio_read(ftio))) {

    fwrite(&index, sizeof (index), 1, stdout);

    if (opt->cflowd_mask & CF_ROUTERMASK) {
       ui32 = *((uint32_t*)(rec+fo.exaddr));
       ui32 = htonl(ui32);
       fwrite(&ui32, sizeof (ui32), 1, stdout);
    }

    if (opt->cflowd_mask & CF_SRCIPADDRMASK) {
       ui32 = *((uint32_t*)(rec+fo.srcaddr));
       ui32 = htonl(ui32);
       fwrite(&ui32, sizeof (ui32), 1, stdout);
    }

    if (opt->cflowd_mask & CF_DSTIPADDRMASK) {
       ui32 = *((uint32_t*)(rec+fo.dstaddr));
       ui32 = htonl(ui32);
       fwrite(&ui32, sizeof (ui32), 1, stdout);
    }

    if (opt->cflowd_mask & CF_INPUTIFINDEXMASK) {
       ui16 = *((uint16_t*)(rec+fo.input));
       ui16 = htons(ui16);
       fwrite(&ui16, sizeof (ui16), 1, stdout);
    }

    if (opt->cflowd_mask & CF_OUTPUTIFINDEXMASK) {
       ui16 = *((uint16_t*)(rec+fo.output));
       ui16 = htons(ui16);
       fwrite(&ui16, sizeof (ui16), 1, stdout);
    }

    if (opt->cflowd_mask & CF_SRCPORTMASK) {
       ui16 = *((uint16_t*)(rec+fo.srcport));
       ui16 = htons(ui16);
       fwrite(&ui16, sizeof (ui16), 1, stdout);
    }

    if (opt->cflowd_mask & CF_DSTPORTMASK) {
       ui16 = *((uint16_t*)(rec+fo.dstport));
       ui16 = htons(ui16);
       fwrite(&ui16, sizeof (ui16), 1, stdout);
    }

    if (opt->cflowd_mask & CF_PKTSMASK) {
       ui32 = *((uint32_t*)(rec+fo.dPkts));
       ui32 = htonl(ui32);
       fwrite(&ui32, sizeof (ui32), 1, stdout);
    }

    if (opt->cflowd_mask & CF_BYTESMASK) {
       ui32 = *((uint32_t*)(rec+fo.dOctets));
       ui32 = htonl(ui32);
       fwrite(&ui32, sizeof (ui32), 1, stdout);
    }

    if (opt->cflowd_mask & CF_IPNEXTHOPMASK) {
       ui32 = *((uint32_t*)(rec+fo.nexthop));
       ui32 = htonl(ui32);
       fwrite(&ui32, sizeof (ui32), 1, stdout);
    }

    if (opt->cflowd_mask & CF_STARTTIMEMASK) {
       sysUpTime = *((uint32_t*)(rec+fo.sysUpTime));
       unix_secs = *((uint32_t*)(rec+fo.unix_secs));
       unix_nsecs = *((uint32_t*)(rec+fo.unix_nsecs));
       First = *((uint32_t*)(rec+fo.First));
       ftt = ftltime(sysUpTime, unix_secs, unix_nsecs, First);
       ui32 = htonl(ftt.secs);
       fwrite(&ui32, sizeof (ui32), 1, stdout);
    }

    if (opt->cflowd_mask & CF_ENDTIMEMASK) {
       sysUpTime = *((uint32_t*)(rec+fo.sysUpTime));
       unix_secs = *((uint32_t*)(rec+fo.unix_secs));
       unix_nsecs = *((uint32_t*)(rec+fo.unix_nsecs));
       Last = *((uint32_t*)(rec+fo.Last));
       ftt = ftltime(sysUpTime, unix_secs, unix_nsecs, Last);
       ui32 = htonl(ftt.secs);
       fwrite(&ui32, sizeof (ui32), 1, stdout);
    }

    if (opt->cflowd_mask & CF_PROTOCOLMASK) {
       ui8 = *((uint8_t*)(rec+fo.prot));
       fwrite(&ui8, sizeof (ui8), 1, stdout);
    }

    if (opt->cflowd_mask & CF_TOSMASK) {
       ui8 = *((uint8_t*)(rec+fo.tos));
       fwrite(&ui8, sizeof (ui8), 1, stdout);
    }

    if (opt->cflowd_mask & CF_SRCASMASK) {
       ui16 = *((uint16_t*)(rec+fo.src_as));
       ui16 = htons(ui16);
       fwrite(&ui16, sizeof (ui16), 1, stdout);
    }

    if (opt->cflowd_mask & CF_DSTASMASK) {
       ui16 = *((uint16_t*)(rec+fo.dst_as));
       ui16 = htons(ui16);
       fwrite(&ui16, sizeof (ui16), 1, stdout);
    }

    if (opt->cflowd_mask & CF_SRCMASKLENMASK) {
       ui8 = *((uint8_t*)(rec+fo.src_mask));
       fwrite(&ui8, sizeof (ui8), 1, stdout);
    }

    if (opt->cflowd_mask & CF_DSTMASKLENMASK) {
       ui8 = *((uint8_t*)(rec+fo.dst_mask));
       fwrite(&ui8, sizeof (ui8), 1, stdout);
    }

    if (opt->cflowd_mask & CF_TCPFLAGSMASK) {
       ui8 = *((uint8_t*)(rec+fo.tcp_flags));
       fwrite(&ui8, sizeof (ui8), 1, stdout);
    }

    if (opt->cflowd_mask & CF_INPUTENCAPMASK) {
       ui8 = *((uint8_t*)(rec+fo.in_encaps));
       fwrite(&ui8, sizeof (ui8), 1, stdout);
    }

    if (opt->cflowd_mask & CF_OUTPUTENCAPMASK) {
       ui8 = *((uint8_t*)(rec+fo.out_encaps));
       fwrite(&ui8, sizeof (ui8), 1, stdout);
    }

    if (opt->cflowd_mask & CF_PEERNEXTHOPMASK) {
       ui32 = *((uint32_t*)(rec+fo.peer_nexthop));
       ui32 = htonl(ui32);
       fwrite(&ui32, sizeof (ui32), 1, stdout);
    }

    if (opt->cflowd_mask & CF_ENGINETYPEMASK) {
       ui8 = *((uint8_t*)(rec+fo.engine_type));
       fwrite(&ui8, sizeof (ui8), 1, stdout);
    }

    if (opt->cflowd_mask & CF_ENGINEIDMASK) {
       ui8 = *((uint8_t*)(rec+fo.engine_id));
       fwrite(&ui8, sizeof (ui8), 1, stdout);
    }

    ++opt->records;

  } /* while */

  return 0;

} /* format 0 */