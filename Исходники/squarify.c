/**
 * Determines the worst resulting aspect ratio of a set of rectangles laid out in a larger one.
 *
 * @param sum       The sum of all areas in the list.
 * @param min_dim   The value of the outer rectangle's minimum dimension.
 * @param areas     The areas to be laid out.
 * @param num_rects The number of rectangles in the list.
 */
float worst(float sum, float min_dim, float *areas, size_t num_rects) {
    float sum_sq = sum * sum;
    float min_dim_sq = min_dim * min_dim;

    float min_area = areas[0];
    float max_area = areas[0];
    size_t i;
    
    /* Determine the rectangles with the largest and smallest areas */
    for(i = 1; i < num_rects; ++i) {
        if(areas[i] < min_area) {
            min_area = areas[i];
        } else if(areas[i] > max_area) {
            max_area = areas[i];
        }
    }

    return fmaxf(min_dim_sq * max_area / sum_sq, sum_sq / (min_dim_sq * min_area));
}