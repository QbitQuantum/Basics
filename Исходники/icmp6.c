/**@brief Function for notifying application of the ICMPv6 received packet.
 *
 * @param[in]   p_interface    Pointer to external interface from which packet come.
 * @param[in]   p_pbuffer      Pointer to packet buffer of ICMP6_PACKET_TYPE.
 * @param[in]   process_result Result of internal processing packet.
 *
 * @return      NRF_SUCCESS after successful processing, error otherwise. 
 */
static uint32_t app_notify_icmp_data(iot_interface_t  * p_interface, 
                                 iot_pbuffer_t    * p_pbuffer,
                                 uint32_t           process_result)
{
    uint32_t err_code = NRF_SUCCESS;

    if(m_event_handler != NULL)
    {

       ipv6_header_t  * p_ip_header   = (ipv6_header_t *)
                               (p_pbuffer->p_payload - ICMP6_HEADER_SIZE - IPV6_IP_HEADER_SIZE);
       icmp6_header_t * p_icmp_header = (icmp6_header_t *)
                               (p_pbuffer->p_payload - ICMP6_HEADER_SIZE);

        ICMP6_MUTEX_UNLOCK();
        
        // Change byte order of ICMP header given to application.
        p_icmp_header->checksum = NTOHS(p_icmp_header->checksum);

        err_code = m_event_handler(p_interface,
                                   p_ip_header,
                                   p_icmp_header,
                                   process_result,
                                   p_pbuffer);

        ICMP6_MUTEX_LOCK();
    }

    return err_code;
}