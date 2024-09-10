/* stride is bytes between rows in the output buffer. */
BOOL rfx_decode_rgb(RFX_CONTEXT* context, wStream* data_in,
	int y_size, const UINT32* y_quants,
	int cb_size, const UINT32* cb_quants,
	int cr_size, const UINT32* cr_quants, BYTE* rgb_buffer, int stride)
{
	INT16* pSrcDst[3];
	static const prim_size_t roi_64x64 = { 64, 64 };
	const primitives_t *prims = primitives_get();

	PROFILER_ENTER(context->priv->prof_rfx_decode_rgb);

	pSrcDst[0] = (INT16*)((BYTE*)BufferPool_Take(context->priv->BufferPool, -1) + 16); /* y_r_buffer */
	pSrcDst[1] = (INT16*)((BYTE*)BufferPool_Take(context->priv->BufferPool, -1) + 16); /* cb_g_buffer */
	pSrcDst[2] = (INT16*)((BYTE*)BufferPool_Take(context->priv->BufferPool, -1) + 16); /* cr_b_buffer */

#if 0
	if (context->priv->UseThreads)
	{
		PTP_WORK work_objects[3];
		RFX_COMPONENT_WORK_PARAM params[3];

		params[0].context = context;
		params[0].quantization_values = y_quants;
		params[0].buffer = stream_get_tail(data_in);
		params[0].capacity = y_size;
		params[0].buffer = pSrcDst[0];
		stream_seek(data_in, y_size);

		params[1].context = context;
		params[1].quantization_values = cb_quants;
		params[1].buffer = stream_get_tail(data_in);
		params[1].capacity = cb_size;
		params[1].buffer = pSrcDst[1];
		stream_seek(data_in, cb_size);

		params[2].context = context;
		params[2].quantization_values = cr_quants;
		params[2].buffer = stream_get_tail(data_in);
		params[2].capacity = cr_size;
		params[2].buffer = pSrcDst[2];
		stream_seek(data_in, cr_size);

		work_objects[0] = CreateThreadpoolWork((PTP_WORK_CALLBACK) rfx_decode_component_work_callback,
				(void*) &params[0], &context->priv->ThreadPoolEnv);
		work_objects[1] = CreateThreadpoolWork((PTP_WORK_CALLBACK) rfx_decode_component_work_callback,
				(void*) &params[1], &context->priv->ThreadPoolEnv);
		work_objects[2] = CreateThreadpoolWork((PTP_WORK_CALLBACK) rfx_decode_component_work_callback,
				(void*) &params[2], &context->priv->ThreadPoolEnv);

		SubmitThreadpoolWork(work_objects[0]);
		SubmitThreadpoolWork(work_objects[1]);
		SubmitThreadpoolWork(work_objects[2]);

		WaitForThreadpoolWorkCallbacks(work_objects[0], FALSE);
		WaitForThreadpoolWorkCallbacks(work_objects[1], FALSE);
		WaitForThreadpoolWorkCallbacks(work_objects[2], FALSE);
	}
	else
#endif
	{
		if (stream_get_left(data_in) < y_size+cb_size+cr_size)
		{
			DEBUG_WARN("rfx_decode_rgb: packet too small for y_size+cb_size+cr_size");
			return FALSE;
		}
		rfx_decode_component(context, y_quants, stream_get_tail(data_in), y_size, pSrcDst[0]); /* YData */
		stream_seek(data_in, y_size);

		rfx_decode_component(context, cb_quants, stream_get_tail(data_in), cb_size, pSrcDst[1]); /* CbData */
		stream_seek(data_in, cb_size);

		rfx_decode_component(context, cr_quants, stream_get_tail(data_in), cr_size, pSrcDst[2]); /* CrData */
		stream_seek(data_in, cr_size);
	}

	prims->yCbCrToRGB_16s16s_P3P3((const INT16**) pSrcDst, 64 * sizeof(INT16),
			pSrcDst, 64 * sizeof(INT16), &roi_64x64);

	PROFILER_ENTER(context->priv->prof_rfx_decode_format_rgb);
		rfx_decode_format_rgb(pSrcDst[0], pSrcDst[1], pSrcDst[2],
			context->pixel_format, rgb_buffer, stride);
	PROFILER_EXIT(context->priv->prof_rfx_decode_format_rgb);
	
	PROFILER_EXIT(context->priv->prof_rfx_decode_rgb);

	BufferPool_Return(context->priv->BufferPool, (BYTE*)pSrcDst[0] - 16);
	BufferPool_Return(context->priv->BufferPool, (BYTE*)pSrcDst[1] - 16);
	BufferPool_Return(context->priv->BufferPool, (BYTE*)pSrcDst[2] - 16);
	return TRUE;
}