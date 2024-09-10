static void __ipcs_table_updating(
    struct nc_ipcs_table *tbl,
    int *arp_fds,
    int arp_wireless_fd
)
{
    fd_set readfds;
    int maxfd = -1;
    struct timeval timeo;
#define RCV_BUF_SIZE    1400
    char buf[RCV_BUF_SIZE];
    struct sockaddr_ll saddr;
    socklen_t saddr_len;
    int i;
    int ret = -1;

    timeo.tv_sec = NC_ARP_TIMEOUT_INTERVAL;
    timeo.tv_usec = 0;

    while (1)
    {
        FD_ZERO(&readfds);
        maxfd = 0;

        for (i = 0; i < tbl->wire_cnt; ++i)
        {
            st_fds_set(&readfds, arp_fds[i], &maxfd);
        }

        if (tbl->wireless_enable)
        {
            st_fds_set(&readfds, arp_wireless_fd, &maxfd);
        }

        st_fds_set(&readfds, tbl->dhcp_fd, &maxfd);

        ret = select(maxfd + 1, &readfds, NULL, NULL, &timeo);
        if (ret < 0)
        {
            if (errno == EINTR)
            {
                continue;
            }
            st_err("select error:%d\n", errno);
            perror("select ");
            break;
        }

        if (ret == 0)
        {
            timeo.tv_sec = NC_ARP_TIMEOUT_INTERVAL;
            timeo.tv_usec = 0;
            ipcs_table_updating_by_time(tbl);
            ipcs_table_refresh_wire(tbl, arp_fds);
            ipcs_table_refresh_wireless(tbl, arp_wireless_fd);
            continue;
        }

        /*for wire*/
        for (i = 0; i < tbl->wire_cnt; ++i)
        {
            if (FD_ISSET(arp_fds[i], &readfds))
            {
                st_dbg("\n");
                saddr_len = sizeof(saddr);
                memset(&saddr, 0, sizeof(saddr));
                ret = recvfrom(
                          arp_fds[i],
                          buf,
                          RCV_BUF_SIZE,
                          0,
                          (struct sockaddr *)&saddr,
                          &saddr_len
                      );
                if (ret < 0)
                {
                    st_err("recvfrom error:%d!\n", errno);
                    perror("recvfrom");
                    continue;
                }

                ipcs_table_updating_wire_by_arp(tbl, i, buf, ret, &saddr);
            }
        }

        /*for wireless*/
        if (tbl->wireless_enable)
        {
            if (FD_ISSET(arp_wireless_fd, &readfds))
            {
                st_dbg("\n");
                while (1)
                {
                    saddr_len = sizeof(saddr);
                    memset(&saddr, 0, sizeof(saddr));
                    ret = recvfrom(
                              arp_wireless_fd,
                              buf,
                              RCV_BUF_SIZE,
                              MSG_DONTWAIT,
                              (struct sockaddr *)&saddr,
                              &saddr_len
                          );
                    if (ret < 0)
                    {
                        st_dbg("errno = %d\n",errno);
                        if ((errno != EAGAIN) && (errno != EWOULDBLOCK))
                        {
                            st_err("recvfrom error:%d!\n", errno);
                            perror("recvfrom");
                        }
                        break;
                    }

                    ipcs_table_updating_wireless_by_arp(tbl, buf, ret, &saddr);
                }
            }
        }

        if (FD_ISSET(tbl->dhcp_fd, &readfds))
        {
            struct nc_new_info *ipc = NULL;

            while (1)
            {
                ret = recv(tbl->dhcp_fd, buf, RCV_BUF_SIZE, MSG_DONTWAIT);
                if (ret < 0)
                {
                    if ((errno != EAGAIN) && (errno != EWOULDBLOCK))
                    {
                        st_err("recv error:%d!\n", errno);
                        perror("recv");
                    }
                    break;
                }

                if (ret == 0)
                {
                    st_err("fd error, something wrong ...!\n");
                    break;
                }

                ipc = (struct nc_new_info*)buf;
                if (ipc->port_id == (unsigned short)-1)
                {
                    st_dbg("dhcp update:%d,%02x:%02x:%02x:%02x:%02x:%02x\n",
                           ipc->client_ip,(ipc->hwaddr)[0],(ipc->hwaddr)[1],
                           (ipc->hwaddr)[2],(ipc->hwaddr)[3],(ipc->hwaddr)[4],
                           (ipc->hwaddr)[5]);
                    ipcs_table_updating_wireless(tbl, ipc->client_ip, ipc->hwaddr);
                }
                else
                {
                    if ((((short)ipc->port_id) < 0) || (ipc->port_id >= tbl->wire_cnt))
                    {
                        st_err("port_id:%d from dhcp is wrong! range:[0-%d)\n", ipc->port_id, tbl->wire_cnt);
                        abort();
                    }
                    ipcs_table_updating_wire(tbl, ipc->port_id, ipc->client_ip, ipc->hwaddr);
                }
            }
        }
    }
}