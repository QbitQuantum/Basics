boolean esp8266GetIP(char *buf)
{
	INT8U err;
	char *str;
	boolean result;
	
	result = FALSE;
	esp8266RxBufferFlash();
	usart0Print("AT+CIFSR\r\n");
	while (1) {
		err = usart0Read(&str, ESP8266_SHORT_TIMEOUT);
		if (err == OS_ERR_TIMEOUT || strCmp(str, "OK")) {
			break;
		} else if (*str >= '0' && *str <= '9') {
			if (!strCmp(str, "192.168.4.1")) {
				strCpy(str, buf);
				result = TRUE;
			}
		}
	}
	return result;
}