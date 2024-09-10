/**
 * rmnet_init() - Module initialization
 *
 * todo: check for (and init) startup errors
 */
static int __init rmnet_init(void)
{
	rmnet_config_init();
	rmnet_vnd_init();

	LOGL("%s", "RMNET Data driver loaded successfully");
	return 0;
}