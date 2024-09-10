int bluetooth_read(int fd, __ptr_t bytes, int size, struct gn_statemachine *state)
{
	return recv((SOCKET)fd, bytes, size, 0);
}