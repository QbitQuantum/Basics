olibc_retval_t
olibc_pak_send (olibc_pak_hdl pak_hdl,  int fd, uint32_t offset_bytes)
{
    char *data_buff = NULL;
    struct iovec iov;
    struct msghdr smsghdr;
    struct cmsghdr *scmsgp;
    uint32_t msg_controllen = 0;
    u_char cmsgbuf4[CMSG_SPACE((int)sizeof(struct in_pktinfo))];
    u_char cmsgbuf6[CMSG_SPACE((int)sizeof(struct in6_pktinfo))];
    uint32_t data_sent = 0;

    memset(&smsghdr, 0, sizeof(smsghdr)); 
    memset(&iov, 0, sizeof(iov));
    memset(cmsgbuf4, 0, CMSG_SPACE(sizeof(struct in_pktinfo)));
    memset(cmsgbuf6, 0, CMSG_SPACE(sizeof(struct in6_pktinfo)));

    if (!pak_hdl || (fd < 0 )) {
        olibc_log_error("\nInvalid input");
        return OLIBC_RETVAL_INVALID_INPUT;
    }

    if (pak_hdl->data_set_flags & OLIBC_DST_SOCKADDR_SET) {
        smsghdr.msg_name = (caddr_t) &pak_hdl->dst_sock_addr;
        if (pak_hdl->dst_sock_addr.ss_family == AF_INET) {
            smsghdr.msg_namelen = sizeof(struct sockaddr_in);
        }
         
        if (pak_hdl->dst_sock_addr.ss_family == AF_INET6) {
            smsghdr.msg_namelen = sizeof(struct sockaddr_in6);
            if (pak_hdl->data_set_flags & OLIBC_OUT_IFHNDL_SET) {
                struct sockaddr_in6 *s6 = (struct sockaddr_in6 *)
                    &pak_hdl->dst_sock_addr;
                s6->sin6_scope_id = pak_hdl->out_ifindex;
            }
        }
    }
            
    if (pak_hdl->data_set_flags & 
        (OLIBC_OUT_IFHNDL_SET | OLIBC_SRC_SOCKADDR_SET)) {
        if (pak_hdl->addr_family == AF_INET) {
            scmsgp = (struct cmsghdr *)cmsgbuf4;
            scmsgp->cmsg_level = IPPROTO_IP;
            scmsgp->cmsg_type = IP_PKTINFO;
            scmsgp->cmsg_len = CMSG_LEN(sizeof(struct in_pktinfo));
            msg_controllen = CMSG_SPACE(sizeof(struct in_pktinfo));

        } else if (pak_hdl->addr_family == AF_INET6) {
            struct in6_pktinfo *dst_in6_pkt_info = NULL;
            
            scmsgp = (struct cmsghdr *)cmsgbuf6;

            scmsgp->cmsg_level = IPPROTO_IPV6;
            scmsgp->cmsg_type = IPV6_PKTINFO;
            scmsgp->cmsg_len = CMSG_LEN(sizeof(struct in6_pktinfo));
            msg_controllen = CMSG_SPACE(sizeof(struct in6_pktinfo));

            dst_in6_pkt_info = (struct in6_pktinfo *)CMSG_DATA(scmsgp);
            dst_in6_pkt_info->ipi6_ifindex = pak_hdl->out_ifindex;

            if (pak_hdl->data_set_flags & OLIBC_SRC_SOCKADDR_SET) { 
                struct sockaddr_in6 *s6 = 
                    (struct sockaddr_in6 *)&pak_hdl->dst_sock_addr;
                memcpy(&dst_in6_pkt_info->ipi6_addr, &s6->sin6_addr,
                       sizeof(struct in6_addr)); 
            }

            if (pak_hdl->data_set_flags & OLIBC_OUT_IFHNDL_SET) {
                if (setsockopt(fd, IPPROTO_IPV6, IPV6_MULTICAST_IF, &pak_hdl->out_ifindex,
                            sizeof(pak_hdl->out_ifindex)) < 0) {
                    olibc_log_error("\nFailed to set IPv6 Out IfIndex");
                    return OLIBC_RETVAL_FAILED;
                }
            }
        }
    }


    data_buff =  pak_hdl->data_buf + offset_bytes;
    iov.iov_base = data_buff;
    iov.iov_len = pak_hdl->data_length - offset_bytes;

    smsghdr.msg_iov = &iov;
    smsghdr.msg_iovlen = 1;
    smsghdr.msg_controllen = msg_controllen;
    if (msg_controllen) { 
        smsghdr.msg_control = (caddr_t) scmsgp;
    }

    data_sent = sendmsg(fd, &smsghdr, 0);
    if (data_sent != iov.iov_len) {
        olibc_log_error("\nFailed to send data %d - %d", 
                (int)iov.iov_len, data_sent);
        return OLIBC_RETVAL_FAILED;
    }

    return OLIBC_RETVAL_SUCCESS;
}