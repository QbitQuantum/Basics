static int me6000_dio_io_single_write(me_subdevice_t * subdevice,
				      struct file *filep,
				      int channel,
				      int value, int time_out, int flags)
{
	me6000_dio_subdevice_t *instance;
	int err = ME_ERRNO_SUCCESS;
	uint8_t mode;
	uint8_t byte;

	PDEBUG("executed.\n");

	instance = (me6000_dio_subdevice_t *) subdevice;

	ME_SUBDEVICE_ENTER spin_lock(&instance->subdevice_lock);
	spin_lock(instance->ctrl_reg_lock);
	switch (flags) {
	case ME_IO_SINGLE_TYPE_DIO_BIT:
		if ((channel >= 0) && (channel < 8)) {
			mode =
			    inb(instance->
				ctrl_reg) & ((ME6000_DIO_CTRL_BIT_MODE_0 |
					      ME6000_DIO_CTRL_BIT_MODE_1) <<
					     (instance->dio_idx * 2));

			if (mode ==
			    (ME6000_DIO_CTRL_BIT_MODE_0 <<
			     (instance->dio_idx * 2))) {
				byte = inb(instance->port_reg) & 0x00FF;

				if (value)
					byte |= 0x1 << channel;
				else
					byte &= ~(0x1 << channel);

				outb(byte, instance->port_reg);
			} else {
				PERROR("Port not in output or input mode.\n");
				err = ME_ERRNO_PREVIOUS_CONFIG;
			}
		} else {
			PERROR("Invalid bit number specified.\n");
			err = ME_ERRNO_INVALID_CHANNEL;
		}
		break;

	case ME_IO_SINGLE_NO_FLAGS:
	case ME_IO_SINGLE_TYPE_DIO_BYTE:
		if (channel == 0) {
			mode =
			    inb(instance->
				ctrl_reg) & ((ME6000_DIO_CTRL_BIT_MODE_0 |
					      ME6000_DIO_CTRL_BIT_MODE_1) <<
					     (instance->dio_idx * 2));

			if (mode ==
			    (ME6000_DIO_CTRL_BIT_MODE_0 <<
			     (instance->dio_idx * 2))) {
				outb(value, instance->port_reg);
			} else {
				PERROR("Port not in output or input mode.\n");
				err = ME_ERRNO_PREVIOUS_CONFIG;
			}
		} else {
			PERROR("Invalid byte number specified.\n");
			err = ME_ERRNO_INVALID_CHANNEL;
		}
		break;

	default:
		PERROR("Invalid flags specified.\n");
		err = ME_ERRNO_INVALID_FLAGS;
	}
	spin_unlock(instance->ctrl_reg_lock);
	spin_unlock(&instance->subdevice_lock);

	ME_SUBDEVICE_EXIT;

	return err;
}