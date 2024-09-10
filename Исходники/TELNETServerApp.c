/** Initialization function for the simple TELNET webserver. */
void TELNETServerApp_Init(void)
{
	/* Listen on port 23 for TELNET connections from hosts */
	uip_listen(HTONS(TELNET_SERVER_PORT));
}