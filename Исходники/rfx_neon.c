void rfx_init_neon(RFX_CONTEXT * context)
{
	if (IsProcessorFeaturePresent(PF_ARM_NEON_INSTRUCTIONS_AVAILABLE))
	{
		DEBUG_RFX("Using NEON optimizations");

		IF_PROFILER(context->priv->prof_rfx_ycbcr_to_rgb->name = "rfx_decode_YCbCr_to_RGB_NEON");
		IF_PROFILER(context->priv->prof_rfx_quantization_decode->name = "rfx_quantization_decode_NEON");
		IF_PROFILER(context->priv->prof_rfx_dwt_2d_decode->name = "rfx_dwt_2d_decode_NEON");

		context->quantization_decode = rfx_quantization_decode_NEON;
		context->dwt_2d_decode = rfx_dwt_2d_decode_NEON;
	}
}