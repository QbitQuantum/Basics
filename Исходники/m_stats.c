int m_stats(struct Client *cptr, struct Client *sptr, int parc, char *parv[])
{
  struct Message* mptr;
  struct Client*  acptr;
  char            l_stat = parc > 1 ? parv[1][0] : '\0';
  int             i;
  int             doall = 0;
  int             wilds = 0;
  int             ignore_request = 0;
  int             valid_stats = 0;
  char*           name;
  char *mename = me.name;
  
  if(sptr->user && sptr->user->vlink)
    mename = sptr->user->vlink->name;

  if(!IsClient(sptr))
    {
      return 0;
    }

  if(!IsAnOper(sptr))
    {
      sendto_one(sptr, form_str(ERR_NOPRIVILEGES), mename, parv[0]);
	  return -1;
    }

  if (hunt_server(cptr,sptr,":%s STATS %s :%s",2,parc,parv)!=HUNTED_ISME)
    return 0;

  if (parc > 2)
    {
      name = parv[2];
      if (!irccmp(name, mename))
        doall = 2;
      else if (match(name, mename))
        doall = 1;
      if (strchr(name, '*') || strchr(name, '?'))
        wilds = 1;
    }
  else
    name = mename;

  switch (l_stat)
    {
    case 'L' : case 'l' :
      /*
       * send info about connections which match, or all if the
       * mask matches mename.  Only restrictions are on those who
       * are invisible not being visible to 'foreigners' who use
       * a wild card based search to list it.
       */
      for (i = 0; i <= highest_fd; i++)
        {
          if (!(acptr = local[i]))
            continue;

			
          if (!doall && wilds && !match(name, acptr->name))
            continue;
          if (!(doall || wilds) && irccmp(name, acptr->name))
            continue;

          /* I've added a sanity test to the "CurrentTime - acptr->since"
           * occasionally, acptr->since is larger than CurrentTime.
           * The code in parse.c "randomly" increases the "since",
           * which means acptr->since is larger then CurrentTime at times,
           * this gives us very high odd number.. 
           * So, I am going to return 0 for ->since if this happens.
           * - Dianora
           */
          /* trust opers not on this server */
          /* if(IsAnOper(sptr)) */

          /* Don't trust opers not on this server */
#ifdef HIDE_SERVERS_IPS
          if(MyClient(sptr) && IsAnOper(sptr) && !IsServer(acptr) &&
	    !IsConnecting(acptr) && !IsHandshake(acptr)) 
#else
          if(MyClient(sptr) && IsAnOper(sptr))
#endif
            {
              sendto_one(sptr, Lformat, mename,
                     RPL_STATSLINKINFO, parv[0],
                     get_client_name(acptr, TRUE),
                     (int)DBufLength(&acptr->sendQ),
                     (int)acptr->sendM, (int)acptr->sendK,
                     (int)acptr->receiveM, (int)acptr->receiveK,
                     CurrentTime - acptr->firsttime,
                     (CurrentTime > acptr->since) ? (CurrentTime - acptr->since):0,
                     IsServer(acptr) ? show_capabilities(acptr) : "-");
              }
            else
              {
                if(IsServer(acptr))
                  sendto_one(sptr, Lformat, mename,
                     RPL_STATSLINKINFO, parv[0],
                     get_client_name(acptr, HIDEME),
                     (int)DBufLength(&acptr->sendQ),
                     (int)acptr->sendM, (int)acptr->sendK,
                     (int)acptr->receiveM, (int)acptr->receiveK,
                     CurrentTime - acptr->firsttime,
                     (CurrentTime > acptr->since) ? (CurrentTime - acptr->since):0,
                     IsServer(acptr) ? show_capabilities(acptr) : "-");
                 else
                  sendto_one(sptr, Lformat, mename,
                     RPL_STATSLINKINFO, parv[0],
                     (IsUpper(lstat)) ?
                     get_client_name(acptr, TRUE) :
                     get_client_name(acptr, FALSE),
                     (int)DBufLength(&acptr->sendQ),
                     (int)acptr->sendM, (int)acptr->sendK,
                     (int)acptr->receiveM, (int)acptr->receiveK,
                     CurrentTime - acptr->firsttime,
                     (CurrentTime > acptr->since) ? (CurrentTime - acptr->since):0,
                     IsServer(acptr) ? show_capabilities(acptr) : "-");
              }
        }
      valid_stats++;
      break;
    case 'C' : case 'c' :
      report_configured_links(sptr, CONF_CONNECT_SERVER|CONF_NOCONNECT_SERVER);
      valid_stats++;
      break;

    case 'B' : case 'b' :
      sendto_one(sptr,":%s NOTICE %s :Use stats I instead", mename, parv[0]);
      break;

    case 'D':
      report_dlines(sptr);
      valid_stats++;
      break;
      
    case 'd':
      report_domain_stats(sptr);
      valid_stats++;
      break;

    case 'E' : case 'e' :
      sendto_one(sptr,":%s NOTICE %s :Use stats I instead", mename, parv[0]);
      break;

    case 'F' : case 'f' :
      report_channel_stats(sptr);
      break;

    case 'g' :
      report_sxlines(sptr);
      valid_stats++;
      break;


    case 'G' :
      report_glines(sptr, NULL);
      valid_stats++;
      break;

    case 'H' : case 'h' :
      report_configured_links(sptr, CONF_HUB|CONF_LEAF);
      valid_stats++;
      break;

    case 'i' :
      report_vlinks(sptr);
      valid_stats++;
      break;

    case 'I' :
      report_mtrie_conf_links(sptr, CONF_CLIENT);
      valid_stats++;
      break;

    case 'k' :
      report_temp_klines(sptr);
      valid_stats++;
      break;

    case 'K' :
      if(parc > 3)
        report_matching_host_klines(sptr,parv[3]);
      else
        report_mtrie_conf_links(sptr, CONF_KILL);
      valid_stats++;
      break;

    case 'M' : case 'm' :
      for (mptr = msgtab; mptr->cmd; mptr++)
          sendto_one(sptr, form_str(RPL_STATSCOMMANDS),
                     mename, parv[0], mptr->cmd,
                     mptr->count, mptr->bytes);
      valid_stats++;
      break;

    case 'o' : case 'O' :
      report_configured_links(sptr, CONF_OPS);
      valid_stats++;
      break;

    case 'P' :
      show_ports(sptr);
      valid_stats++;
      break;

    case 'p' :
      show_opers(sptr);
      valid_stats++;
      break;

    case 'Q' :
      report_qlines(sptr);
      valid_stats++;
      break;

    case 'q' :
      report_sqlines(sptr);
      valid_stats++;
      break;	  

    case 'R' : case 'r' :
      send_usage(sptr,parv[0]);
      valid_stats++;
      break;

    case 'S' :
      list_scache(cptr,sptr,parc,parv);
      valid_stats++;
      break;

    case 'T' : case 't' :
      tstats(sptr, parv[0]);
      valid_stats++;
      break;

    case 'U' :
      report_specials(sptr,CONF_ULINE,RPL_STATSULINE);
      valid_stats++;
      break;

    case 'u' :
      {
        time_t now;
        
        now = CurrentTime - me.since;
        sendto_one(sptr, form_str(RPL_STATSUPTIME), mename, parv[0],
                   now/86400, (now/3600)%24, (now/60)%60, now%60);
        sendto_one(sptr, form_str(RPL_STATSCONN), mename, parv[0],
                   MaxConnectionCount, MaxClientCount,
                   Count.totalrestartcount);
        valid_stats++;
        break;
      }

    case 'V' :
      show_servers(sptr);
      valid_stats++;
      break;

    case 'v' :
      report_svlines(sptr);
      valid_stats++;
      break;
    case 'x' :
        report_specials(sptr,CONF_XLINE,RPL_STATSXLINE);
        valid_stats++;
      break;
	  
    case 'X' :        
	report_configured_links(sptr, CONF_MISSING);
        valid_stats++;
      break;;
	  

    case 'Y' : case 'y' :
        report_classes(sptr);
        valid_stats++;
      break;
	  
    case 'Z' :
      report_zlines(sptr);
      valid_stats++;
      break;

	case 'z' :
      count_memory(sptr, parv[0]);
      valid_stats++;
      break;

    case '?':
      serv_info(sptr, parv[0]);
      valid_stats++;
      break;

    default :
      l_stat = '*';
      break;
    }
  sendto_one(sptr, form_str(RPL_ENDOFSTATS), mename, parv[0], l_stat);

  /* personally, I don't see why opers need to see stats requests
   * at all. They are just "noise" to an oper, and users can't do
   * any damage with stats requests now anyway. So, why show them?
   * -Dianora
   */

  if (valid_stats)
    {
      if ( (l_stat == 'L') || (l_stat == 'l') )
        {
          sendto_ops_imodes(IMODE_SPY,
                "STATS %c requested by %s (%s@%s) [%s] on %s%s",
                l_stat,
                sptr->name,
                sptr->username,
                sptr->host,
                sptr->user->server,
                parc > 2 ? parv[2] : "<no recipient>",
                ignore_request > 0 ? " [request ignored]" : "\0"
                );
        }
      else
        {
          sendto_ops_imodes(IMODE_SPY,
                "STATS %c requested by %s (%s@%s) [%s]%s",
                l_stat,
                sptr->name,
                sptr->username,
                sptr->host,
                sptr->user->server,
                ignore_request > 0 ? " [request ignored]" : "\0"
                );
        }
    }

  return 0;
}