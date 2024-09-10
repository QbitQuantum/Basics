int tls_cmd_create_ibss_net( void )
{
	u8 ret=0;
#if TLS_CONFIG_IBSS
	struct tls_ibss_info_t* ibssinfo;
	struct tls_ibssip_info_t* ipinfo;
	struct tls_cmd_ssid_t ssid;
	struct tls_cmd_ip_params_t ip_addr;
	u8 channel_en;

	ibssinfo = tls_mem_alloc(sizeof(struct tls_softap_info_t));
	if(ibssinfo == NULL)
		return CMD_ERR_MEM;
	ipinfo = tls_mem_alloc(sizeof(struct tls_ip_info_t));
	if(ipinfo == NULL){
		tls_mem_free(ibssinfo);
		return CMD_ERR_MEM;
	}
		
	tls_cmd_get_ssid(&ssid);
	MEMCPY(ibssinfo->ssid, ssid.ssid, ssid.ssid_len);
	ibssinfo->ssid[ssid.ssid_len] = '\0';
	
	tls_cmd_get_encrypt( &ibssinfo->encrypt);
	
	tls_cmd_get_channel( &ibssinfo->channel, &channel_en);

	tls_cmd_get_key((struct tls_cmd_key_t *)(&ibssinfo->keyinfo));

	tls_cmd_get_ip_info(&ip_addr);

	/*ip配置信息:ip地址，掩码，dns名称*/
	MEMCPY(ipinfo->ip, ip_addr.ip_addr, 4);
	MEMCPY(ipinfo->netmask, ip_addr.netmask, 4);
	MEMCPY(ipinfo->gateway, ip_addr.gateway, 4);
	MEMCPY(ipinfo->dns1, ip_addr.dns, 4);
	MEMCPY(ipinfo->dns2, ip_addr.dns, 4);

	ret = tls_wifi_ibss_create(ibssinfo, ipinfo);
	tls_mem_free(ibssinfo);
	tls_mem_free(ipinfo);
#endif	
	return ret;	
}