void multi_dhcp_parse_dhcp_msg(struct multi_dhcp_info *di, 
        struct multi_dhcp_message *dm, struct multi_link_info *li){
    struct multi_dhcp_config cfg;
    uint32_t t_now, t_diff;
    uint8_t ipaddr[INET_ADDRSTRLEN];
    uint8_t baddr[INET_ADDRSTRLEN];
    uint8_t gwaddr[INET_ADDRSTRLEN];
    uint8_t netmask[INET_ADDRSTRLEN];

    multi_dhcp_parse_options(dm, &cfg);

    if (dm->xid != di->xid || dm->hlen != 6 || 
            memcmp(dm->chaddr, &(di->mac_addr),6)){ 
        //fprintf(stderr, "Message intended for someone else!\n");
        return;
    }

    switch(di->state){
        case SELECTING:
            //One typical scenario here is if the lease expires before the 
            //DHCP ACK for final REBIND is received
            if(cfg.dhcpmsgtype != DHCP_TYPE_OFFER){ 
                MULTI_DEBUG_PRINT(stderr,"Mismatch state. In INIT but did not "
                        "get OFFER. Got %u\n", cfg.dhcpmsgtype);
                return;
            }

            /* Move on to the next state, retrans count must be reset */
            di->retrans_count = 0;

            MULTI_DEBUG_PRINT(stderr,"Received DHCP OFFER on interface %s "
                    "(iface idx %u), will send DHCP REQUEST\n", li->dev_name, 
                    li->ifi_idx);

            di->cfg = cfg;
            di->state = REQUESTING; 
            multi_dhcp_create_dhcp_msg(di);
            break;
        case RENEWING:
        case REBINDING:
        case REQUESTING:
        case REBOOTING:
            /* All these states  */
            if(cfg.dhcpmsgtype == DHCP_TYPE_NAK){
                /* According to the RFC, a NAK involves moving straight back to
                 * INIT and resending request. Moving to INIT implies resetting
                 * variables and state, just in case */
                MULTI_DEBUG_PRINT(stderr,"Got NAK in state %u. Resetting and "
                        "retrying DISCOVER! (iface idx %u)\n", di->state, 
                        di->ifidx);
                di->state = INIT;
                di->req_sent_time = 0;
                //Since next packet is sent immideatly, this can 0 (as opposed 
                //to -1 for ACK)
                di->retrans_count = 0; 

                /* Set state as waiting. I can here if a) rebooting fails b)
                 * requesting fails c) renewing fails d) rebinding fails. In the
                 * last two, the link can be in UP state */
                g_static_rw_lock_writer_lock(&(li->state_lock));
                li->state = WAITING_FOR_DHCP;
                g_static_rw_lock_writer_unlock(&(li->state_lock));

                multi_dhcp_create_dhcp_msg(di);
            } else if(cfg.dhcpmsgtype == DHCP_TYPE_ACK){
                //Always decline DHCP address
                di->cfg = cfg; //Just in case, I know these are the good values
                
                di->state = BOUND;
                
                inet_ntop(AF_INET, &(cfg.address), (char*) ipaddr, INET_ADDRSTRLEN);
                inet_ntop(AF_INET, &(cfg.broadcast), (char*) baddr, INET_ADDRSTRLEN);
                inet_ntop(AF_INET, &(cfg.gateway), (char*) gwaddr, INET_ADDRSTRLEN);
                inet_ntop(AF_INET, &(cfg.netmask), (char*) netmask, INET_ADDRSTRLEN);
                
                //Do the timeout calculation. Be warned that inet_ntoa is NOT
                    //reentrant. In other words, the IP adresses are wrong!
                MULTI_DEBUG_PRINT(stderr,"Got DHCP ACK on interface %s "
                        "(iface idx %u). %s will be bound to IP: %s Broadcast: "
                        "%s Gateway: %s Netmask %s (%u) Lease: %u T1: %u T2: "
                        "%u\n", li->dev_name, li->ifi_idx, li->dev_name, 
                        ipaddr, baddr, gwaddr, netmask, 
                        32 - (ffs(ntohl(cfg.netmask.s_addr)) - 1), 
                        cfg.lease, cfg.t1, cfg.t2);


                //TODO: I need some variable or check to prevent adding the same IP twice. Compare cfg is maybe sufficient? Or at least address?
                //pthread_mutex_lock(&(li->link_state_lock));
                g_static_rw_lock_writer_lock(&(li->state_lock));

                /* This is needed if one interface switches network. Otherwise,
                 * the main thread will not know that it has to clean up (it
                 * will just see a new set of addresses)! */
                /* Need to wireless access points in order to test this, with
                 * different subnets */
                if(li->cfg.address.s_addr != 0 && 
                    (li->cfg.address.s_addr != cfg.address.s_addr || 
                     li->cfg.broadcast.s_addr != cfg.broadcast.s_addr || 
                     li->cfg.gateway.s_addr != cfg.gateway.s_addr || 
                     li->cfg.netmask.s_addr != cfg.netmask.s_addr)){

                    li->state = DHCP_IP_CHANGED;
                    li->new_cfg = cfg;
                    multi_dhcp_notify_link_module(li->write_pipe);
                } else{ 
                    li->cfg = cfg;

                    /* This is correct becuase if the information has not
                     * changed, then there is no need to update the state. The
                     * cfg must be updated due to leases and so on */
                    if(li->state != LINK_UP){
                        li->state = GOT_IP_DHCP;
                        multi_dhcp_notify_link_module(li->write_pipe);
                    }
                }

                g_static_rw_lock_writer_unlock(&(li->state_lock));

                t_now = time(NULL);
                t_diff = t_now - di->req_sent_time;

                di->lease = cfg.lease;
                di->t1 = cfg.t1 ? cfg.t1 : cfg.lease / 2;
                di->t2 = cfg.t2 ? cfg.t2 : cfg.lease * 0.875;

                /* Not exactly sure what to do in this case */                
                assert(t_diff < di->t1 || t_diff < di->t2);
                assert(di->t1 < di->t2);

                /* Lease is from WHEN the request was sent */
                di->lease -= t_diff;
                di->t1 -= t_diff;
                di->t2 -= t_diff;

                /* Convert values to be absolute */
                di->lease += t_now;
                di->t1 += t_now;
                di->t2 += t_now;
 
                /* Every packet has been accounted for, so timers and everything can be reset */
                di->req_sent_time = 0;
                //This will overflow, but it is ok. When the next timeout (T1) 
                //is triggered, retrans_count will be increased by 1 and, thus,
                //be 0 again (but a little hackish)

                di->retrans_count = -1; 
                /* New timeout event started */
                di->output_timer = 1;
           }
        default:
            break;
    }
}