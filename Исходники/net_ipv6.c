int net_ipv6_send(netif_t *net, const uint8 *data, size_t data_size,
                  int hop_limit, int proto, const struct in6_addr *src,
                  const struct in6_addr *dst) {
    ipv6_hdr_t hdr;

    if(!net) {
        net = net_default_dev;

        if(!net) {
            errno = ENETDOWN;
            return -1;
        }
    }

    /* Set up the hop limit. We need to do this here, in case we end up passing
       this off to the IPv4 code, otherwise we could end up with a 0 down there
       for the ttl, which would be bad. */
    if(!hop_limit) {
        if(net->hop_limit)
            hop_limit = net->hop_limit;
        else
            hop_limit = 255;
    }

    /* If this is actually going both to and from an IPv4 address, use the IPv4
       send function to do the rest. Note that only V4-mapped addresses are
       supported here (::ffff:x.y.z.w) */
    if(IN6_IS_ADDR_V4MAPPED(src) && IN6_IS_ADDR_V4MAPPED(dst)) {
        return net_ipv4_send(net, data, data_size, -1, hop_limit, proto,
                             src->__s6_addr.__s6_addr32[3],
                             dst->__s6_addr.__s6_addr32[3]);
    }
    else if(IN6_IS_ADDR_V4MAPPED(src) || IN6_IS_ADDR_V4MAPPED(dst) ||
            IN6_IS_ADDR_V4COMPAT(src) || IN6_IS_ADDR_V4COMPAT(dst)) {
        return -1;
    }

    hdr.version_lclass = 0x60;
    hdr.hclass_lflow = 0;
    hdr.lclass = 0;
    hdr.length = ntohs(data_size);
    hdr.next_header = proto;
    hdr.hop_limit = hop_limit;
    hdr.src_addr = *src;
    hdr.dst_addr = *dst;

    /* XXXX: Handle fragmentation... */
    return net_ipv6_send_packet(net, &hdr, data, data_size);
}