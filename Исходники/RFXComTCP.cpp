void RFXComTCP::OnError(const boost::system::error_code& error)
{
	_log.Log(LOG_ERROR, "RFXCOM: Error: %s", error.message().c_str());
}