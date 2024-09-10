void main() {

    struct hw_ip_pair *hi_pair;
    char IP_str[20], cache_hw_addr[6];
    fd_set rset;
    int cache_ifindex, cache_hatype;
    struct hw_addr HWaddr;

    hi_pair = malloc(sizeof(struct hw_ip_pair));
    get_hw_ip_pair(hi_pair);

    printf("My IP :%s,\t HW addr", hi_pair->ip_addr);
    print_mac_to_string(hi_pair->hw_addr);
    printf("\n");

    int pf_pack_sockfd = create_pf_pack_socket();
    void* buffer = (void*)malloc(ETH_FRAME_LEN);

    int listen_sockfd, conn_sockfd, clilen, n;
    struct sockaddr_un servaddr, cliaddr;
    char sendline[MAXLINE], recvline[MAXLINE];
    struct sockaddr_in *destIP = malloc(sizeof(struct sockaddr_in));
    char ip_addr[20];
    struct arp_packet *arp_req = malloc(sizeof(struct arp_packet));
    struct arp_packet *arp_rep = malloc(sizeof(struct arp_packet));
    struct arp_packet *arp_recv = malloc(sizeof(struct arp_packet));
    struct sockaddr_ll socket_address; 
    int ll_len = sizeof(struct sockaddr_ll);
    int i=0;

    listen_sockfd = Socket(AF_LOCAL, SOCK_STREAM, 0);
    unlink(SUN_PATH_ARP);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sun_family = AF_LOCAL;
    strcpy(servaddr.sun_path, SUN_PATH_ARP);
    Bind(listen_sockfd, (SA *) &servaddr, sizeof(servaddr));
    Listen(listen_sockfd, LISTENQ);

    int lookup_flag=0;
    clilen = sizeof(struct sockaddr_un);
    while(1) {

        FD_ZERO(&rset);

        FD_SET(listen_sockfd, &rset);
        FD_SET(pf_pack_sockfd, &rset);
        FD_SET(conn_sockfd, &rset);
        int max;

        if(conn_sockfd != 0)
            max = max(max(listen_sockfd, conn_sockfd),pf_pack_sockfd);
        else	
            max = max(listen_sockfd,pf_pack_sockfd);
        int ret = select(max+1, &rset, NULL, NULL, NULL);

        if(FD_ISSET(listen_sockfd, &rset)) {
            conn_sockfd = Accept(listen_sockfd, (SA *) &cliaddr, &clilen);
            /*			n = read(conn_sockfd, destIP, sizeof(struct sockaddr_in));
                        Inet_ntop(AF_INET, &(destIP->sin_addr), ip_addr, 20);

            // Lookup for the <HW,IP> pair in the ARP cache
            lookup_arp_cache(ip_addr, cache_hw_addr, &cache_ifindex, &cache_hatype,&lookup_flag);


            if(lookup_flag == 0) {
            printf("Entry not found from cache\n");
            create_arp_request_packet(arp_req, ip_addr, hi_pair);
            send_arp_request(pf_pack_sockfd, arp_req, hi_pair, conn_sockfd);
            }
            else{
            printf("Entry found from cache\n");
            // Send from cache
            HWaddr.sll_ifindex = cache_ifindex;
            HWaddr.sll_hatype = cache_hatype;
            HWaddr.sll_halen = sizeof(cache_hatype);

            memcpy(HWaddr.mac_addr, cache_hw_addr,6); 

            print_mac_to_string(HWaddr.mac_addr);
            Write(conn_sockfd, (void *)&HWaddr, sizeof(HWaddr));
            close(conn_sockfd);

            }
            printf("Sent ARP request\n");
             */		}

        else if(ret!= -1 && FD_ISSET(conn_sockfd, &rset)) {
            n = read(conn_sockfd, destIP, sizeof(struct sockaddr_in));
            Inet_ntop(AF_INET, &(destIP->sin_addr), ip_addr, 20);

            // Lookup for the <HW,IP> pair in the ARP cache
            lookup_arp_cache(ip_addr, cache_hw_addr, &cache_ifindex, &cache_hatype,&lookup_flag);


            if(lookup_flag == 0) {
                create_arp_request_packet(arp_req, ip_addr, hi_pair);
                printf("send 1\n");
                send_arp_request(pf_pack_sockfd, arp_req, hi_pair, conn_sockfd);
            }   
            else{
                // Send from cache
                HWaddr.sll_ifindex = cache_ifindex;
                HWaddr.sll_hatype = cache_hatype;
                HWaddr.sll_halen = sizeof(cache_hatype);

                memcpy(HWaddr.mac_addr, cache_hw_addr,6);

                //				print_mac_to_string(HWaddr.mac_addr);
                Write(conn_sockfd, (void *)&HWaddr, sizeof(HWaddr));
                close(conn_sockfd);
                conn_sockfd = 0;
            }
        }

        else if(FD_ISSET(pf_pack_sockfd, &rset)) {

            Recvfrom(pf_pack_sockfd, buffer, ETH_FRAME_LEN, 0, (SA *)&socket_address, &ll_len);
            void *data = buffer + 14;
            arp_rep = (struct arp_packet *)data;
            if (arp_rep->id == ARP_ID){
                if(arp_rep->op == ARP_REQ) {
                    if(strcmp(arp_rep->dest_IP, hi_pair->ip_addr) == 0) {

                        printf("Printing Ethernet Header and ARP Request Packet Received\n");
                        print_ethernet_and_arp(arp_rep->src_mac, arp_rep->dest_mac, arp_rep);
                        add_to_arp_cache_list(arp_rep->src_IP, arp_rep->src_mac, socket_address.sll_ifindex, socket_address.sll_hatype, conn_sockfd, 1);
                        //						print_arp_cache_list();
                        create_arp_reply_packet(arp_recv, arp_rep->src_IP, hi_pair, arp_rep->src_mac, arp_rep->id);
                        send_arp_reply(pf_pack_sockfd, arp_recv, hi_pair, socket_address.sll_ifindex);
                    }
                    else {
                        update_arp_cache(arp_rep->src_IP, arp_rep->src_mac, socket_address.sll_ifindex, 0, conn_sockfd);
                    }
                    continue;
                }
                else if(arp_rep->op == ARP_REP) {
                    if(ret == -1) {
                        delete_from_arp_cache(arp_rep->src_IP);
                        //						print_arp_cache_list();
                        continue;
                    }

                    printf("Printing Ethernet Header and ARP Reply Packet Received\n");
                    print_ethernet_and_arp(arp_rep->src_mac, arp_rep->dest_mac, arp_rep);

                    update_arp_cache(arp_rep->src_IP, arp_rep->src_mac, socket_address.sll_ifindex, 0, conn_sockfd);
                    //					print_arp_cache_list();
                    HWaddr.sll_ifindex = socket_address.sll_ifindex;
                    HWaddr.sll_hatype = socket_address.sll_hatype;
                    HWaddr.sll_halen = socket_address.sll_halen;

                    memcpy(HWaddr.mac_addr, arp_rep->src_mac,6); 

                    //					print_mac_to_string(HWaddr.mac_addr);
                    Write(conn_sockfd, (void *)&HWaddr, sizeof(HWaddr));
                    close(conn_sockfd);
                    conn_sockfd = 0;
                    update_arp_cache(arp_rep->src_IP, arp_rep->src_mac, socket_address.sll_ifindex, 0, -1);
                    //					print_arp_cache_list();
                }
            }

        }
    }
}