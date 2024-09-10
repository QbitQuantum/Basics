// obs³u¿ pakiet
void udp_config_handle_packet(unsigned char* data, unsigned int len) {

    // otrzymany pakiet
    udp_config_packet *packet = (udp_config_packet*) data;

    // ignoruj niepoprawne pakiety
    if (packet->start != UDP_CONFIG_MAGIC) {
        return;
    }

    // ignoruj pakiety z ustawionym adresem MAC innego urz¹dzenia
    if (memcmp(packet->mac, nic_get_mac(), 6) != 0) {
        // MAC niezgodny, sprawdŸ czy nie ustawiono adresu broadcast MAC (ff:ff:ff:ff:ff:ff)
        for (i=0; i<6; i++) {
            if (packet->mac[i] != 0xFF) {
                return;
            }
        }
    }

    switch(packet->type) {

        // wyszukiwanie urz¹dzeñ
        case UDP_CONFIG_TYPE_DISCOVERY:
            // wyszukiwanie okreœlonego typu urz¹dzeñ
            if ( (packet->length == 1) && (packet->data[0] != UDP_CONFIG_DEVICE_TYPE) ) {
                // szukany inny typ urz¹dzenia
                return;
            }

            // formuj pakiet
            packet->type = UDP_CONFIG_TYPE_MY_CONFIG;
            len = udp_config_fill(packet->data);
            
            break;

        // identyfikacja wybranego urz¹dzenia
        case UDP_CONFIG_TYPE_IDENTIFY:
            // mrugaj naprzemiennie diodami RX/TX przez 3 sekundy
            udp_identify_timer = 30;

            packet->type = UDP_CONFIG_TYPE_IDENTIFY_OK;
            len = 0;
            break;

        // niepoprawny typ
        default:
            return;
    }

    // odeœlij pakiet
    struct uip_udp_conn* conn;
    conn = uip_udp_new(&uip_udp_conn->ripaddr, uip_udp_conn->rport);

    if (!conn) {
        return;
    }

    // wyœlij z portu, na którym pakiet zosta³ odebrany
    uip_udp_bind(conn, HTONS(UDP_CONFIG_PORT));

    // nag³ówek    
    packet->start = UDP_CONFIG_MAGIC;
    packet->length = len;

    // nadawca
    memcpy(packet->mac, nic_get_mac(), 6);

    // wyœlij
    uip_udp_send(len + 10);

    // czekaj na wys³anie
    nic_wait_for_send();

    // zamknij po³¹czenia UDP (przychodz¹cy broadcast i wychodz¹cy unicast)
    uip_udp_remove(conn);
    uip_udp_remove(uip_udp_conn);
}