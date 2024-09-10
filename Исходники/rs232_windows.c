static unsigned int
port_buffers(struct rs232_port_t *p, unsigned int rb, unsigned int wb)
{
	struct rs232_windows_t *wx = p->pt;

	DBG("p=%p p->pt=%p rb=%d wb=%d\n", (void *)p, p->pt, rb, wb);

	if (!rs232_port_open(p))
		return RS232_ERR_PORT_CLOSED;

	if (!SetupComm(wx->fd, rb, wb)) {
		DBG("SetupComm() %s\n", last_error());
		return RS232_ERR_UNKNOWN;
	}

	wx->r_buffer = rb;
	wx->w_buffer = wb;

	return RS232_ERR_NOERROR;
}