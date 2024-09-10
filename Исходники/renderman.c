void rmInit() {
	gsGlobal = gsKit_init_global();

	rm_mode_table[RM_VMODE_AUTO].mode = gsGlobal->Mode;
	rm_mode_table[RM_VMODE_AUTO].height = gsGlobal->Height;

	dmaKit_init(D_CTRL_RELE_OFF, D_CTRL_MFD_OFF, D_CTRL_STS_UNSPEC,
				D_CTRL_STD_OFF, D_CTRL_RCYC_8, 1 << DMA_CHANNEL_GIF);

	// Initialize the DMAC
	dmaKit_chan_init(DMA_CHANNEL_GIF);

	rmSetMode(1);

	order = 0;

	aspectWidth = 1.0f;
	aspectHeight = 1.0f;

	shiftYVal = 1.0f;
	shiftY = &shiftYFunc;

	transX = 0.0f;
	transY = 0.0f;

	guiThreadID = GetThreadId();
	gsKit_add_vsync_handler(&rmOnVSync);
}