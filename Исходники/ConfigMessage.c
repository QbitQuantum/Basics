static void process_firmware_upload_init(uint8_t sock, Remote_Info *remote_info, WIZnet_Header *wiznet_header)
{
    S2E_Packet *value = get_S2E_Packet_pointer();
    struct __network_info_common tmp;
    uint16_t len;
    WIZnet_Firmware_Upload_Init firmware_upload;
    uint8_t buffer[sizeof(WIZnet_Header) + sizeof(WIZnet_Firmware_Upload_Done_Reply)];
    uint32_t ptr;
    WIZnet_Firmware_Upload_Init_Reply reply;
    Firmware_Upload_Info firmware_upload_info;
    S2E_Packet *s2e_packet = get_S2E_Packet_pointer();
    uint8_t ip[4];
    uint16_t port;

    getsockopt(sock, SO_REMAINSIZE, &len);
    if(len != wiznet_header->length)
        return;

    recvfrom(sock, (uint8_t *)&firmware_upload, sizeof(WIZnet_Firmware_Upload_Init), ip, &port);

    if(wiznet_header->op_code[0] != FIRMWARE_UPLOAD_INIT)
        return;

    if((wiznet_header->valid & 0x80))
        decrypt((wiznet_header->valid & 0x7F), (uint8_t *)&firmware_upload, len);

    if(memcmp(firmware_upload.dst_mac_address, s2e_packet->network_info_common.mac, 6))
        return;

    if(strcmp((char *)firmware_upload.set_pw, (char *)s2e_packet->options.pw_setting))
        return;

    /* Storee Current Network Information (For DHCP) */
    memcpy(&tmp, &(value->network_info_common), sizeof(struct __network_info_common));
    load_S2E_Packet_from_storage();
    memcpy(&(value->network_info_common), &tmp, sizeof(struct __network_info_common));
    save_S2E_Packet_to_storage();

    //write the TFTP server ip, port, filename and etc. to storage
    memcpy(&firmware_upload_info.wiznet_header                , wiznet_header                            , sizeof(WIZnet_Header));
    memcpy(&firmware_upload_info.configtool_info              , remote_info                              , sizeof(Remote_Info));
    memcpy(firmware_upload_info.tftp_info.ip                  , (uint8_t *) (firmware_upload.server_ip)  , sizeof(uint8_t)*4);
    memcpy((uint8_t *)&(firmware_upload_info.tftp_info.port)  , (uint8_t *)&(firmware_upload.server_port), sizeof(uint8_t)*2);
    memcpy(firmware_upload_info.filename                      , (uint8_t *) (firmware_upload.file_name)  , sizeof(uint8_t)*50);
    write_storage(0, &firmware_upload_info, sizeof(Firmware_Upload_Info));

    // reply
    wiznet_header->length = sizeof(WIZnet_Firmware_Upload_Init_Reply);
    wiznet_header->op_code[1] = WIZNET_REPLY;

    memcpy(reply.src_mac_address, s2e_packet->network_info_common.mac, 6);

    if((wiznet_header->valid & 0x80))
        encrypt((wiznet_header->valid & 0x7F), (uint8_t *)&reply, sizeof(WIZnet_Firmware_Upload_Init_Reply));

    ptr = 0;
    memcpy(buffer, wiznet_header, sizeof(WIZnet_Header));
    ptr += sizeof(WIZnet_Header);
    memcpy(buffer + ptr, (void *)&reply, sizeof(WIZnet_Firmware_Upload_Init_Reply));
    ptr += sizeof(WIZnet_Firmware_Upload_Init_Reply);

    if(wiznet_header->unicast == 0) {
        memset(remote_info->ip, 255, 4);
    }
    sendto(sock, buffer, ptr, remote_info->ip, remote_info->port);

    // Reboot to bootloader
    NVIC_SystemReset();
}