int
ttl_io(SCARDHANDLE card, DWORD protocol, struct c_apdu *c_apdu, struct r_apdu *r_apdu) {
    LONG rc;
    SCARD_IO_REQUEST send_io_req, recv_io_req;
    BYTE send_buf[256 + 5], recv_buf[NELEMS(send_buf)];
    DWORD send_buf_len, recv_buf_len;
    
    if (protocol != SCARD_PROTOCOL_T0) {
        fprintf(stderr, "only T0 protocol is currently supported");
        return -1;
    }
    
    memset(&send_io_req, 0, sizeof(send_io_req));
    memset(&recv_io_req, 0, sizeof(recv_io_req));
    memset(send_buf, 0, sizeof(send_buf));
    memset(recv_buf, 0, sizeof(recv_buf));
    send_buf_len = recv_buf_len = 0;
    
    if (c_apdu->body.len == -1) {
        memcpy(send_buf, c_apdu, 4);
        send_buf_len = 4;
    } else {
        memcpy(send_buf, c_apdu, 4);
        send_buf[4] = (BYTE) c_apdu->body.len;
        memcpy(send_buf + 5, c_apdu->body.data, c_apdu->body.len);
        send_buf_len = 4 + 1 + c_apdu->body.len;
    }
    
    recv_buf_len = 2;
    if (c_apdu->body.max_r_len > 0)
        recv_buf_len += c_apdu->body.max_r_len;
    
    fprintf(stderr, "calling SCardTransmit\n");
    if ((rc = SCardTransmit(card, protocol == SCARD_PROTOCOL_T0 ? SCARD_PCI_T0 : SCARD_PCI_T1, send_buf, send_buf_len, NULL, recv_buf, &recv_buf_len)) != SCARD_S_SUCCESS) {
        fprintf(stderr, "SCardTransmit failed with code %d\n", rc);
        return -1;
    }
    
    memcpy(r_apdu, recv_buf + recv_buf_len - 2, 2);
    if (recv_buf_len > 2) {
        memcpy(r_apdu->body.data, recv_buf, recv_buf_len - 2);
        r_apdu->body.len = recv_buf_len - 2;

    } else {
        r_apdu->body.len = -1;
    }
    
    return 0;  
}