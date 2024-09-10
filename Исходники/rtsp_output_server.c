static void rtsp_ginfo_print(rtsp_server_config *config)
{
	PRINTF("rtsp_ginfo_print: config= %p\n", config);
	PRINTF("s_port=%d,active=%d,s_mtu=%d,mult_flag=%d,ip=%s:%d\n", config->s_port, config->active, config->s_mtu, config->mult_flag, config->mult_ip, config->mult_port);
}