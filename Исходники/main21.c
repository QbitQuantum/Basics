/**
 * \brief Main application function.
 *
 * Application entry point.
 * Initialize board and WINC1500 Wi-Fi module.
 * Read input data from serial interface and sent it to the remote device.
 *
 * \return program return value.
 */
int main(void)
{
	tstrWifiInitParam param;
	int8_t ret;

	/* Initialize the board. */
	system_init();

	/* Initialize the UART console. */
	configure_console();
	printf(STRING_HEADER);

	/* Initialize the BSP. */
	nm_bsp_init();

	/* Initialize Wi-Fi parameters structure. */
	memset((uint8_t *)&param, 0, sizeof(tstrWifiInitParam));

	/* Initialize Wi-Fi driver with data and status callbacks. */
	param.pfAppWifiCb = wifi_cb;
	ret = m2m_wifi_init(&param);
	if (M2M_SUCCESS != ret) {
		printf("main: m2m_wifi_init call error!(%d)\r\n", ret);
		while (1) {
		}
	}

	/* Initialize socket interface. */
	socketInit();
	registerSocketCallback(socket_cb, NULL);

	/* Connect to router. */
	m2m_wifi_connect((char *)MAIN_WLAN_SSID, sizeof(MAIN_WLAN_SSID),
			MAIN_WLAN_AUTH, (char *)MAIN_WLAN_PSK, M2M_WIFI_CH_ALL);

	while (1) {
		if (wifi_connected == M2M_WIFI_CONNECTED && tcp_server_socket < 0) {
			struct sockaddr_in addr;

			/* Create TCP server socket. */
			if ((tcp_server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
				printf("Failed to create TCP server socket!\r\n");
				continue;
			}

			/* Initialize socket address structure and bind service. */
			addr.sin_family = AF_INET;
			addr.sin_port = _htons(MAIN_WIFI_M2M_SERVER_PORT);
			addr.sin_addr.s_addr = 0;
			bind(tcp_server_socket, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
		}

		/* Handle pending events from network controller. */
		m2m_wifi_handle_events(NULL);

		/* Try to read user input from EDBG. */
		usart_read_job(&cdc_uart_module, &uart_ch_buffer);

		/* Handle user message from EDBG. */
		handle_input_message();
	}

	return 0;
}