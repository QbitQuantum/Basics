void
dt_view_image_expose(
    dt_view_image_over_t *image_over,
    uint32_t imgid,
    cairo_t *cr,
    int32_t width,
    int32_t height,
    int32_t zoom,
    int32_t px,
    int32_t py)
{
    const double start = dt_get_wtime();
    // some performance tuning stuff, for your pleasure.
    // on my machine with 7 image per row it seems grouping has the largest
    // impact from around 400ms -> 55ms per redraw.
#define DRAW_THUMB 1
#define DRAW_COLORLABELS 1
#define DRAW_GROUPING 1
#define DRAW_SELECTED 1
#define DRAW_HISTORY 1

#if DRAW_THUMB == 1
    // this function is not thread-safe (gui-thread only), so we
    // can safely allocate this leaking bit of memory to decompress thumbnails:
    static int first_time = 1;
    static uint8_t *scratchmem = NULL;
    if(first_time)
    {
        // scratchmem might still be NULL after this, if compression is off.
        scratchmem = dt_mipmap_cache_alloc_scratchmem(darktable.mipmap_cache);
        first_time = 0;
    }
#endif

    cairo_save (cr);
    float bgcol = 0.4, fontcol = 0.425, bordercol = 0.1, outlinecol = 0.2;
    int selected = 0, altered = 0, imgsel = -1, is_grouped = 0;
    // this is a gui thread only thing. no mutex required:
    imgsel = darktable.control->global_settings.lib_image_mouse_over_id;

#if DRAW_SELECTED == 1
    /* clear and reset statements */
    DT_DEBUG_SQLITE3_CLEAR_BINDINGS(darktable.view_manager->statements.is_selected);
    DT_DEBUG_SQLITE3_RESET(darktable.view_manager->statements.is_selected);
    /* bind imgid to prepared statments */
    DT_DEBUG_SQLITE3_BIND_INT(darktable.view_manager->statements.is_selected, 1, imgid);
    /* lets check if imgid is selected */
    if(sqlite3_step(darktable.view_manager->statements.is_selected) == SQLITE_ROW)
        selected = 1;
#endif

#if DRAW_HISTORY == 1
    DT_DEBUG_SQLITE3_CLEAR_BINDINGS(darktable.view_manager->statements.have_history);
    DT_DEBUG_SQLITE3_RESET(darktable.view_manager->statements.have_history);
    DT_DEBUG_SQLITE3_BIND_INT(darktable.view_manager->statements.have_history, 1, imgid);

    /* lets check if imgid has history */
    if(sqlite3_step(darktable.view_manager->statements.have_history) == SQLITE_ROW)
        altered = 1;
#endif

    const dt_image_t *img = dt_image_cache_read_testget(darktable.image_cache, imgid);

#if DRAW_GROUPING == 1
    DT_DEBUG_SQLITE3_CLEAR_BINDINGS(darktable.view_manager->statements.get_grouped);
    DT_DEBUG_SQLITE3_RESET(darktable.view_manager->statements.get_grouped);
    DT_DEBUG_SQLITE3_BIND_INT(darktable.view_manager->statements.get_grouped, 1, imgid);
    DT_DEBUG_SQLITE3_BIND_INT(darktable.view_manager->statements.get_grouped, 2, imgid);

    /* lets check if imgid is in a group */
    if(sqlite3_step(darktable.view_manager->statements.get_grouped) == SQLITE_ROW)
        is_grouped = 1;
    else if(img && darktable.gui->expanded_group_id == img->group_id)
        darktable.gui->expanded_group_id = -1;
#endif

    if(selected == 1)
    {
        outlinecol = 0.4;
        bgcol = 0.6;
        fontcol = 0.5;
    }
    if(imgsel == imgid)
    {
        bgcol = 0.8;  // mouse over
        fontcol = 0.7;
        outlinecol = 0.6;
        // if the user points at this image, we really want it:
        if(!img)
            img = dt_image_cache_read_get(darktable.image_cache, imgid);
    }
    float imgwd = 0.90f;
    if(zoom == 1)
    {
        imgwd = .97f;
        // cairo_set_antialias(cr, CAIRO_ANTIALIAS_NONE);
    }
    else
    {
        double x0 = 1, y0 = 1, rect_width = width-2, rect_height = height-2, radius = 5;
        double x1, y1, off, off1;

        x1=x0+rect_width;
        y1=y0+rect_height;
        off=radius*0.666;
        off1 = radius-off;
        cairo_move_to  (cr, x0, y0 + radius);
        cairo_curve_to (cr, x0, y0+off1, x0+off1 , y0, x0 + radius, y0);
        cairo_line_to (cr, x1 - radius, y0);
        cairo_curve_to (cr, x1-off1, y0, x1, y0+off1, x1, y0 + radius);
        cairo_line_to (cr, x1 , y1 - radius);
        cairo_curve_to (cr, x1, y1-off1, x1-off1, y1, x1 - radius, y1);
        cairo_line_to (cr, x0 + radius, y1);
        cairo_curve_to (cr, x0+off1, y1, x0, y1-off1, x0, y1- radius);
        cairo_close_path (cr);
        cairo_set_source_rgb(cr, bgcol, bgcol, bgcol);
        cairo_fill_preserve(cr);
        cairo_set_line_width(cr, 0.005*width);
        cairo_set_source_rgb(cr, outlinecol, outlinecol, outlinecol);
        cairo_stroke(cr);

        if(img)
        {
            const char *ext = img->filename + strlen(img->filename);
            while(ext > img->filename && *ext != '.') ext--;
            ext++;
            cairo_set_source_rgb(cr, fontcol, fontcol, fontcol);
            cairo_select_font_face (cr, "sans-serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
            cairo_set_font_size (cr, .25*width);
            cairo_text_extents_t text_extends;
            cairo_text_extents (cr, ext, &text_extends);
            cairo_move_to (cr, .025*width - text_extends.x_bearing, .24*height);
            cairo_show_text (cr, ext);
        }
    }

    dt_mipmap_buffer_t buf;
    dt_mipmap_size_t mip =
        dt_mipmap_cache_get_matching_size(
            darktable.mipmap_cache,
            imgwd*width, imgwd*height);
    dt_mipmap_cache_read_get(
        darktable.mipmap_cache,
        &buf,
        imgid,
        mip,
        0);
#if DRAW_THUMB == 1
    float scale = 1.0;
    // decompress image, if necessary. if compression is off, scratchmem will be == NULL,
    // so get the real pointer back:
    uint8_t *buf_decompressed = dt_mipmap_cache_decompress(&buf, scratchmem);

    cairo_surface_t *surface = NULL;
    if(buf.buf)
    {
        const int32_t stride = cairo_format_stride_for_width (CAIRO_FORMAT_RGB24, buf.width);
        surface = cairo_image_surface_create_for_data (buf_decompressed, CAIRO_FORMAT_RGB24, buf.width, buf.height, stride);
        if(zoom == 1)
        {
            scale = fminf(
                        fminf(darktable.thumbnail_width, width) / (float)buf.width,
                        fminf(darktable.thumbnail_height, height) / (float)buf.height
                    );
        }
        else scale = fminf(width*imgwd/(float)buf.width, height*imgwd/(float)buf.height);
    }

    // draw centered and fitted:
    cairo_save(cr);
    cairo_translate(cr, width/2.0, height/2.0f);
    cairo_scale(cr, scale, scale);

    if(buf.buf)
    {
        cairo_translate(cr, -.5f*buf.width, -.5f*buf.height);
        cairo_set_source_surface (cr, surface, 0, 0);
        // set filter no nearest:
        // in skull mode, we want to see big pixels.
        // in 1 iir mode for the right mip, we want to see exactly what the pipe gave us, 1:1 pixel for pixel.
        // in between, filtering just makes stuff go unsharp.
        if((buf.width <= 8 && buf.height <= 8) || fabsf(scale - 1.0f) < 0.01f)
            cairo_pattern_set_filter(cairo_get_source(cr), CAIRO_FILTER_NEAREST);
        cairo_rectangle(cr, 0, 0, buf.width, buf.height);
        cairo_fill(cr);
        cairo_surface_destroy (surface);

        cairo_rectangle(cr, 0, 0, buf.width, buf.height);
    }

    // border around image
    const float border = zoom == 1 ? 16/scale : 2/scale;
    cairo_set_source_rgb(cr, bordercol, bordercol, bordercol);
    if(buf.buf && selected)
    {
        cairo_set_line_width(cr, 1./scale);
        if(zoom == 1)
        {
            // draw shadow around border
            cairo_set_source_rgb(cr, 0.2, 0.2, 0.2);
            cairo_stroke(cr);
            // cairo_new_path(cr);
            cairo_set_fill_rule (cr, CAIRO_FILL_RULE_EVEN_ODD);
            float alpha = 1.0f;
            for(int k=0; k<16; k++)
            {
                cairo_rectangle(cr, 0, 0, buf.width, buf.height);
                cairo_new_sub_path(cr);
                cairo_rectangle(cr, -k/scale, -k/scale, buf.width+2.*k/scale, buf.height+2.*k/scale);
                cairo_set_source_rgba(cr, 0, 0, 0, alpha);
                alpha *= 0.6f;
                cairo_fill(cr);
            }
        }
        else
        {
            cairo_set_fill_rule (cr, CAIRO_FILL_RULE_EVEN_ODD);
            cairo_new_sub_path(cr);
            cairo_rectangle(cr, -border, -border, buf.width+2.*border, buf.height+2.*border);
            cairo_stroke_preserve(cr);
            cairo_set_source_rgb(cr, 1.0-bordercol, 1.0-bordercol, 1.0-bordercol);
            cairo_fill(cr);
        }
    }
    else if(buf.buf)
    {
        cairo_set_line_width(cr, 1);
        cairo_stroke(cr);
    }
    cairo_restore(cr);
#endif
    if(buf.buf)
        dt_mipmap_cache_read_release(darktable.mipmap_cache, &buf);

    const float fscale = fminf(width, height);
    if(imgsel == imgid)
    {
        // draw mouseover hover effects, set event hook for mouse button down!
        *image_over = DT_VIEW_DESERT;
        cairo_set_line_width(cr, 1.5);
        cairo_set_source_rgb(cr, outlinecol, outlinecol, outlinecol);
        cairo_set_line_join (cr, CAIRO_LINE_JOIN_ROUND);
        float r1, r2;
        if(zoom != 1)
        {
            r1 = 0.05*width;
            r2 = 0.022*width;
        }
        else
        {
            r1 = 0.015*fscale;
            r2 = 0.007*fscale;
        }

        float x, y;
        if(zoom != 1) y = 0.90*height;
        else y = .12*fscale;
        gboolean image_is_rejected = (img && ((img->flags & 0x7) == 6));

        if(img) for(int k=0; k<5; k++)
            {
                if(zoom != 1) x = (0.41+k*0.12)*width;
                else x = (.08+k*0.04)*fscale;

                if(!image_is_rejected) //if rejected: draw no stars
                {
                    dt_view_star(cr, x, y, r1, r2);
                    if((px - x)*(px - x) + (py - y)*(py - y) < r1*r1)
                    {
                        *image_over = DT_VIEW_STAR_1 + k;
                        cairo_fill(cr);
                    }
                    else if((img->flags & 0x7) > k)
                    {
                        cairo_fill_preserve(cr);
                        cairo_set_source_rgb(cr, 1.0-bordercol, 1.0-bordercol, 1.0-bordercol);
                        cairo_stroke(cr);
                        cairo_set_source_rgb(cr, outlinecol, outlinecol, outlinecol);
                    }
                    else cairo_stroke(cr);
                }
            }

        //Image rejected?
        if(zoom !=1) x = 0.11*width;
        else x = .04*fscale;

        if (image_is_rejected)
            cairo_set_source_rgb(cr, 1., 0., 0.);

        if((px - x)*(px - x) + (py - y)*(py - y) < r1*r1)
        {
            *image_over = DT_VIEW_REJECT; //mouse sensitive
            cairo_new_sub_path(cr);
            cairo_arc(cr, x, y, (r1+r2)*.5, 0, 2.0f*M_PI);
            cairo_stroke(cr);
        }

        if (image_is_rejected)
            cairo_set_line_width(cr, 2.5);

        //reject cross:
        cairo_move_to(cr, x-r2, y-r2);
        cairo_line_to(cr, x+r2, y+r2);
        cairo_move_to(cr, x+r2, y-r2);
        cairo_line_to(cr, x-r2, y+r2);
        cairo_close_path(cr);
        cairo_stroke(cr);
        cairo_set_source_rgb(cr, outlinecol, outlinecol, outlinecol);
        cairo_set_line_width(cr, 1.5);


        // image part of a group?
        if(is_grouped && darktable.gui && darktable.gui->grouping)
        {
            // draw grouping icon and border if the current group is expanded
            // align to the right, left of altered
            float s = (r1+r2)*.75;
            float _x, _y;
            if(zoom != 1)
            {
                _x = width*0.9 - s*2.5;
                _y = height*0.1 - s*.4;
            }
            else
            {
                _x = (.04+7*0.04-1.1*.04)*fscale;
                _y = y - (.17*.04)*fscale;
            }
            cairo_save(cr);
            if(img && (imgid != img->group_id))
                cairo_set_source_rgb(cr, fontcol, fontcol, fontcol);
            dtgtk_cairo_paint_grouping(cr, _x, _y, s, s, 23);
            cairo_restore(cr);
            // mouse is over the grouping icon
            if(img && abs(px-_x-.5*s) <= .8*s && abs(py-_y-.5*s) <= .8*s)
                *image_over = DT_VIEW_GROUP;
        }

        // image altered?
        if(altered)
        {
            // align to right
            float s = (r1+r2)*.5;
            if(zoom != 1)
            {
                x = width*0.9;
                y = height*0.1;
            }
            else x = (.04+7*0.04)*fscale;
            dt_view_draw_altered(cr, x, y, s);
            //g_print("px = %d, x = %.4f, py = %d, y = %.4f\n", px, x, py, y);
            if(img && abs(px-x) <= 1.2*s && abs(py-y) <= 1.2*s) // mouse hovers over the altered-icon -> history tooltip!
            {
                darktable.gui->center_tooltip = 1;
            }
        }
    }

    // kill all paths, in case img was not loaded yet, or is blocked:
    cairo_new_path(cr);

#if DRAW_COLORLABELS == 1
    // TODO: make mouse sensitive, just as stars!
    // TODO: cache in image struct!
    {
        // color labels:
        const float x = zoom == 1 ? (0.07)*fscale : .21*width;
        const float y = zoom == 1 ? 0.17*fscale: 0.1*height;
        const float r = zoom == 1 ? 0.01*fscale : 0.03*width;

        /* clear and reset prepared statement */
        DT_DEBUG_SQLITE3_CLEAR_BINDINGS(darktable.view_manager->statements.get_color);
        DT_DEBUG_SQLITE3_RESET(darktable.view_manager->statements.get_color);

        /* setup statement and iterate rows */
        DT_DEBUG_SQLITE3_BIND_INT(darktable.view_manager->statements.get_color, 1, imgid);
        while(sqlite3_step(darktable.view_manager->statements.get_color) == SQLITE_ROW)
        {
            cairo_save(cr);
            int col = sqlite3_column_int(darktable.view_manager->statements.get_color, 0);
            // see src/dtgtk/paint.c
            dtgtk_cairo_paint_label(cr, x+(3*r*col)-5*r, y-r, r*2, r*2, col);
            cairo_restore(cr);
        }
    }
#endif

    if(img && (zoom == 1))
    {
        // some exif data
        cairo_set_source_rgb(cr, .7, .7, .7);
        cairo_select_font_face (cr, "sans-serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
        cairo_set_font_size (cr, .025*fscale);

        cairo_move_to (cr, .02*fscale, .04*fscale);
        // cairo_show_text(cr, img->filename);
        cairo_text_path(cr, img->filename);
        char exifline[50];
        cairo_move_to (cr, .02*fscale, .08*fscale);
        dt_image_print_exif(img, exifline, 50);
        cairo_text_path(cr, exifline);
        cairo_fill_preserve(cr);
        cairo_set_line_width(cr, 1.0);
        cairo_set_source_rgb(cr, 0.3, 0.3, 0.3);
        cairo_stroke(cr);
    }

    if(img) dt_image_cache_read_release(darktable.image_cache, img);
    cairo_restore(cr);
    // if(zoom == 1) cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);

    const double end = dt_get_wtime();
    dt_print(DT_DEBUG_PERF, "[lighttable] image expose took %0.04f sec\n", end-start);
}