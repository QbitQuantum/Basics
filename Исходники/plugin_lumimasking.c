static int
lumi_plg_frame(lumi_data_t *handle, xvid_plg_data_t *data)
{
	int i, j;

	float global = 0.0f;

	const float DarkAmpl = 14 / 4;
	const float BrightAmpl = 10 / 3;
	float DarkThres = 90;
	float BrightThres = 200;

	const float GlobalDarkThres = 60;
	const float GlobalBrightThres = 170;

	/* Arbitrary centerpoint for variance-based AQ.  Roughly the same as used in x264. */
	float center = 14000.f;
	/* Arbitrary strength for variance-based AQ. */
	float strength = 0.2f;

	if (data->type == XVID_TYPE_BVOP) return 0;

	/* Do this for all macroblocks individually  */
	for (j = 0; j < data->mb_height; j++) {
		for (i = 0; i < data->mb_width; i++) {
			int k, l, sum = 0, sum_of_squares = 0;	
			unsigned char *ptr;

			/* Initialize the current quant value to the frame quant */
			handle->quant[j*data->mb_width + i] = (float)data->quant;

			/* Next steps compute the luminance-masking */

			/* Get the MB address */
			ptr  = data->current.plane[0];
			ptr += 16*j*data->current.stride[0] + 16*i;

			if (handle->method) { /* Variance masking mode */
				int variance = 0;
				/* Accumulate sum and sum of squares over the MB */
				for (k = 0; k < 16; k++) {
 					for (l = 0; l < 16; l++) {
						int val = ptr[k*data->current.stride[0] + l];
						sum += val;
						sum_of_squares += val * val;
					}
				}
				/* Variance = SSD - SAD^2 / (numpixels) */
				variance = sum_of_squares - sum * sum / 256;
				handle->val[j*data->mb_width + i] = (float)variance;
			}
			else { /* Luminance masking mode */
				/* Accumulate luminance */
				for (k = 0; k < 16; k++)
					for (l = 0; l < 16; l++)
						 sum += ptr[k*data->current.stride[0] + l];
			
				handle->val[j*data->mb_width + i] = (float)sum/256.0f;

				/* Accumulate the global frame luminance */
				global += (float)sum/256.0f;
			}
		}
	}

	if (handle->method) { /* Variance masking */
		/* Apply the variance masking formula to all MBs */
		for (i = 0; i < data->mb_height; i++)
		{
			for (j = 0; j < data->mb_width; j++)
			{
				float value = handle->val[i*data->mb_width + j];
				float qscale_diff = strength * logf(value / center);
				handle->quant[i*data->mb_width + j] *= (1.0f + qscale_diff);
 			}
 		}
	}
	else { /* Luminance masking */
		/* Normalize the global luminance accumulator */
		global /= data->mb_width*data->mb_height;

		DarkThres = DarkThres*global/127.0f;
		BrightThres = BrightThres*global/127.0f;


		/* Apply luminance masking only to frames where the global luminance is
		 * higher than DarkThreshold and lower than Bright Threshold */
		 if ((global < GlobalBrightThres) && (global > GlobalDarkThres)) {

			/* Apply the luminance masking formulas to all MBs */
			for (i = 0; i < data->mb_height; i++) {
				for (j = 0; j < data->mb_width; j++) {
					if (handle->val[i*data->mb_width + j] < DarkThres)
						handle->quant[i*data->mb_width + j] *= 1 + DarkAmpl * (DarkThres - handle->val[i*data->mb_width + j]) / DarkThres;
					else if (handle->val[i*data->mb_width + j] > BrightThres)
						handle->quant[i*data->mb_width + j] *= 1 + BrightAmpl * (handle->val[i*data->mb_width + j] - BrightThres) / (255 - BrightThres);
				}
			}
		}
	}

	/* Normalize the quantizer field */
	data->quant = normalize_quantizer_field(handle->quant,
											 data->dquant,
											 data->mb_width*data->mb_height,
											 data->quant,
											 MAX(2,data->quant + data->quant/2));

	/* Plugin job finished */
	return(0);
}