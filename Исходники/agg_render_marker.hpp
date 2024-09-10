void render_raster_marker(RendererType renb, RasterizerType & ras, image_rgba8 const& src,
                          agg::trans_affine const& tr, double opacity,
                          float scale_factor, bool snap_to_pixels)
{
    using color_type = agg::rgba8;
    using const_rendering_buffer = util::rendering_buffer<image_rgba8>;
    using pixfmt_pre = agg::pixfmt_alpha_blend_rgba<agg::blender_rgba32_pre, const_rendering_buffer, agg::pixel32_type>;

    agg::scanline_u8 sl;
    double width  = src.width();
    double height = src.height();
    if (std::fabs(1.0 - scale_factor) < 0.001
        && (std::fabs(1.0 - tr.sx) < agg::affine_epsilon)
        && (std::fabs(0.0 - tr.shy) < agg::affine_epsilon)
        && (std::fabs(0.0 - tr.shx) < agg::affine_epsilon)
        && (std::fabs(1.0 - tr.sy) < agg::affine_epsilon))
    {
        const_rendering_buffer src_buffer(src);
        pixfmt_pre pixf_mask(src_buffer);
        if (snap_to_pixels)
        {
            renb.blend_from(pixf_mask,
                            0,
                            static_cast<int>(std::floor(tr.tx + .5)),
                            static_cast<int>(std::floor(tr.ty + .5)),
                            unsigned(255*opacity));
        }
        else
        {
            renb.blend_from(pixf_mask,
                            0,
                            static_cast<int>(tr.tx),
                            static_cast<int>(tr.ty),
                            unsigned(255*opacity));
        }
    }
    else
    {
        using img_accessor_type = agg::image_accessor_clone<pixfmt_pre>;
        using interpolator_type = agg::span_interpolator_linear<>;
        //using span_gen_type = agg::span_image_filter_rgba_2x2<img_accessor_type,interpolator_type>;
        using span_gen_type = agg::span_image_resample_rgba_affine<img_accessor_type>;
        using renderer_type = agg::renderer_scanline_aa_alpha<RendererType,
                                                              agg::span_allocator<color_type>,
                                                              span_gen_type>;

        double p[8];
        p[0] = 0;     p[1] = 0;
        p[2] = width; p[3] = 0;
        p[4] = width; p[5] = height;
        p[6] = 0;     p[7] = height;
        tr.transform(&p[0], &p[1]);
        tr.transform(&p[2], &p[3]);
        tr.transform(&p[4], &p[5]);
        tr.transform(&p[6], &p[7]);
        agg::span_allocator<color_type> sa;
        agg::image_filter_lut filter;
        filter.calculate(agg::image_filter_bilinear(), true);
        const_rendering_buffer src_buffer(src);
        pixfmt_pre pixf(src_buffer);
        img_accessor_type ia(pixf);
        agg::trans_affine final_tr(p, 0, 0, width, height);
        if (snap_to_pixels)
        {
            final_tr.tx = std::floor(final_tr.tx+.5);
            final_tr.ty = std::floor(final_tr.ty+.5);
        }
        interpolator_type interpolator(final_tr);
        span_gen_type sg(ia, interpolator, filter);
        renderer_type rp(renb, sa, sg, unsigned(opacity*255));
        ras.move_to_d(p[0],p[1]);
        ras.line_to_d(p[2],p[3]);
        ras.line_to_d(p[4],p[5]);
        ras.line_to_d(p[6],p[7]);
        agg::render_scanlines(ras, sl, rp);
    }
}