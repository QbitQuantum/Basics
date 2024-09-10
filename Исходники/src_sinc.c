int
sinc_set_converter (SRC_PRIVATE *psrc, int src_enum)
{	SINC_FILTER *filter, temp_filter ;
	increment_t count ;
	int bits ;

	/* Quick sanity check. */
	if (SHIFT_BITS >= sizeof (increment_t) * 8 - 1)
		return SRC_ERR_SHIFT_BITS ;

	if (psrc->private_data != NULL)
	{	free (psrc->private_data) ;
		psrc->private_data = NULL ;
		} ;

	memset (&temp_filter, 0, sizeof (temp_filter)) ;

	temp_filter.sinc_magic_marker = SINC_MAGIC_MARKER ;
	temp_filter.channels = psrc->channels ;

	if (psrc->channels > ARRAY_LEN (temp_filter.left_calc))
		return SRC_ERR_BAD_CHANNEL_COUNT ;
	else if (psrc->channels == 1)
	{	psrc->const_process = sinc_mono_vari_process ;
		psrc->vari_process = sinc_mono_vari_process ;
		}
	else
	if (psrc->channels == 2)
	{	psrc->const_process = sinc_stereo_vari_process ;
		psrc->vari_process = sinc_stereo_vari_process ;
		}
	else
	if (psrc->channels == 4)
	{	psrc->const_process = sinc_quad_vari_process ;
		psrc->vari_process = sinc_quad_vari_process ;
		}
	else
	if (psrc->channels == 6)
	{	psrc->const_process = sinc_hex_vari_process ;
		psrc->vari_process = sinc_hex_vari_process ;
		}
	else
	{	psrc->const_process = sinc_multichan_vari_process ;
		psrc->vari_process = sinc_multichan_vari_process ;
		} ;
	psrc->reset = sinc_reset ;

	switch (src_enum)
	{	case SRC_SINC_FASTEST :
				temp_filter.coeffs = fastest_coeffs.coeffs ;
				temp_filter.coeff_half_len = ARRAY_LEN (fastest_coeffs.coeffs) - 1 ;
				temp_filter.index_inc = fastest_coeffs.increment ;
				break ;

		case SRC_SINC_MEDIUM_QUALITY :
				temp_filter.coeffs = slow_mid_qual_coeffs.coeffs ;
				temp_filter.coeff_half_len = ARRAY_LEN (slow_mid_qual_coeffs.coeffs) - 1 ;
				temp_filter.index_inc = slow_mid_qual_coeffs.increment ;
				break ;

		case SRC_SINC_BEST_QUALITY :
				temp_filter.coeffs = slow_high_qual_coeffs.coeffs ;
				temp_filter.coeff_half_len = ARRAY_LEN (slow_high_qual_coeffs.coeffs) - 1 ;
				temp_filter.index_inc = slow_high_qual_coeffs.increment ;
				break ;

		default :
				return SRC_ERR_BAD_CONVERTER ;
		} ;

	/*
	** FIXME : This needs to be looked at more closely to see if there is
	** a better way. Need to look at prepare_data () at the same time.
	*/

	temp_filter.b_len = lrint (2.5 * temp_filter.coeff_half_len / (temp_filter.index_inc * 1.0) * SRC_MAX_RATIO) ;
	temp_filter.b_len = MAX (temp_filter.b_len, 4096) ;
	temp_filter.b_len *= temp_filter.channels ;

	if ((filter = calloc (1, sizeof (SINC_FILTER) + sizeof (filter->buffer [0]) * (temp_filter.b_len + temp_filter.channels))) == NULL)
		return SRC_ERR_MALLOC_FAILED ;

	*filter = temp_filter ;
	memset (&temp_filter, 0xEE, sizeof (temp_filter)) ;

	psrc->private_data = filter ;

	sinc_reset (psrc) ;

	count = filter->coeff_half_len ;
	for (bits = 0 ; (MAKE_INCREMENT_T (1) << bits) < count ; bits++)
		count |= (MAKE_INCREMENT_T (1) << bits) ;

	if (bits + SHIFT_BITS - 1 >= (int) (sizeof (increment_t) * 8))
		return SRC_ERR_FILTER_LEN ;

	return SRC_ERR_NO_ERROR ;
} /* sinc_set_converter */