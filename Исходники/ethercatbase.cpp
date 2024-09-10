/** Close sockets used
* @param[in] port        = port context struct
* @return 0
*/
int ecx_portt::closenic()
{
	timeEndPeriod(15);

	if (this->sockhandle != NULL)
	{
		DeleteCriticalSection(&(this->getindex_mutex));
		DeleteCriticalSection(&(this->tx_mutex));
		DeleteCriticalSection(&(this->rx_mutex));
		pcap_close(this->sockhandle);
		this->sockhandle = NULL;
	}
	if ((this->redport) && (this->redport->sockhandle != NULL))
	{
		pcap_close(this->redport->sockhandle);
		this->redport->sockhandle = NULL;
	}

	return 0;
}