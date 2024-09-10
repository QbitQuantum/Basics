int pcmcia_get_next_tuple(client_handle_t handle, tuple_t *tuple)
{
	struct pcmcia_socket *s;
	if (CHECK_HANDLE(handle))
		return CS_BAD_HANDLE;
	s = SOCKET(handle);
	return pccard_get_next_tuple(s, handle->Function, tuple);
}