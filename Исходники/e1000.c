static void e1000_receive(struct e1000_dev *e1000)
{
  int head = e1000->rx_ring.head;
  unsigned char *cp = (unsigned char *)
      (e1000->rx_ring.buf + head * CONFIG_E1000_BUFF_SIZE);
  int cnt;

  while (e1000->rx_ring.desc[head].desc_status)
    {
      /* Check for errors and update statistics */

      /* Here we do not handle packets that exceed packet-buffer size */

      if ((e1000->rx_ring.desc[head].desc_status & 3) == 1)
        {
          cprintf("NIC READ: Oversized packet\n");
          goto next;
        }

      /* Check if the packet is a valid size for the uIP buffer configuration */

      /* get the number of actual data-bytes in this packet */

      cnt = e1000->rx_ring.desc[head].packet_length;

      if (cnt > CONFIG_NET_BUFSIZE || cnt < 14)
        {
          cprintf("NIC READ: invalid package size\n");
          goto next;
        }

      /* Copy the data data from the hardware to e1000->uip_dev.d_buf.  Set
       * amount of data in e1000->uip_dev.d_len
       */

      /* now we try to copy these data-bytes to the UIP buffer */

      memcpy(e1000->uip_dev.d_buf, cp, cnt);
      e1000->uip_dev.d_len = cnt;

      /* We only accept IP packets of the configured type and ARP packets */

#ifdef CONFIG_NET_IPv6
      if (BUF->type == HTONS(UIP_ETHTYPE_IP6))
#else
        {
          if (BUF->type == HTONS(UIP_ETHTYPE_IP))
#endif
            {
              arp_ipin(&e1000->uip_dev);
              uip_input(&e1000->uip_dev);

              /* If the above function invocation resulted in data that should be
               * sent out on the network, the field  d_len will set to a value > 0.
               */

              if (e1000->uip_dev.d_len > 0)
                {
                  arp_out(&e1000->uip_dev);
                  e1000_transmit(e1000);
                }
            }
          else if (BUF->type == htons(UIP_ETHTYPE_ARP))
            {
              arp_arpin(&e1000->uip_dev);

              /* If the above function invocation resulted in data that should be
               * sent out on the network, the field  d_len will set to a value > 0.
               */

              if (e1000->uip_dev.d_len > 0)
                {
                  e1000_transmit(e1000);
                }
            }
        }

next:
      e1000->rx_ring.desc[head].desc_status = 0;
      e1000->rx_ring.head = (head + 1) % CONFIG_E1000_N_RX_DESC;
      e1000->rx_ring.free++;
      head = e1000->rx_ring.head;
      cp = (unsigned char *)(e1000->rx_ring.buf + head * CONFIG_E1000_BUFF_SIZE);
    }
}