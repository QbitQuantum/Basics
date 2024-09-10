int vfc_init_i2c_bus(struct vfc_dev *dev)
{
	WRITE_S1(ENABLE_SERIAL | SELECT(S0) | ACK);
	vfc_i2c_reset_bus(dev);
	return 0;
}