status_t
BPrivate::send_request_to_launch_daemon(KMessage& request, KMessage& reply)
{
	status_t status = request.SendTo(get_launch_daemon_port(),
		B_PREFERRED_TOKEN, &reply);
	if (status != B_OK)
		return status;

	return (status_t)reply.What();
}