/* Interface between zebra message and rtm message. */
static int
kernel_rtm_ipv4 (int cmd, struct prefix *p, struct rib *rib, int family)

{
  struct sockaddr_in *mask = NULL;
  struct sockaddr_in sin_dest, sin_mask, sin_gate;
  struct nexthop *nexthop, *tnexthop;
  int recursing;
  int nexthop_num = 0;
  unsigned int ifindex = 0;
  int gate = 0;
  int error;
  char prefix_buf[INET_ADDRSTRLEN];

  if (IS_ZEBRA_DEBUG_RIB)
    inet_ntop (AF_INET, &p->u.prefix, prefix_buf, INET_ADDRSTRLEN);
  memset (&sin_dest, 0, sizeof (struct sockaddr_in));
  sin_dest.sin_family = AF_INET;
#ifdef HAVE_STRUCT_SOCKADDR_IN_SIN_LEN
  sin_dest.sin_len = sizeof (struct sockaddr_in);
#endif /* HAVE_STRUCT_SOCKADDR_IN_SIN_LEN */
  sin_dest.sin_addr = p->u.prefix4;

  memset (&sin_mask, 0, sizeof (struct sockaddr_in));

  memset (&sin_gate, 0, sizeof (struct sockaddr_in));
  sin_gate.sin_family = AF_INET;
#ifdef HAVE_STRUCT_SOCKADDR_IN_SIN_LEN
  sin_gate.sin_len = sizeof (struct sockaddr_in);
#endif /* HAVE_STRUCT_SOCKADDR_IN_SIN_LEN */

  /* Make gateway. */
  for (ALL_NEXTHOPS_RO(rib->nexthop, nexthop, tnexthop, recursing))
    {
      if (CHECK_FLAG (nexthop->flags, NEXTHOP_FLAG_RECURSIVE))
        continue;

      gate = 0;
      char gate_buf[INET_ADDRSTRLEN] = "NULL";

      /*
       * XXX We need to refrain from kernel operations in some cases,
       * but this if statement seems overly cautious - what about
       * other than ADD and DELETE?
       */
      if ((cmd == RTM_ADD
	   && CHECK_FLAG (nexthop->flags, NEXTHOP_FLAG_ACTIVE))
	  || (cmd == RTM_DELETE
	      && CHECK_FLAG (nexthop->flags, NEXTHOP_FLAG_FIB)
	      ))
	{
	  if (nexthop->type == NEXTHOP_TYPE_IPV4 ||
	      nexthop->type == NEXTHOP_TYPE_IPV4_IFINDEX)
	    {
	      sin_gate.sin_addr = nexthop->gate.ipv4;
	      gate = 1;
	    }
	  if (nexthop->type == NEXTHOP_TYPE_IFINDEX
	      || nexthop->type == NEXTHOP_TYPE_IFNAME
	      || nexthop->type == NEXTHOP_TYPE_IPV4_IFINDEX)
	    ifindex = nexthop->ifindex;
	  if (nexthop->type == NEXTHOP_TYPE_BLACKHOLE)
	    {
	      struct in_addr loopback;
	      loopback.s_addr = htonl (INADDR_LOOPBACK);
	      sin_gate.sin_addr = loopback;
	      gate = 1;
	    }

	  if (gate && p->prefixlen == 32)
	    mask = NULL;
	  else
	    {
	      masklen2ip (p->prefixlen, &sin_mask.sin_addr);
	      sin_mask.sin_family = AF_INET;
#ifdef HAVE_STRUCT_SOCKADDR_IN_SIN_LEN
	      sin_mask.sin_len = sin_masklen (sin_mask.sin_addr);
#endif /* HAVE_STRUCT_SOCKADDR_IN_SIN_LEN */
	      mask = &sin_mask;
	    }

	  error = rtm_write (cmd,
			     (union sockunion *)&sin_dest, 
			     (union sockunion *)mask, 
			     gate ? (union sockunion *)&sin_gate : NULL,
			     ifindex,
			     rib->flags,
			     rib->metric);

           if (IS_ZEBRA_DEBUG_RIB)
           {
             if (!gate)
             {
               zlog_debug ("%s: %s/%d: attention! gate not found for rib %p",
                 __func__, prefix_buf, p->prefixlen, rib);
               rib_dump (p, rib);
             }
             else
               inet_ntop (AF_INET, &sin_gate.sin_addr, gate_buf, INET_ADDRSTRLEN);
           }
 
           switch (error)
           {
             /* We only flag nexthops as being in FIB if rtm_write() did its work. */
             case ZEBRA_ERR_NOERROR:
               nexthop_num++;
               if (IS_ZEBRA_DEBUG_RIB)
                 zlog_debug ("%s: %s/%d: successfully did NH %s",
                   __func__, prefix_buf, p->prefixlen, gate_buf);
               if (cmd == RTM_ADD)
                 SET_FLAG (nexthop->flags, NEXTHOP_FLAG_FIB);
               break;
 
             /* The only valid case for this error is kernel's failure to install
              * a multipath route, which is common for FreeBSD. This should be
              * ignored silently, but logged as an error otherwise.
              */
             case ZEBRA_ERR_RTEXIST:
               if (cmd != RTM_ADD)
                 zlog_err ("%s: rtm_write() returned %d for command %d",
                   __func__, error, cmd);
               continue;
               break;
 
             /* Given that our NEXTHOP_FLAG_FIB matches real kernel FIB, it isn't
              * normal to get any other messages in ANY case.
              */
             case ZEBRA_ERR_RTNOEXIST:
             case ZEBRA_ERR_RTUNREACH:
             default:
               /* This point is reachable regardless of debugging mode. */
               if (!IS_ZEBRA_DEBUG_RIB)
                 inet_ntop (AF_INET, &p->u.prefix, prefix_buf, INET_ADDRSTRLEN);
               zlog_err ("%s: %s/%d: rtm_write() unexpectedly returned %d for command %s",
                 __func__, prefix_buf, p->prefixlen, error, lookup (rtm_type_str, cmd));
               break;
           }
         } /* if (cmd and flags make sense) */
       else
         if (IS_ZEBRA_DEBUG_RIB)
           zlog_debug ("%s: odd command %s for flags %d",
             __func__, lookup (rtm_type_str, cmd), nexthop->flags);
     } /* for (ALL_NEXTHOPS_RO(...))*/
 
   /* If there was no useful nexthop, then complain. */
   if (nexthop_num == 0 && IS_ZEBRA_DEBUG_KERNEL)
     zlog_debug ("%s: No useful nexthops were found in RIB entry %p", __func__, rib);

  return 0; /*XXX*/
}