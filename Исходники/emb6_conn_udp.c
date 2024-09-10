int conn_udp_getlocaladdr(conn_udp_t *conn, void *addr, uint16_t *port)
{
    if (conn->sock.input_callback != NULL) {
        mutex_lock(&conn->mutex);
        memset(addr, 0, sizeof(ipv6_addr_t));
        *port = NTOHS(conn->sock.udp_conn->lport);
        mutex_unlock(&conn->mutex);
        return sizeof(ipv6_addr_t);
    }
    return -EBADF;
}