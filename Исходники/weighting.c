struct flow_interpolation_line_contributions *
flow_interpolation_line_contributions_create(flow_c * context, const uint32_t output_line_size,
                                             const uint32_t input_line_size,
                                             const struct flow_interpolation_details * details)
{
    const double sharpen_ratio = flow_interpolation_details_percent_negative_weight(details);
    const double desired_sharpen_ratio = details->sharpen_percent_goal / 100.0;

    const double scale_factor = (double)output_line_size / (double)input_line_size;
    const double downscale_factor = fmin(1.0, scale_factor);
    const double half_source_window = (details->window + 0.5) / downscale_factor;

    const uint32_t allocated_window_size = (int)ceil(2 * (half_source_window - TONY)) + 1;
    uint32_t u, ix;
    struct flow_interpolation_line_contributions * res
        = LineContributions_alloc(context, output_line_size, allocated_window_size);
    if (res == NULL) {
        FLOW_add_to_callstack(context);
        return NULL;
    }
    double negative_area = 0;
    double positive_area = 0;

    for (u = 0; u < output_line_size; u++) {
        const double center_src_pixel = ((double)u + 0.5) / scale_factor - 0.5;

        const int left_edge = (int)floor(center_src_pixel) - ((allocated_window_size - 1) / 2);
        const int right_edge = left_edge + allocated_window_size - 1;

        const uint32_t left_src_pixel = (uint32_t)int_max(0, left_edge);
        const uint32_t right_src_pixel = (uint32_t)int_min(right_edge, (int)input_line_size - 1);

        double total_weight = 0.0;
        double total_negative_weight = 0.0;

        const uint32_t source_pixel_count = right_src_pixel - left_src_pixel + 1;

        if (source_pixel_count > allocated_window_size) {
            flow_interpolation_line_contributions_destroy(context, res);
            FLOW_error(context, flow_status_Invalid_internal_state);
            return NULL;
        }

        res->ContribRow[u].Left = left_src_pixel;
        res->ContribRow[u].Right = right_src_pixel;

        float * weights = res->ContribRow[u].Weights;

        // commented: additional weight for edges (doesn't seem to be too effective)
        // for (ix = left_edge; ix <= right_edge; ix++) {
        for (ix = left_src_pixel; ix <= right_src_pixel; ix++) {
            int tx = ix - left_src_pixel;
            // int tx = min(max(ix, left_src_pixel), right_src_pixel) - left_src_pixel;
            double add = (*details->filter)(details, downscale_factor *((double)ix - center_src_pixel));
            if (fabs(add) <= 0.00000002){
                add = 0.0;
                // Weights below a certain threshold make consistent x-plat
                // integration test results impossible. pos/neg zero, etc.
                // They should be rounded down to zero at the threshold at which results are consistent.
            }
            weights[tx] = (float)add;
            total_weight += add;
            total_negative_weight -= fmin(0,add);
        }

        float neg_factor, pos_factor;
        if (total_weight <= 0 || desired_sharpen_ratio > sharpen_ratio){
            float total_positive_weight = total_weight + total_negative_weight;
            float target_negative_weight = desired_sharpen_ratio * total_positive_weight;
            pos_factor = 1;
            neg_factor = target_negative_weight / total_negative_weight;
        }else{
            neg_factor = pos_factor = (float)(1.0f / total_weight);
        }
        for (ix = 0; ix < source_pixel_count; ix++) {
            if (weights[ix] < 0) {
                weights[ix] *= neg_factor;
                negative_area -= weights[ix];
            } else {
                weights[ix] *= pos_factor;
                positive_area += weights[ix];
            }
        }

        //Shrink to improve perf & result consistency
        int32_t iix;
        //Shrink region from the right
        for (iix = source_pixel_count - 1; iix >= 0; iix--){
            if (weights[iix] != 0) break;
            res->ContribRow[u].Right--;
        }
        //Shrink region from the left
        for (iix = 0; iix < (int32_t)source_pixel_count; iix++){
            if (weights[0] != 0) break;
            res->ContribRow[u].Weights++;
            weights++;
            res->ContribRow[u].Left++;
        }
    }
    res->percent_negative = negative_area / positive_area;
    return res;
}