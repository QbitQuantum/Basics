static int
zoh_vari_process (SRC_PRIVATE *psrc, SRC_DATA *data)
{	ZOH_DATA 	*priv ;
	double		src_ratio, input_index, rem ;
	int			ch ;

	if (data->input_frames <= 0)
		return SRC_ERR_NO_ERROR ;

	if (psrc->private_data == NULL)
		return SRC_ERR_NO_PRIVATE ;

	priv = (ZOH_DATA*) psrc->private_data ;

	if (priv->reset)
	{	/* If we have just been reset, set the last_value data. */
		for (ch = 0 ; ch < priv->channels ; ch++)
			priv->last_value [ch] = data->data_in [ch] ;
		priv->reset = 0 ;
		} ;

	priv->in_count = data->input_frames * priv->channels ;
	priv->out_count = data->output_frames * priv->channels ;
	priv->in_used = priv->out_gen = 0 ;

	src_ratio = psrc->last_ratio ;
	input_index = psrc->last_position ;

	/* Calculate samples before first sample in input array. */
	while (input_index < 1.0 && priv->out_gen < priv->out_count)
	{
		if (priv->in_used + priv->channels * input_index >= priv->in_count)
			break ;

		if (priv->out_count > 0 && fabs (psrc->last_ratio - data->src_ratio) > SRC_MIN_RATIO_DIFF)
			src_ratio = psrc->last_ratio + priv->out_gen * (data->src_ratio - psrc->last_ratio) / priv->out_count ;

		for (ch = 0 ; ch < priv->channels ; ch++)
		{	data->data_out [priv->out_gen] = priv->last_value [ch] ;
			priv->out_gen ++ ;
			} ;

		/* Figure out the next index. */
		input_index += 1.0 / src_ratio ;
		} ;

	rem = fmod_one (input_index) ;
	priv->in_used += priv->channels * lrint (input_index - rem) ;
	input_index = rem ;

	/* Main processing loop. */
	while (priv->out_gen < priv->out_count && priv->in_used + priv->channels * input_index <= priv->in_count)
	{
		if (priv->out_count > 0 && fabs (psrc->last_ratio - data->src_ratio) > SRC_MIN_RATIO_DIFF)
			src_ratio = psrc->last_ratio + priv->out_gen * (data->src_ratio - psrc->last_ratio) / priv->out_count ;

		for (ch = 0 ; ch < priv->channels ; ch++)
		{	data->data_out [priv->out_gen] = data->data_in [priv->in_used - priv->channels + ch] ;
			priv->out_gen ++ ;
			} ;

		/* Figure out the next index. */
		input_index += 1.0 / src_ratio ;
		rem = fmod_one (input_index) ;

		priv->in_used += priv->channels * lrint (input_index - rem) ;
		input_index = rem ;
		} ;

	if (priv->in_used > priv->in_count)
	{	input_index += (priv->in_used - priv->in_count) / priv->channels ;
		priv->in_used = priv->in_count ;
		} ;

	psrc->last_position = input_index ;

	if (priv->in_used > 0)
		for (ch = 0 ; ch < priv->channels ; ch++)
			priv->last_value [ch] = data->data_in [priv->in_used - priv->channels + ch] ;

	/* Save current ratio rather then target ratio. */
	psrc->last_ratio = src_ratio ;

	data->input_frames_used = priv->in_used / priv->channels ;
	data->output_frames_gen = priv->out_gen / priv->channels ;

	return SRC_ERR_NO_ERROR ;
} /* zoh_vari_process */