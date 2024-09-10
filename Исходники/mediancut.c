/*
 ** Here is the fun part, the median-cut colormap generator.  This is based
 ** on Paul Heckbert's paper, "Color Image Quantization for Frame Buffer
 ** Display," SIGGRAPH 1982 Proceedings, page 297.
 */
LIQ_PRIVATE colormap *mediancut(histogram *hist, const float min_opaque_val, unsigned int newcolors, const double target_mse, const double max_mse, void* (*malloc)(size_t), void (*free)(void*))
{
    hist_item *achv = hist->achv;
    struct box bv[newcolors];

    /*
     ** Set up the initial box.
     */
    bv[0].ind = 0;
    bv[0].colors = hist->size;
    bv[0].color = averagepixels(bv[0].colors, &achv[bv[0].ind], min_opaque_val, (f_pixel){0.5,0.5,0.5,0.5});
    bv[0].variance = box_variance(achv, &bv[0]);
    bv[0].max_error = box_max_error(achv, &bv[0]);
    bv[0].sum = 0;
    bv[0].total_error = -1;
    for(unsigned int i=0; i < bv[0].colors; i++) bv[0].sum += achv[i].adjusted_weight;

    unsigned int boxes = 1;

    // remember smaller palette for fast searching
    colormap *representative_subset = NULL;
    unsigned int subset_size = ceilf(powf(newcolors,0.7f));

    /*
     ** Main loop: split boxes until we have enough.
     */
    while (boxes < newcolors) {

        if (boxes == subset_size) {
            representative_subset = pam_colormap(boxes, malloc, free);
            set_colormap_from_boxes(representative_subset, bv, boxes, achv);
        }

        // first splits boxes that exceed quality limit (to have colors for things like odd green pixel),
        // later raises the limit to allow large smooth areas/gradients get colors.
        const double current_max_mse = max_mse + (boxes/(double)newcolors)*16.0*max_mse;
        const int bi = best_splittable_box(bv, boxes, current_max_mse);
        if (bi < 0)
            break;        /* ran out of colors! */

        unsigned int indx = bv[bi].ind;
        unsigned int clrs = bv[bi].colors;

        /*
         Classic implementation tries to get even number of colors or pixels in each subdivision.

         Here, instead of popularity I use (sqrt(popularity)*variance) metric.
         Each subdivision balances number of pixels (popular colors) and low variance -
         boxes can be large if they have similar colors. Later boxes with high variance
         will be more likely to be split.

         Median used as expected value gives much better results than mean.
         */

        const double halfvar = prepare_sort(&bv[bi], achv);
        double lowervar=0;

        // hist_item_sort_halfvar sorts and sums lowervar at the same time
        // returns item to break at …minus one, which does smell like an off-by-one error.
        hist_item *break_p = hist_item_sort_halfvar(&achv[indx], clrs, &lowervar, halfvar);
        unsigned int break_at = MIN(clrs-1, break_p - &achv[indx] + 1);

        /*
         ** Split the box.
         */
        double sm = bv[bi].sum;
        double lowersum = 0;
        for(unsigned int i=0; i < break_at; i++) lowersum += achv[indx + i].adjusted_weight;

        const f_pixel previous_center = bv[bi].color;
        bv[bi].colors = break_at;
        bv[bi].sum = lowersum;
        bv[bi].color = averagepixels(bv[bi].colors, &achv[bv[bi].ind], min_opaque_val, previous_center);
        bv[bi].total_error = -1;
        bv[bi].variance = box_variance(achv, &bv[bi]);
        bv[bi].max_error = box_max_error(achv, &bv[bi]);
        bv[boxes].ind = indx + break_at;
        bv[boxes].colors = clrs - break_at;
        bv[boxes].sum = sm - lowersum;
        bv[boxes].color = averagepixels(bv[boxes].colors, &achv[bv[boxes].ind], min_opaque_val, previous_center);
        bv[boxes].total_error = -1;
        bv[boxes].variance = box_variance(achv, &bv[boxes]);
        bv[boxes].max_error = box_max_error(achv, &bv[boxes]);

        ++boxes;

        if (total_box_error_below_target(target_mse, bv, boxes, hist)) {
            break;
        }
    }

    colormap *map = pam_colormap(boxes, malloc, free);
    set_colormap_from_boxes(map, bv, boxes, achv);

    map->subset_palette = representative_subset;
    adjust_histogram(achv, map, bv, boxes);

    return map;
}