/*
 * Read from serial, when we have a packet write it to tun. No output
 * buffering, input buffered by stdio.
 */
void
serial_to_tun(FILE *inslip, int outfd)
{
    static union {
        unsigned char inbuf[2000];
        struct ip iphdr;
    } uip;
    static int inbufptr = 0;

    int ret;
    unsigned char c;

#ifdef linux
    ret = fread(&c, 1, 1, inslip);

    if (ret == -1 || ret == 0) {
        err(1, "serial_to_tun: read");
    }

    goto after_fread;
#endif

read_more:

    if (inbufptr >= sizeof(uip.inbuf)) {
        inbufptr = 0;
    }

    ret = fread(&c, 1, 1, inslip);
#ifdef linux
after_fread:
#endif

    if (ret == -1) {
        err(1, "serial_to_tun: read");
    }

    if (ret == 0) {
        clearerr(inslip);
        return;
        fprintf(stderr, "serial_to_tun: EOF\n");
        exit(1);
    }

    /*  fprintf(stderr, ".");*/
    switch (c) {
        case SLIP_END:
            if (inbufptr > 0) {
                /*
                 * Sanity checks.
                 */
#define DEBUG_LINE_MARKER '\r'
                int ecode;
                ecode = check_ip(&uip.iphdr, inbufptr);

                if (ecode < 0 && inbufptr == 8 && strncmp(uip.inbuf, "=IPA", 4) == 0) {
                    static struct in_addr ipa;

                    inbufptr = 0;

                    if (memcmp(&ipa, &uip.inbuf[4], sizeof(ipa)) == 0) {
                        break;
                    }

                    /* New address. */
                    if (ipa.s_addr != 0) {
#ifdef linux
                        ssystem("route delete -net %s netmask %s dev %s",
                                inet_ntoa(ipa), "255.255.255.255", tundev);
#else
                        ssystem("route delete -net %s -netmask %s -interface %s",
                                inet_ntoa(ipa), "255.255.255.255", tundev);
#endif
                    }

                    memcpy(&ipa, &uip.inbuf[4], sizeof(ipa));

                    if (ipa.s_addr != 0) {
#ifdef linux
                        ssystem("route add -net %s netmask %s dev %s",
                                inet_ntoa(ipa), "255.255.255.255", tundev);
#else
                        ssystem("route add -net %s -netmask %s -interface %s",
                                inet_ntoa(ipa), "255.255.255.255", tundev);
#endif
                    }

                    break;
                }
                else if (ecode < 0) {
                    /*
                     * If sensible ASCII string, print it as debug info!
                     */
                    if (uip.inbuf[0] == DEBUG_LINE_MARKER) {
                        fwrite(uip.inbuf + 1, inbufptr - 1, 1, stderr);
                    }
                    else if (is_sensible_string(uip.inbuf, inbufptr)) {
                        fwrite(uip.inbuf, inbufptr, 1, stderr);
                    }
                    else {
                        fprintf(stderr,
                                "serial_to_tun: drop packet len=%d ecode=%d\n",
                                inbufptr, ecode);
                    }

                    inbufptr = 0;
                    break;
                }

                PROGRESS("s");

                if (dhsock != -1) {
                    struct ip *ip = (void *)uip.inbuf;

                    if (ip->ip_p == 17 && ip->ip_dst == 0xffffffff /* UDP and broadcast */
                        && ip->uh_sport == ntohs(BOOTPC) && ip->uh_dport == ntohs(BOOTPS)) {
                        relay_dhcp_to_server(ip, inbufptr);
                        inbufptr = 0;
                    }
                }

                if (write(outfd, uip.inbuf, inbufptr) != inbufptr) {
                    err(1, "serial_to_tun: write");
                }

                inbufptr = 0;
            }

            break;

        case SLIP_ESC:
            if (fread(&c, 1, 1, inslip) != 1) {
                clearerr(inslip);
                /* Put ESC back and give up! */
                ungetc(SLIP_ESC, inslip);
                return;
            }

            switch (c) {
                case SLIP_ESC_END:
                    c = SLIP_END;
                    break;

                case SLIP_ESC_ESC:
                    c = SLIP_ESC;
                    break;
            }

            /* FALLTHROUGH */
        default:
            uip.inbuf[inbufptr++] = c;
            break;
    }

    goto read_more;
}