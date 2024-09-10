static gboolean
spectrogram_draw (GtkWidget *widget, cairo_t *cr, gpointer user_data) {
    w_spectrogram_t *w = user_data;
    GtkAllocation a;
    gtk_widget_get_allocation (widget, &a);
    if (!w->samples || a.height < 1) {
        return FALSE;
    }

    int width, height;
    width = a.width;
    height = a.height;
    int ratio = ftoi (FFT_SIZE/(a.height*2));
    ratio = CLAMP (ratio,0,1023);

    if (deadbeef->get_output ()->state () == OUTPUT_STATE_PLAYING) {
        do_fft (w);
        float log_scale = (log2f(w->samplerate/2)-log2f(25.))/(a.height);
        float freq_res = w->samplerate / FFT_SIZE;

        if (a.height != w->height) {
            w->height = MIN (a.height, MAX_HEIGHT);
            for (int i = 0; i < w->height; i++) {
                w->log_index[i] = ftoi (powf(2.,((float)i) * log_scale + log2f(25.)) / freq_res);
                if (i > 0 && w->log_index[i-1] == w->log_index [i]) {
                    w->low_res_end = i;
                }
            }
        }
    }

    // start drawing
    if (!w->surf || cairo_image_surface_get_width (w->surf) != a.width || cairo_image_surface_get_height (w->surf) != a.height) {
        if (w->surf) {
            cairo_surface_destroy (w->surf);
            w->surf = NULL;
        }
        w->surf = cairo_image_surface_create (CAIRO_FORMAT_RGB24, a.width, a.height);
    }

    cairo_surface_flush (w->surf);

    unsigned char *data = cairo_image_surface_get_data (w->surf);
    if (!data) {
        return FALSE;
    }
    int stride = cairo_image_surface_get_stride (w->surf);

    if (deadbeef->get_output ()->state () == OUTPUT_STATE_PLAYING) {
        for (int i = 0; i < a.height; i++) {
            // scrolling: move line i 1px to the left
            memmove (data + (i*stride), data + sizeof (uint32_t) + (i*stride), stride - sizeof (uint32_t));
        }

        for (int i = 0; i < a.height; i++)
        {
            float f = 1.0;
            int index0, index1;
            int bin0, bin1, bin2;
            if (CONFIG_LOG_SCALE) {
                bin0 = w->log_index[CLAMP (i-1,0,height-1)];
                bin1 = w->log_index[i];
                bin2 = w->log_index[CLAMP (i+1,0,height-1)];
            }
            else {
                bin0 = (i-1) * ratio;
                bin1 = i * ratio;
                bin2 = (i+1) * ratio;
            }

            index0 = bin0 + ftoi ((bin1 - bin0)/2.f);
            if (index0 == bin0) index0 = bin1;
            index1 = bin1 + ftoi ((bin2 - bin1)/2.f);
            if (index1 == bin2) index1 = bin1;

            index0 = CLAMP (index0,0,FFT_SIZE/2-1);
            index1 = CLAMP (index1,0,FFT_SIZE/2-1);

            f = spectrogram_get_value (w, index0, index1);
            float x = 10 * log10f (f);

            // interpolate
            if (i <= w->low_res_end && CONFIG_LOG_SCALE) {
                int j = 0;
                // find index of next value
                while (i+j < height && w->log_index[i+j] == w->log_index[i]) {
                    j++;
                }
                float v0 = x;
                float v1 = w->data[w->log_index[i+j]];
                if (v1 != 0) {
                    v1 = 10 * log10f (v1);
                }

                int k = 0;
                while ((k+i) >= 0 && w->log_index[k+i] == w->log_index[i]) {
                    j++;
                    k--;
                }
                x = linear_interpolate (v0,v1,(1.0/(j-1)) * ((-1 * k) - 1));
            }

            // TODO: get rid of hardcoding 
            x += CONFIG_DB_RANGE - 63;
            x = CLAMP (x, 0, CONFIG_DB_RANGE);
            int color_index = GRADIENT_TABLE_SIZE - ftoi (GRADIENT_TABLE_SIZE/(float)CONFIG_DB_RANGE * x);
            color_index = CLAMP (color_index, 0, GRADIENT_TABLE_SIZE-1);
            _draw_point (data, stride, width-1, height-1-i, w->colors[color_index]);
        }
    }
    cairo_surface_mark_dirty (w->surf);

    cairo_save (cr);
    cairo_set_source_surface (cr, w->surf, 0, 0);
    cairo_rectangle (cr, 0, 0, a.width, a.height);
    cairo_fill (cr);
    cairo_restore (cr);

    return FALSE;
}