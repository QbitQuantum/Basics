/**
 * Reassembles incoming IP fragments into an IP datagram.
 *
 * @param p points to a pbuf chain of the fragment
 * @return NULL if reassembly is incomplete, ? otherwise
 */
struct pbuf *
ip4_reass(struct pbuf *p)
{
  struct pbuf *r;
  struct ip_hdr *fraghdr;
  struct ip_reassdata *ipr;
  struct ip_reass_helper *iprh;
  u16_t offset, len;
  u8_t clen;

  IPFRAG_STATS_INC(ip_frag.recv);
  MIB2_STATS_INC(mib2.ipreasmreqds);

  fraghdr = (struct ip_hdr*)p->payload;

  if ((IPH_HL(fraghdr) * 4) != IP_HLEN) {
    LWIP_DEBUGF(IP_REASS_DEBUG,("ip4_reass: IP options currently not supported!\n"));
    IPFRAG_STATS_INC(ip_frag.err);
    goto nullreturn;
  }

  offset = (ntohs(IPH_OFFSET(fraghdr)) & IP_OFFMASK) * 8;
  len = ntohs(IPH_LEN(fraghdr)) - IPH_HL(fraghdr) * 4;

  /* Check if we are allowed to enqueue more datagrams. */
  clen = pbuf_clen(p);
  if ((ip_reass_pbufcount + clen) > IP_REASS_MAX_PBUFS) {
#if IP_REASS_FREE_OLDEST
    if (!ip_reass_remove_oldest_datagram(fraghdr, clen) ||
        ((ip_reass_pbufcount + clen) > IP_REASS_MAX_PBUFS))
#endif /* IP_REASS_FREE_OLDEST */
    {
      /* No datagram could be freed and still too many pbufs enqueued */
      LWIP_DEBUGF(IP_REASS_DEBUG,("ip4_reass: Overflow condition: pbufct=%d, clen=%d, MAX=%d\n",
        ip_reass_pbufcount, clen, IP_REASS_MAX_PBUFS));
      IPFRAG_STATS_INC(ip_frag.memerr);
      /* @todo: send ICMP time exceeded here? */
      /* drop this pbuf */
      goto nullreturn;
    }
  }

  /* Look for the datagram the fragment belongs to in the current datagram queue,
   * remembering the previous in the queue for later dequeueing. */
  for (ipr = reassdatagrams; ipr != NULL; ipr = ipr->next) {
    /* Check if the incoming fragment matches the one currently present
       in the reassembly buffer. If so, we proceed with copying the
       fragment into the buffer. */
    if (IP_ADDRESSES_AND_ID_MATCH(&ipr->iphdr, fraghdr)) {
      LWIP_DEBUGF(IP_REASS_DEBUG, ("ip4_reass: matching previous fragment ID=%"X16_F"\n",
        ntohs(IPH_ID(fraghdr))));
      IPFRAG_STATS_INC(ip_frag.cachehit);
      break;
    }
  }

  if (ipr == NULL) {
  /* Enqueue a new datagram into the datagram queue */
    ipr = ip_reass_enqueue_new_datagram(fraghdr, clen);
    /* Bail if unable to enqueue */
    if (ipr == NULL) {
      goto nullreturn;
    }
  } else {
    if (((ntohs(IPH_OFFSET(fraghdr)) & IP_OFFMASK) == 0) &&
      ((ntohs(IPH_OFFSET(&ipr->iphdr)) & IP_OFFMASK) != 0)) {
      /* ipr->iphdr is not the header from the first fragment, but fraghdr is
       * -> copy fraghdr into ipr->iphdr since we want to have the header
       * of the first fragment (for ICMP time exceeded and later, for copying
       * all options, if supported)*/
      SMEMCPY(&ipr->iphdr, fraghdr, IP_HLEN);
    }
  }
  /* Track the current number of pbufs current 'in-flight', in order to limit
  the number of fragments that may be enqueued at any one time */
  ip_reass_pbufcount += clen;

  /* At this point, we have either created a new entry or pointing
   * to an existing one */

  /* check for 'no more fragments', and update queue entry*/
  if ((IPH_OFFSET(fraghdr) & PP_NTOHS(IP_MF)) == 0) {
    ipr->flags |= IP_REASS_FLAG_LASTFRAG;
    ipr->datagram_len = offset + len;
    LWIP_DEBUGF(IP_REASS_DEBUG,
     ("ip4_reass: last fragment seen, total len %"S16_F"\n",
      ipr->datagram_len));
  }
  /* find the right place to insert this pbuf */
  /* @todo: trim pbufs if fragments are overlapping */
  if (ip_reass_chain_frag_into_datagram_and_validate(ipr, p)) {
    struct ip_reassdata *ipr_prev;
    /* the totally last fragment (flag more fragments = 0) was received at least
     * once AND all fragments are received */
    ipr->datagram_len += IP_HLEN;

    /* save the second pbuf before copying the header over the pointer */
    r = ((struct ip_reass_helper*)ipr->p->payload)->next_pbuf;

    /* copy the original ip header back to the first pbuf */
    fraghdr = (struct ip_hdr*)(ipr->p->payload);
    SMEMCPY(fraghdr, &ipr->iphdr, IP_HLEN);
    IPH_LEN_SET(fraghdr, htons(ipr->datagram_len));
    IPH_OFFSET_SET(fraghdr, 0);
    IPH_CHKSUM_SET(fraghdr, 0);
    /* @todo: do we need to set/calculate the correct checksum? */
#if CHECKSUM_GEN_IP
    IF__NETIF_CHECKSUM_ENABLED(ip_current_input_netif(), NETIF_CHECKSUM_GEN_IP) {
      IPH_CHKSUM_SET(fraghdr, inet_chksum(fraghdr, IP_HLEN));
    }
#endif /* CHECKSUM_GEN_IP */

    p = ipr->p;

    /* chain together the pbufs contained within the reass_data list. */
    while (r != NULL) {
      iprh = (struct ip_reass_helper*)r->payload;

      /* hide the ip header for every succeeding fragment */
      pbuf_header(r, -IP_HLEN);
      pbuf_cat(p, r);
      r = iprh->next_pbuf;
    }

    /* find the previous entry in the linked list */
    if (ipr == reassdatagrams) {
      ipr_prev = NULL;
    } else {
      for (ipr_prev = reassdatagrams; ipr_prev != NULL; ipr_prev = ipr_prev->next) {
        if (ipr_prev->next == ipr) {
          break;
        }
      }
    }

    /* release the sources allocate for the fragment queue entry */
    ip_reass_dequeue_datagram(ipr, ipr_prev);

    /* and adjust the number of pbufs currently queued for reassembly. */
    ip_reass_pbufcount -= pbuf_clen(p);

    MIB2_STATS_INC(mib2.ipreasmoks);

    /* Return the pbuf chain */
    return p;
  }