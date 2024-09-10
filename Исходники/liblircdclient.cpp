int CLircdClient::SendOnce(string device, string key)
{
	return Send("SEND_ONCE",device,key);
}