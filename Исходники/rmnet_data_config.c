/**
 * rmnet_associate_network_device() - Associate network device
 * @dev:      Device to register with RmNet data
 *
 * Typically used on physical network devices. Registers RX handler and private
 * metadata structures.
 *
 * Return:
 *      - RMNET_CONFIG_OK if successful
 *      - RMNET_CONFIG_NO_SUCH_DEVICE dev is null
 *      - RMNET_CONFIG_INVALID_REQUEST if the device to be associated is a vnd
 *      - RMNET_CONFIG_DEVICE_IN_USE if dev rx_handler is already filled
 *      - RMNET_CONFIG_DEVICE_IN_USE if netdev_rx_handler_register() fails
 */
int rmnet_associate_network_device(struct net_device *dev)
{
	struct rmnet_phys_ep_conf_s *config;
	int rc;
	ASSERT_RTNL();

	LOGL("(%s);\n", dev->name);

	if (!dev)
		return RMNET_CONFIG_NO_SUCH_DEVICE;

	if (_rmnet_is_physical_endpoint_associated(dev)) {
		LOGM("%s is already regestered", dev->name);
		return RMNET_CONFIG_DEVICE_IN_USE;
	}

	if (rmnet_vnd_is_vnd(dev)) {
		LOGM("%s is a vnd", dev->name);
		return RMNET_CONFIG_INVALID_REQUEST;
	}

	config = (struct rmnet_phys_ep_conf_s *)
		 kmalloc(sizeof(struct rmnet_phys_ep_conf_s), GFP_ATOMIC);

	if (!config)
		return RMNET_CONFIG_NOMEM;

	memset(config, 0, sizeof(struct rmnet_phys_ep_conf_s));
	config->dev = dev;
	spin_lock_init(&config->agg_lock);

	rc = netdev_rx_handler_register(dev, rmnet_rx_handler, config);

	if (rc) {
		LOGM("netdev_rx_handler_register returns %d", rc);
		kfree(config);
		return RMNET_CONFIG_DEVICE_IN_USE;
	}

	/* Explicitly hold a reference to the device */
	dev_hold(dev);
	trace_rmnet_associate(dev);
	return RMNET_CONFIG_OK;
}