/* Accept data from an XBee module & build into valid XBEE
 *  packets
 */
void xbee_in(xbee_t *xbee, const void *buf, uint8_t len)
{
    uint8_t *data = (uint8_t *)buf;


    while(len) {
        switch(xbee->in.bytes_rcvd) {
            case 0:
                while (*data != XBEE_PKT_START) {
                    if (!--len)
                        return;
                    data++;
                }

                xbee->in.hdr_data[xbee->in.bytes_rcvd++] = *data++;
                if (!--len)
                    return;

                /* Fall thru */

            case 1:
              xbee->in.hdr_data[xbee->in.bytes_rcvd++] = *data++;
                if (!--len)
                    return;

                /* Fall thru */

            case 2:
              xbee->in.hdr_data[xbee->in.bytes_rcvd++] = *data++;

                /* Got enough to get packet length */

                xbee->in.bytes_left = ntohs(((xbee_pkt_hdr_t *)xbee->in.hdr_data)->len);

                if (xbee->in.bytes_left > XBEE_MAX_DATA_LEN
                    || ((xbee->in.packet 
                              = xbee_alloc_pkt_mem(XBEE_RECV, xbee->in.bytes_left + 4)) == NULL)
                )
                {
                    xbee->in.bytes_left = 0;
                    xbee_rx_err(xbee);
                    continue;
                }

                xbee->in.bytes_left++; /* Extra for crc (alloc_pkt already accounts for it) */

                memcpy(&(xbee->in.packet->hdr), &(xbee->in.hdr_data),
                         sizeof(xbee->in.hdr_data));

                if (!--len)
                    return;

                /* Fall thru */

            default:
                while (xbee->in.bytes_left--) {
                    ((uint8_t *)xbee->in.packet)[xbee->in.bytes_rcvd++] = *data++;
                    if (!--len && xbee->in.bytes_left)
                        return;
                }
        }

        if (xbee_crc(xbee->in.packet) 
                     != ((uint8_t *)xbee->in.packet)[xbee->in.bytes_rcvd - 1])
        {
            xbee->in.bytes_rcvd = 0;
            xbee_rx_crc_err(xbee);
            continue;
        }

        if (xbee_recv_pkt(xbee, xbee->in.packet, xbee->in.bytes_rcvd)) {
            xbee_free_pkt_mem(xbee->in.packet);
            xbee_rx_dropped(xbee);
        }

        xbee->in.bytes_rcvd = 0;
    }
}