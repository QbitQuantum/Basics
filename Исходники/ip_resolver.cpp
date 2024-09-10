int zmq::ip_resolver_t::resolve_nic_name (ip_addr_t *ip_addr_, const char *nic_)
{
    int rc;
    bool found = false;
    const int max_attempts = 10;

    int iterations = 0;
    IP_ADAPTER_ADDRESSES *addresses = NULL;
    IP_ADAPTER_ADDRESSES *current_addresses = NULL;
    unsigned long out_buf_len = sizeof (IP_ADAPTER_ADDRESSES);

    do {
        addresses = static_cast<IP_ADAPTER_ADDRESSES *> (malloc (out_buf_len));
        alloc_assert (addresses);

        rc =
          GetAdaptersAddresses (AF_UNSPEC,
                                GAA_FLAG_SKIP_ANYCAST | GAA_FLAG_SKIP_MULTICAST
                                  | GAA_FLAG_SKIP_DNS_SERVER,
                                NULL, addresses, &out_buf_len);
        if (rc == ERROR_BUFFER_OVERFLOW) {
            free (addresses);
            addresses = NULL;
        } else {
            break;
        }
        iterations++;
    } while ((rc == ERROR_BUFFER_OVERFLOW) && (iterations < max_attempts));

    if (rc == 0) {
        current_addresses = addresses;
        while (current_addresses) {
            char *if_name = NULL;
            char *if_friendly_name = NULL;
            int str_rc1, str_rc2;

            str_rc1 = get_interface_name (current_addresses->IfIndex, &if_name);
            str_rc2 = wchar_to_utf8 (current_addresses->FriendlyName,
                                     &if_friendly_name);

            //  Find a network adapter by its "name" or "friendly name"
            if (((str_rc1 == 0) && (!strcmp (nic_, if_name)))
                || ((str_rc2 == 0) && (!strcmp (nic_, if_friendly_name)))) {
                //  Iterate over all unicast addresses bound to the current network interface
                IP_ADAPTER_UNICAST_ADDRESS *unicast_address =
                  current_addresses->FirstUnicastAddress;
                IP_ADAPTER_UNICAST_ADDRESS *current_unicast_address =
                  unicast_address;

                while (current_unicast_address) {
                    ADDRESS_FAMILY family =
                      current_unicast_address->Address.lpSockaddr->sa_family;

                    if (family == (options.ipv6 () ? AF_INET6 : AF_INET)) {
                        memcpy (
                          ip_addr_, current_unicast_address->Address.lpSockaddr,
                          (family == AF_INET) ? sizeof (struct sockaddr_in)
                                              : sizeof (struct sockaddr_in6));
                        found = true;
                        break;
                    }

                    current_unicast_address = current_unicast_address->Next;
                }

                if (found)
                    break;
            }

            if (str_rc1 == 0)
                free (if_name);
            if (str_rc2 == 0)
                free (if_friendly_name);

            current_addresses = current_addresses->Next;
        }

        free (addresses);
    }

    if (!found) {
        errno = ENODEV;
        return -1;
    }
    return 0;
}