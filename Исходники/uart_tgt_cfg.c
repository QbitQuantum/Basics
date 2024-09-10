/**
  *  @brief open serial port
  *
  *  @param
  *  @return
  */
static int serial_open(char *dev)
{
	struct ipmi_msg req = {0};

	req.union_app_req.serial.serial_flag = IPMI_SERIAL_OPEN_DEV;
	req.netfn = OEM_IPMI_NETFN;
	req.cmd   = OEM_SERIAL_OPEN_CMD;

	memcpy_s(req.data, sizeof(req.data), dev, strnlen_s(dev, RSIZE_MAX_STR));

	req.data_len = strnlen_s(dev, RSIZE_MAX_STR);

	libipmi_serial_cmd(&req, serial_open_resp_handler, NULL);

	return 0;
}