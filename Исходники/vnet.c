void rtos_vnet_recv(struct rgmp_vnet *rgmp_vnet, char *data, int len)
{
  struct vnet_driver_s *vnet = rgmp_vnet->priv;

  do
    {
      /* Check if the packet is a valid size for the network buffer
       * configuration.
       */

      if (len > CONFIG_NET_ETH_MTU || len < 14)
        {
#ifdef CONFIG_DEBUG
          cprintf("VNET: receive invalid packet of size %d\n", len);
#endif
          return;
        }

      /* Copy the data data from the hardware to vnet->sk_dev.d_buf.  Set
       * amount of data in vnet->sk_dev.d_len
       */

      memcpy(vnet->sk_dev.d_buf, data, len);
      vnet->sk_dev.d_len = len;

#ifdef CONFIG_NET_PKT
      /* When packet sockets are enabled, feed the frame into the packet tap */

       pkt_input(&vnet->sk_dev);
#endif

      /* We only accept IP packets of the configured type and ARP packets */

#ifdef CONFIG_NET_IPv4
      if (BUF->type == HTONS(ETHTYPE_IP))
        {
          nllvdbg("IPv4 frame\n");

          /* Handle ARP on input then give the IPv4 packet to the network
           * layer
           */

          arp_ipin(&vnet->sk_dev);
          ipv4_input(&vnet->sk_dev);

          /* If the above function invocation resulted in data that should be
           * sent out on the network, the field  d_len will set to a value > 0.
           */

          if (vnet->sk_dev.d_len > 0)
            {
              /* Update the Ethernet header with the correct MAC address */

#ifdef CONFIG_NET_IPv6
              if (IFF_IS_IPv4(vnet->sk_dev.d_flags))
#endif
                {
                  arp_out(&vnet->sk_dev);
                }
#ifdef CONFIG_NET_IPv6
              else
                {
                  neighbor_out(&vnet->sk_dev);
                }
#endif

              /* And send the packet */

              vnet_transmit(vnet);
            }
        }
      else
#endif
#ifdef CONFIG_NET_IPv6
      if (BUF->type == HTONS(ETHTYPE_IP6))
        {
          nllvdbg("Iv6 frame\n");

          /* Give the IPv6 packet to the network layer */

          ipv6_input(&vnet->sk_dev);

          /* If the above function invocation resulted in data that should be
           * sent out on the network, the field  d_len will set to a value > 0.
           */

          if (vnet->sk_dev.d_len > 0)
           {
              /* Update the Ethernet header with the correct MAC address */

#ifdef CONFIG_NET_IPv4
              if (IFF_IS_IPv4(vnet->sk_dev.d_flags))
                {
                  arp_out(&vnet->sk_dev);
                }
              else
#endif
#ifdef CONFIG_NET_IPv6
                {
                  neighbor_out(&vnet->sk_dev);
                }
#endif

              /* And send the packet */

              vnet_transmit(vnet);
            }
        }
      else
#endif
#ifdef CONFIG_NET_ARP
      if (BUF->type == htons(ETHTYPE_ARP))
        {
          arp_arpin(&vnet->sk_dev);

          /* If the above function invocation resulted in data that should
           * be sent out on the network, the field  d_len will set to a
           * value > 0.
           */

          if (vnet->sk_dev.d_len > 0)
            {
              vnet_transmit(vnet);
            }
        }
#endif
    }
  while (0); /* While there are more packets to be processed */
}