static void Sampled_getSum2AndDefinitionRange
	(Sampled me, double xmin, double xmax, long ilevel, int unit, double mean, bool interpolate, double *return_sum2, double *return_definitionRange)
{
	/*
		This function computes the area under the linearly interpolated squared difference curve between xmin and xmax.
		Outside [x1-dx/2, xN+dx/2], the curve is undefined and neither times nor values are counted.
		In [x1-dx/2,x1] and [xN,xN+dx/2], the curve is linearly extrapolated.
	*/
	long imin, imax;
	double sum2 = 0.0, definitionRange = 0.0;
	Function_unidirectionalAutowindow (me, & xmin, & xmax);
	if (Function_intersectRangeWithDomain (me, & xmin, & xmax)) {
		if (interpolate) {
			if (Sampled_getWindowSamples (me, xmin, xmax, & imin, & imax)) {
				double leftEdge = my x1 - 0.5 * my dx, rightEdge = leftEdge + my nx * my dx;
				for (long isamp = imin; isamp <= imax; isamp ++) {
					double value = my v_getValueAtSample (isamp, ilevel, unit);   // a fast way to integrate a linearly interpolated curve; works everywhere except at the edges
					if (NUMdefined (value)) {
						value -= mean;
						value *= value;
						definitionRange += 1.0;
						sum2 += value;
					}
				}
				/*
				 * Corrections within the first and last sampling intervals.
				 */
				if (xmin > leftEdge) {   // otherwise, constant extrapolation over 0.5 sample is OK
					double phase = (my x1 + (imin - 1) * my dx - xmin) / my dx;   // this fraction of sampling interval is still to be determined
					double rightValue = Sampled_getValueAtSample (me, imin, ilevel, unit);
					double leftValue = Sampled_getValueAtSample (me, imin - 1, ilevel, unit);
					if (NUMdefined (rightValue)) {
						rightValue -= mean;
						rightValue *= rightValue;
						definitionRange -= 0.5;   // delete constant extrapolation over 0.5 sample
						sum2 -= 0.5 * rightValue;
						if (NUMdefined (leftValue)) {
							leftValue -= mean;
							leftValue *= leftValue;
							definitionRange += phase;   // add current fraction
							sum2 += phase * (rightValue + 0.5 * phase * (leftValue - rightValue));   // interpolate to outside sample
						} else {
							if (phase > 0.5) phase = 0.5;
							definitionRange += phase;   // add current fraction, but never more than 0.5
							sum2 += phase * rightValue;
						}
					} else if (NUMdefined (leftValue) && phase > 0.5) {
						leftValue -= mean;
						leftValue *= leftValue;
						definitionRange += phase - 0.5;
						sum2 += (phase - 0.5) * leftValue;
					}
				}
				if (xmax < rightEdge) {   // otherwise, constant extrapolation is OK
					double phase = (xmax - (my x1 + (imax - 1) * my dx)) / my dx;   // this fraction of sampling interval is still to be determined
					double leftValue = Sampled_getValueAtSample (me, imax, ilevel, unit);
					double rightValue = Sampled_getValueAtSample (me, imax + 1, ilevel, unit);
					if (NUMdefined (leftValue)) {
						leftValue -= mean;
						leftValue *= leftValue;
						definitionRange -= 0.5;   // delete constant extrapolation over 0.5 sample
						sum2 -= 0.5 * leftValue;
						if (NUMdefined (rightValue)) {
							rightValue -= mean;
							rightValue *= rightValue;
							definitionRange += phase;   // add current fraction
							sum2 += phase * (leftValue + 0.5 * phase * (rightValue - leftValue));   // interpolate to outside sample
						} else {
							if (phase > 0.5) phase = 0.5;
							definitionRange += phase;   // add current fraction, but never more than 0.5
							sum2 += phase * leftValue;
						}
					} else if (NUMdefined (rightValue) && phase > 0.5) {
						rightValue -= mean;
						rightValue *= rightValue;
						definitionRange += phase - 0.5;
						sum2 += (phase - 0.5) * rightValue;
					}
				}
			} else {   // no sample centres between xmin and xmax
				/*
				 * Try to return the mean of the interpolated values at these two points.
				 * Thus, a small (xmin, xmax) range gives the same value as the (xmin+xmax)/2 point.
				 */
				double leftValue = Sampled_getValueAtSample (me, imax, ilevel, unit);
				double rightValue = Sampled_getValueAtSample (me, imin, ilevel, unit);
				double phase1 = (xmin - (my x1 + (imax - 1) * my dx)) / my dx;
				double phase2 = (xmax - (my x1 + (imax - 1) * my dx)) / my dx;
				if (imin == imax + 1) {   // not too far from sample definition region
					if (NUMdefined (leftValue)) {
						leftValue -= mean;
						leftValue *= leftValue;
						if (NUMdefined (rightValue)) {
							rightValue -= mean;
							rightValue *= rightValue;
							definitionRange += phase2 - phase1;
							sum2 += (phase2 - phase1) * (leftValue + 0.5 * (phase1 + phase2) * (rightValue - leftValue));
						} else if (phase1 < 0.5) {
							if (phase2 > 0.5) phase2 = 0.5;
							definitionRange += phase2 - phase1;
							sum2 += (phase2 - phase1) * leftValue;
						}
					} else if (NUMdefined (rightValue) && phase2 > 0.5) {
						rightValue -= mean;
						rightValue *= rightValue;
						if (phase1 < 0.5) phase1 = 0.5;
						definitionRange += phase2 - phase1;
						sum2 += (phase2 - phase1) * rightValue;
					}
				}
			}
		} else {   // no interpolation
			double rimin = Sampled_xToIndex (me, xmin), rimax = Sampled_xToIndex (me, xmax);
			if (rimax >= 0.5 && rimin < my nx + 0.5) {
				imin = rimin < 0.5 ? 0 : lround (rimin);
				imax = rimax >= my nx + 0.5 ? my nx + 1 : lround (rimax);
				for (long isamp = imin + 1; isamp < imax; isamp ++) {
					double value = my v_getValueAtSample (isamp, ilevel, unit);
					if (NUMdefined (value)) {
						value -= mean;
						value *= value;
						definitionRange += 1.0;
						sum2 += value;
					}
				}
				if (imin == imax) {
					double value = my v_getValueAtSample (imin, ilevel, unit);
					if (NUMdefined (value)) {
						double phase = rimax - rimin;
						value -= mean;
						value *= value;
						definitionRange += phase;
						sum2 += phase * value;
					}
				} else {
					if (imin >= 1) {
						double value = my v_getValueAtSample (imin, ilevel, unit);
						if (NUMdefined (value)) {
							double phase = imin - rimin + 0.5;
							value -= mean;
							value *= value;
							definitionRange += phase;
							sum2 += phase * value;
						}
					}
					if (imax <= my nx) {
						double value = my v_getValueAtSample (imax, ilevel, unit);
						if (NUMdefined (value)) {
							double phase = rimax - imax + 0.5;
							value -= mean;
							value *= value;
							definitionRange += phase;
							sum2 += phase * value;
						}
					}
				}
			}
		}
	}
	if (return_sum2) *return_sum2 = sum2;
	if (return_definitionRange) *return_definitionRange = definitionRange;
}