    void render_raster_marker(agg::trans_affine const& marker_tr,
                              double opacity)
    {
        using pixfmt_pre = agg::pixfmt_rgba32_pre;
        agg::scanline_u8 sl_;
        double width  = src_.width();
        double height = src_.height();
        if (std::fabs(1.0 - scale_factor_) < 0.001
            && (std::fabs(1.0 - marker_tr.sx) < agg::affine_epsilon)
            && (std::fabs(0.0 - marker_tr.shy) < agg::affine_epsilon)
            && (std::fabs(0.0 - marker_tr.shx) < agg::affine_epsilon)
            && (std::fabs(1.0 - marker_tr.sy) < agg::affine_epsilon))
        {
            agg::rendering_buffer src_buffer((unsigned char *)src_.getBytes(),src_.width(),src_.height(),src_.width() * 4);
            pixfmt_pre pixf_mask(src_buffer);
            if (snap_to_pixels_)
            {
                renb_.blend_from(pixf_mask,
                                 0,
                                 std::floor(marker_tr.tx + .5),
                                 std::floor(marker_tr.ty + .5),
                                 unsigned(255*opacity));
            }
            else
            {
                renb_.blend_from(pixf_mask,
                                 0,
                                 marker_tr.tx,
                                 marker_tr.ty,
                                 unsigned(255*opacity));
            }
        }
        else
        {
            using img_accessor_type = agg::image_accessor_clone<pixfmt_pre>;
            using interpolator_type = agg::span_interpolator_linear<>;
            //using span_gen_type = agg::span_image_filter_rgba_2x2<img_accessor_type,interpolator_type>;
            using span_gen_type = agg::span_image_resample_rgba_affine<img_accessor_type>;
            using renderer_type = agg::renderer_scanline_aa_alpha<renderer_base,
                                                                  agg::span_allocator<color_type>,
                                                                  span_gen_type>;

            double p[8];
            p[0] = 0;     p[1] = 0;
            p[2] = width; p[3] = 0;
            p[4] = width; p[5] = height;
            p[6] = 0;     p[7] = height;
            marker_tr.transform(&p[0], &p[1]);
            marker_tr.transform(&p[2], &p[3]);
            marker_tr.transform(&p[4], &p[5]);
            marker_tr.transform(&p[6], &p[7]);
            agg::span_allocator<color_type> sa;
            agg::image_filter_lut filter;
            filter.calculate(agg::image_filter_bilinear(), true);
            agg::rendering_buffer marker_buf((unsigned char *)src_.getBytes(),
                                             src_.width(),
                                             src_.height(),
                                             src_.width()*4);
            pixfmt_pre pixf(marker_buf);
            img_accessor_type ia(pixf);
            agg::trans_affine final_tr(p, 0, 0, width, height);
            if (snap_to_pixels_)
            {
                final_tr.tx = std::floor(final_tr.tx+.5);
                final_tr.ty = std::floor(final_tr.ty+.5);
            }
            interpolator_type interpolator(final_tr);
            span_gen_type sg(ia, interpolator, filter);
            renderer_type rp(renb_,sa, sg, unsigned(opacity*255));
            ras_.move_to_d(p[0],p[1]);
            ras_.line_to_d(p[2],p[3]);
            ras_.line_to_d(p[4],p[5]);
            ras_.line_to_d(p[6],p[7]);
            agg::render_scanlines(ras_, sl_, rp);
        }
    }