int
libcfs_ipif_query (char *name, int *up, __u32 *ip, __u32 *mask)
{
        struct ifreq    ifr;
        socket_t        so;
        __u32           val;
        int             nob;
        int             rc;

        rc = -sock_socket(PF_INET, SOCK_STREAM, 0, 
                          NULL, NULL, &so);
        if (rc != 0) {
                CERROR ("Can't create socket: %d\n", rc);
                return rc;
        }

        nob = strnlen(name, IFNAMSIZ);
        if (nob == IFNAMSIZ) {
                CERROR("Interface name %s too long\n", name);
                rc = -EINVAL;
                goto out;
        }

        CLASSERT (sizeof(ifr.ifr_name) >= IFNAMSIZ);
        bzero(&ifr, sizeof(ifr));
        strcpy(ifr.ifr_name, name);
        rc = -sock_ioctl (so, SIOCGIFFLAGS, &ifr);

        if (rc != 0) {
                CERROR("Can't get flags for interface %s\n", name);
                goto out;
        }
        
        if ((ifr.ifr_flags & IFF_UP) == 0) {
                CDEBUG(D_NET, "Interface %s down\n", name);
                *up = 0;
                *ip = *mask = 0;
                goto out;
        }

        *up = 1;

        bzero(&ifr, sizeof(ifr));
        strcpy(ifr.ifr_name, name);
        *((struct sockaddr_in *)&ifr.ifr_addr) = blank_sin();
        rc = -sock_ioctl(so, SIOCGIFADDR, &ifr);

        if (rc != 0) {
                CERROR("Can't get IP address for interface %s\n", name);
                goto out;
        }
        
        val = ((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr.s_addr;
        *ip = ntohl(val);

        bzero(&ifr, sizeof(ifr));
        strcpy(ifr.ifr_name, name);
        *((struct sockaddr_in *)&ifr.ifr_addr) = blank_sin();
        rc = -sock_ioctl(so, SIOCGIFNETMASK, &ifr);

        if (rc != 0) {
                CERROR("Can't get netmask for interface %s\n", name);
                goto out;
        }

        val = ((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr.s_addr;
        *mask = ntohl(val);
out:
        sock_close(so);
        return rc;
}