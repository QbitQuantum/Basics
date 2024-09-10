static void __init offb_init_fb(const char *name, const char *full_name,
				int width, int height, int depth,
				int pitch, unsigned long address,
				int foreign_endian, struct device_node *dp)
{
	unsigned long res_size = pitch * height * (depth + 7) / 8;
	struct offb_par *par = &default_par;
	unsigned long res_start = address;
	struct fb_fix_screeninfo *fix;
	struct fb_var_screeninfo *var;
	struct fb_info *info;

	if (!request_mem_region(res_start, res_size, "offb"))
		return;

	printk(KERN_INFO
	       "Using unsupported %dx%d %s at %lx, depth=%d, pitch=%d\n",
	       width, height, name, address, depth, pitch);
	if (depth != 8 && depth != 15 && depth != 16 && depth != 32) {
		printk(KERN_ERR "%s: can't use depth = %d\n", full_name,
		       depth);
		release_mem_region(res_start, res_size);
		return;
	}

	info = framebuffer_alloc(sizeof(u32) * 16, NULL);
	
	if (info == 0) {
		release_mem_region(res_start, res_size);
		return;
	}

	fix = &info->fix;
	var = &info->var;
	info->par = par;

	strcpy(fix->id, "OFfb ");
	strncat(fix->id, name, sizeof(fix->id) - sizeof("OFfb "));
	fix->id[sizeof(fix->id) - 1] = '\0';

	var->xres = var->xres_virtual = width;
	var->yres = var->yres_virtual = height;
	fix->line_length = pitch;

	fix->smem_start = address;
	fix->smem_len = pitch * height;
	fix->type = FB_TYPE_PACKED_PIXELS;
	fix->type_aux = 0;

	par->cmap_type = cmap_unknown;
	if (depth == 8)
		offb_init_palette_hacks(info, dp, name, address);
	else
		fix->visual = FB_VISUAL_TRUECOLOR;

	var->xoffset = var->yoffset = 0;
	switch (depth) {
	case 8:
		var->bits_per_pixel = 8;
		var->red.offset = 0;
		var->red.length = 8;
		var->green.offset = 0;
		var->green.length = 8;
		var->blue.offset = 0;
		var->blue.length = 8;
		var->transp.offset = 0;
		var->transp.length = 0;
		break;
	case 15:		/* RGB 555 */
		var->bits_per_pixel = 16;
		var->red.offset = 10;
		var->red.length = 5;
		var->green.offset = 5;
		var->green.length = 5;
		var->blue.offset = 0;
		var->blue.length = 5;
		var->transp.offset = 0;
		var->transp.length = 0;
		break;
	case 16:		/* RGB 565 */
		var->bits_per_pixel = 16;
		var->red.offset = 11;
		var->red.length = 5;
		var->green.offset = 5;
		var->green.length = 6;
		var->blue.offset = 0;
		var->blue.length = 5;
		var->transp.offset = 0;
		var->transp.length = 0;
		break;
	case 32:		/* RGB 888 */
		var->bits_per_pixel = 32;
		var->red.offset = 16;
		var->red.length = 8;
		var->green.offset = 8;
		var->green.length = 8;
		var->blue.offset = 0;
		var->blue.length = 8;
		var->transp.offset = 24;
		var->transp.length = 8;
		break;
	}
	var->red.msb_right = var->green.msb_right = var->blue.msb_right =
	    var->transp.msb_right = 0;
	var->grayscale = 0;
	var->nonstd = 0;
	var->activate = 0;
	var->height = var->width = -1;
	var->pixclock = 10000;
	var->left_margin = var->right_margin = 16;
	var->upper_margin = var->lower_margin = 16;
	var->hsync_len = var->vsync_len = 8;
	var->sync = 0;
	var->vmode = FB_VMODE_NONINTERLACED;

	/* set offb aperture size for generic probing */
	info->apertures = alloc_apertures(1);
	if (!info->apertures)
		goto out_aper;
	info->apertures->ranges[0].base = address;
	info->apertures->ranges[0].size = fix->smem_len;

	info->fbops = &offb_ops;
	info->screen_base = ioremap(address, fix->smem_len);
	info->pseudo_palette = (void *) (info + 1);
	info->flags = FBINFO_DEFAULT | FBINFO_MISC_FIRMWARE | foreign_endian;

	fb_alloc_cmap(&info->cmap, 256, 0);

	if (register_framebuffer(info) < 0)
		goto out_err;

	printk(KERN_INFO "fb%d: Open Firmware frame buffer device on %s\n",
	       info->node, full_name);
	return;

out_err:
	iounmap(info->screen_base);
out_aper:
	iounmap(par->cmap_adr);
	par->cmap_adr = NULL;
	framebuffer_release(info);
	release_mem_region(res_start, res_size);
}