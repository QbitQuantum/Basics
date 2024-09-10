void rpl_process(void)
{
    msg_t m_recv;
    msg_init_queue(msg_queue, RPL_PKT_RECV_BUF_SIZE);

    while (1) {
        msg_receive(&m_recv);
        uint8_t *code;
        code = ((uint8_t *)m_recv.content.ptr);
        /* differentiate packet types */
        ipv6_buf = ipv6_get_buf();
        memcpy(&rpl_buffer, ipv6_buf, NTOHS(ipv6_buf->length) + IPV6_HDR_LEN);
        DEBUG("%s, %d: Reveived RPL information of type %04X\n", __FILE__, __LINE__, *code);

        switch (*code) {
            case (ICMP_CODE_DIS): {
                recv_rpl_dis();
                mutex_unlock(&rpl_recv_mutex);
                break;
            }

            case (ICMP_CODE_DIO): {
                recv_rpl_dio();
                mutex_unlock(&rpl_recv_mutex);
                break;
            }

            case (ICMP_CODE_DAO): {
                recv_rpl_dao();
                mutex_unlock(&rpl_recv_mutex);
                break;
            }

            case (ICMP_CODE_DAO_ACK): {
                recv_rpl_dao_ack();
                mutex_unlock(&rpl_recv_mutex);
                break;
            }

            default:
                mutex_unlock(&rpl_recv_mutex);
                break;
        }
    }
}