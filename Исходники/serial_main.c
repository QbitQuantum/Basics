static void __serial_check_fds(SERIAL_DEVICE* serial)
{
	IRP* irp;
	IRP* prev;
	SERIAL_TTY* tty;
	UINT32 result = 0;
	BOOL irp_completed = FALSE;

	ZeroMemory(&serial->tv, sizeof(struct timeval));
	tty = serial->tty;

	/* scan every pending */
	irp = list_peek(serial->pending_irps);

	while (irp)
	{
		DEBUG_SVC("MajorFunction %u", irp->MajorFunction);

		switch (irp->MajorFunction)
		{
			case IRP_MJ_READ:
				if (FD_ISSET(tty->fd, &serial->read_fds))
				{
					irp->IoStatus = STATUS_SUCCESS;
					serial_process_irp_read(serial, irp);
					irp_completed = TRUE;
				}
				break;

			case IRP_MJ_WRITE:
				if (FD_ISSET(tty->fd, &serial->write_fds))
				{
					irp->IoStatus = STATUS_SUCCESS;
					serial_process_irp_write(serial, irp);
					irp_completed = TRUE;
				}
				break;

			case IRP_MJ_DEVICE_CONTROL:
				if (serial_tty_get_event(tty, &result))
				{
					DEBUG_SVC("got event result %u", result);

					irp->IoStatus = STATUS_SUCCESS;
					stream_write_UINT32(irp->output, result);
					irp->Complete(irp);
					irp_completed = TRUE;
				}
				break;

			default:
				DEBUG_SVC("no request found");
				break;
		}

		prev = irp;
		irp = (IRP*) list_next(serial->pending_irps, irp);

		if (irp_completed || (prev->IoStatus == STATUS_SUCCESS))
		{
			list_remove(serial->pending_irps, prev);
			SetEvent(serial->in_event);
		}
	}
}