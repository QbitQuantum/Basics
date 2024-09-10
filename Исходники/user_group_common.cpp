status_t
BPrivate::send_authentication_request_to_registrar(KMessage& request,
	KMessage& reply)
{
	status_t error = request.SendTo(get_registrar_authentication_port(), 0,
		&reply);
	if (error != B_OK)
		return error;

	return (status_t)reply.What();
}