static void
parse_set_tunnel(struct ofpbuf *b, const char *arg)
{
    uint64_t tun_id = str_to_u64(arg);
    if (tun_id > UINT32_MAX) {
        ofputil_put_NXAST_SET_TUNNEL64(b)->tun_id = htonll(tun_id);
    } else {
        ofputil_put_NXAST_SET_TUNNEL(b)->tun_id = htonl(tun_id);
    }
}