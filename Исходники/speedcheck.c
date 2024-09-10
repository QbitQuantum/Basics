void Curl_speedinit(struct SessionHandle *data)
{
	MEMSET(&data->state.keeps_speed, 0, sizeof(struct timeval));
}