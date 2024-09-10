error_code cellVideoOutGetState(u32 videoOut, u32 deviceIndex, vm::ptr<CellVideoOutState> state)
{
	cellSysutil.trace("cellVideoOutGetState(videoOut=%d, deviceIndex=%d, state=*0x%x)", videoOut, deviceIndex, state);

	if (deviceIndex) return CELL_VIDEO_OUT_ERROR_DEVICE_NOT_FOUND;

	switch (videoOut)
	{
	case CELL_VIDEO_OUT_PRIMARY:
		state->state = CELL_VIDEO_OUT_OUTPUT_STATE_ENABLED;
		state->colorSpace = CELL_VIDEO_OUT_COLOR_SPACE_RGB;
		state->displayMode.resolutionId = g_video_out_resolution_id.at(g_cfg.video.resolution); // TODO
		state->displayMode.scanMode = CELL_VIDEO_OUT_SCAN_MODE_PROGRESSIVE;
		state->displayMode.conversion = CELL_VIDEO_OUT_DISPLAY_CONVERSION_NONE;
		state->displayMode.aspect = g_video_out_aspect_id.at(g_cfg.video.aspect_ratio); // TODO
		state->displayMode.refreshRates = CELL_VIDEO_OUT_REFRESH_RATE_59_94HZ;
		return CELL_OK;

	case CELL_VIDEO_OUT_SECONDARY:
		*state = { CELL_VIDEO_OUT_OUTPUT_STATE_DISABLED }; // ???
		return CELL_OK;
	}

	return CELL_VIDEO_OUT_ERROR_UNSUPPORTED_VIDEO_OUT;
}