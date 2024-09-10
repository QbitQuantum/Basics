static int avalon_panel_init(void)
{
	int err;
	struct resource *res;

	mutex_init(&lcd_lock);

	ast_carveouts[1].base = tegra_carveout_start;
	ast_carveouts[1].size = tegra_carveout_size;

	err = gpio_request(AST_LVDS_SHUTDOWN, "lvds_shutdown");
	if (err < 0)
		return err;

	gpio_direction_output(AST_LVDS_SHUTDOWN, 1);
	tegra_gpio_enable(AST_LVDS_SHUTDOWN);

	/* hdmi software enable pin */
/*        tegra_gpio_enable(AST_HDMI_ENB);*/
/*        gpio_request(AST_HDMI_ENB, "ast_hdmi_enb");*/
/*        gpio_direction_output(AST_HDMI_ENB, 1);*/

	gpio_request(AST_HDMI_HPD, "hdmi_hpd");
	gpio_direction_input(AST_HDMI_HPD);
	tegra_gpio_enable(AST_HDMI_HPD);

#ifdef CONFIG_HAS_EARLYSUSPEND
	ast_panel_early_suspender.suspend = ast_panel_early_suspend;
	ast_panel_early_suspender.resume = ast_panel_late_resume;
	ast_panel_early_suspender.level = EARLY_SUSPEND_LEVEL_DISABLE_FB;
	register_early_suspend(&ast_panel_early_suspender);
#endif

	err = platform_add_devices(ast_gfx_devices,
				ARRAY_SIZE(ast_gfx_devices));
	res = nvhost_get_resource_byname(&ast_disp1_device,
					 IORESOURCE_MEM, "fbmem");
	res->start = tegra_fb_start;
	res->end = tegra_fb_start + tegra_fb_size - 1;

	/* Copy the bootloader fb to the fb. */
	tegra_move_framebuffer(tegra_fb_start, tegra_bootloader_fb_start,
				min(tegra_fb_size, tegra_bootloader_fb_size));

	if (!err)
		err = nvhost_device_register(&ast_disp1_device);

	res = nvhost_get_resource_byname(&ast_disp2_device,
					 IORESOURCE_MEM, "fbmem");
	res->start = tegra_fb2_start;
	res->end = tegra_fb2_start + tegra_fb2_size - 1;
	if (!err)
		err = nvhost_device_register(&ast_disp2_device);

#if defined(CONFIG_TEGRA_NVAVP)
	if (!err)
		err = nvhost_device_register(&nvavp_device);
#endif

	return err;
}