int me8254_io_single_read(struct me_subdevice* subdevice, struct file* filep, int channel, int* value, int time_out, int flags)
{
	me8254_subdevice_t* instance;
	uint8_t ctrl = ME8254_CTRL_TLO;
	uint8_t lo_byte = 0;
	uint8_t hi_byte = 0;
	uint8_t status_byte = 0;
	int err = ME_ERRNO_SUCCESS;

	PDEBUG("executed.\n");

	if (flags)
	{
		PERROR("Invalid flags specified. Must be ME_IO_SINGLE_TYPE_NO_FLAGS.\n");
		return ME_ERRNO_INVALID_FLAGS;
	}

	if (channel)
	{
		PERROR("Invalid channel. Must be 0.\n");
		return ME_ERRNO_INVALID_CHANNEL;
	}

	instance = (me8254_subdevice_t *) subdevice;

	ME_SUBDEVICE_ENTER;
		ME_SUBDEVICE_LOCK;
			ME_SPIN_LOCK(instance->ctrl_reg_lock);
				switch (instance->ctr_idx)
				{
					case 0:
						ctrl |= ME8254_CTRL_SC0;
						break;

					case 1:
						ctrl |= ME8254_CTRL_SC1;
						break;

					default:
						ctrl |= ME8254_CTRL_SC2;
				}
				me_writeb(instance->base.dev, ME8254_STATUS_CMD | (0x2 << instance->ctr_idx), instance->ctrl_reg);
				me_readb(instance->base.dev, &status_byte, instance->val_reg);
				if (status_byte & 0x40)
				{
					PINFO("NULL count detected.\n");
					err = ME_ERRNO_SUBDEVICE_NOT_RUNNING;
					goto EXIT;
				}

				me_writeb(instance->base.dev, ctrl, instance->ctrl_reg);

				me_readb(instance->base.dev, &lo_byte, instance->val_reg);
				me_readb(instance->base.dev, &hi_byte, instance->val_reg);
EXIT:
			ME_SPIN_UNLOCK(instance->ctrl_reg_lock);

			*value = (int)lo_byte | ((int)hi_byte << 8);
		ME_SUBDEVICE_UNLOCK;
	ME_SUBDEVICE_EXIT;

	return err;
}