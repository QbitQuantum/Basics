static void osd_antiflicker_process(void)
{
	canvas_t cs, cd;
	u32 x0 = 0;
	u32 y0 = 0;
	u32 y1 = 0;

	config_para_ex_t *ge2d_config = &ge2d_osd_antiflicker.ge2d_config;
	ge2d_context_t *context = ge2d_osd_antiflicker.ge2d_context;

	canvas_read(OSD1_CANVAS_INDEX, &cs);
	canvas_read(OSD2_CANVAS_INDEX, &cd);

	if (ge2d_osd_antiflicker.pan == 1) {
		y0 = cs.height/2;
		//y1 = cd.height/2;
	}

	memset(ge2d_config, 0, sizeof(config_para_ex_t));
	ge2d_config->alu_const_color = 0;
	ge2d_config->bitmask_en = 0;
	ge2d_config->src1_gb_alpha = 0;

	ge2d_config->src_planes[0].addr = cs.addr;
	ge2d_config->src_planes[0].w = cs.width/4;
	ge2d_config->src_planes[0].h = cs.height;

	ge2d_config->dst_planes[0].addr = cd.addr;
	ge2d_config->dst_planes[0].w = cd.width/4;
	ge2d_config->dst_planes[0].h = cd.height;

	ge2d_config->src_para.canvas_index = OSD1_CANVAS_INDEX;
	ge2d_config->src_para.mem_type = CANVAS_OSD0;
	ge2d_config->dst_para.format = GE2D_FORMAT_S32_ARGB;
	ge2d_config->src_para.fill_color_en = 0;
	ge2d_config->src_para.fill_mode = 0;
	ge2d_config->src_para.x_rev = 0;
	ge2d_config->src_para.y_rev = 0;
	ge2d_config->src_para.color = 0xffffffff;
	ge2d_config->src_para.top = 0;
	ge2d_config->src_para.left = 0;
	ge2d_config->src_para.width = cs.width/4;
	ge2d_config->src_para.height = cs.height;

	ge2d_config->dst_para.canvas_index = OSD2_CANVAS_INDEX;
	ge2d_config->dst_para.mem_type = CANVAS_OSD1;
	ge2d_config->dst_para.format = GE2D_FORMAT_S32_ARGB;
	ge2d_config->dst_para.top = 0;
	ge2d_config->dst_para.left = 0;
	ge2d_config->dst_para.width = cd.width/4;
	ge2d_config->dst_para.height = cd.height;
	ge2d_config->dst_para.fill_color_en = 0;
	ge2d_config->dst_para.fill_mode = 0;
	ge2d_config->dst_para.color = 0;
	ge2d_config->dst_para.x_rev = 0;
	ge2d_config->dst_para.y_rev = 0;
	ge2d_config->dst_xy_swap = 0;

	if (ge2d_context_config_ex(context, ge2d_config) < 0) {
		printk("++ osd antiflicker ge2d config error.\n");
		return;
	}
	stretchblt(context, x0, y0, cs.width/4, cs.height/2, x0, y1, cd.width/4, cd.height);
}