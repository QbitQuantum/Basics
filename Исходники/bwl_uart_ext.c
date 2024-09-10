void uart_send_int(unsigned char port,int val)
{
	itoa(val,uart_send_buffer,10);
	uart_send_string(port,uart_send_buffer);
}