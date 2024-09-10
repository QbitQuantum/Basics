void nx_hwinit()
{
	enable_clocks();
	clock_enable_se();
	clock_enable_fuse(1);
	fuse_disable_program();

	mc_enable();

	config_oscillators();
	_REG(0x70000000, 0x40) = 0;

	config_gpios();

	clock_enable_i2c(I2C_1);
	clock_enable_i2c(I2C_5);
	clock_enable(&clock_unk1);
	clock_enable(&clock_unk2);

	i2c_init(I2C_1);
	i2c_init(I2C_5);

	//Config PMIC (TODO: use max77620.h)
	i2c_send_byte(I2C_5, 0x3C, 4, 0x40);
	i2c_send_byte(I2C_5, 0x3C, 0x41, 0x78);
	i2c_send_byte(I2C_5, 0x3C, 0x43, 0x38);
	i2c_send_byte(I2C_5, 0x3C, 0x44, 0x3A);
	i2c_send_byte(I2C_5, 0x3C, 0x45, 0x38);
	i2c_send_byte(I2C_5, 0x3C, 0x4A, 0xF);
	i2c_send_byte(I2C_5, 0x3C, 0x4E, 0xC7);
	i2c_send_byte(I2C_5, 0x3C, 0x4F, 0x4F);
	i2c_send_byte(I2C_5, 0x3C, 0x50, 0x29);
	i2c_send_byte(I2C_5, 0x3C, 0x52, 0x1B);
	i2c_send_byte(I2C_5, 0x3C, 0x16, 42); //42 = (1000 * 1125 - 600000) / 12500

	config_pmc_scratch();

	CLOCK(CLK_RST_CONTROLLER_SCLK_BURST_POLICY) = CLOCK(CLK_RST_CONTROLLER_SCLK_BURST_POLICY) & 0xFFFF8888 | 0x3333;

	mc_config_carveout();

	sdram_init();
}