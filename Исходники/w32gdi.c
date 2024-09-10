static int w32gdi_restore(void)
{
	/* Restore gamma ramps */
	if( (!state.hDC)||(!state.saved_ramps) ){
		LOG(LOGERR,_("No device context or ramp."));
		return RET_FUN_FAILED;
	}
	if( !SetDeviceGammaRamp(state.hDC, state.saved_ramps) ){
		LOG(LOGERR,_("Unable to restore gamma ramps."));
		return RET_FUN_FAILED;
	}
	return RET_FUN_SUCCESS;
}