/* Caller must hold the device mutex. */
int kgsl_pwrctrl_sleep(struct kgsl_device *device)
{
	int status = 0;
	KGSL_PWR_INFO(device, "sleep device %d\n", device->id);

	/* Work through the legal state transitions */
	switch (device->requested_state) {
	case KGSL_STATE_NAP:
		if (device->pwrctrl.restore_slumber) {
			kgsl_pwrctrl_request_state(device, KGSL_STATE_NONE);
			break;
		}
		status = _nap(device);
		break;
	case KGSL_STATE_SLEEP:
		if (device->pwrctrl.restore_slumber)
			status = _slumber(device);
		else
			status = _sleep(device);
		break;
	case KGSL_STATE_SLUMBER:
		status = _slumber(device);
		break;
	default:
		KGSL_PWR_INFO(device, "bad state request 0x%x\n",
				device->requested_state);
		kgsl_pwrctrl_request_state(device, KGSL_STATE_NONE);
		status = -EINVAL;
		break;
	}
	return status;
}