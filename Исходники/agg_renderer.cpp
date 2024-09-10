void agg_renderer<T0,T1>::render_marker(pixel_position const& pos,
                                    marker const& marker,
                                    agg::trans_affine const& tr,
                                    double opacity,
                                    composite_mode_e comp_op)
{
    using color_type = agg::rgba8;
    using order_type = agg::order_rgba;
    using blender_type = agg::comp_op_adaptor_rgba_pre<color_type, order_type>; // comp blender
    using pixfmt_comp_type = agg::pixfmt_custom_blend_rgba<blender_type, agg::rendering_buffer>;
    using renderer_base = agg::renderer_base<pixfmt_comp_type>;
    using renderer_type = agg::renderer_scanline_aa_solid<renderer_base>;
    using svg_attribute_type = agg::pod_bvector<mapnik::svg::path_attributes>;

    ras_ptr->reset();
    if (gamma_method_ != GAMMA_POWER || gamma_ != 1.0)
    {
        ras_ptr->gamma(agg::gamma_power());
        gamma_method_ = GAMMA_POWER;
        gamma_ = 1.0;
    }
    agg::scanline_u8 sl;
    agg::rendering_buffer buf(current_buffer_->raw_data(),
                              current_buffer_->width(),
                              current_buffer_->height(),
                              current_buffer_->width() * 4);
    pixfmt_comp_type pixf(buf);
    pixf.comp_op(static_cast<agg::comp_op_e>(comp_op));
    renderer_base renb(pixf);

    if (marker.is_vector())
    {
        box2d<double> const& bbox = (*marker.get_vector_data())->bounding_box();
        coord<double,2> c = bbox.center();
        // center the svg marker on '0,0'
        agg::trans_affine mtx = agg::trans_affine_translation(-c.x,-c.y);
        // apply symbol transformation to get to map space
        mtx *= tr;
        mtx *= agg::trans_affine_scaling(common_.scale_factor_);
        // render the marker at the center of the marker box
        mtx.translate(pos.x, pos.y);
        using namespace mapnik::svg;
        vertex_stl_adapter<svg_path_storage> stl_storage((*marker.get_vector_data())->source());
        svg_path_adapter svg_path(stl_storage);
        svg_renderer_agg<svg_path_adapter,
            svg_attribute_type,
            renderer_type,
            pixfmt_comp_type> svg_renderer(svg_path,
                                                   (*marker.get_vector_data())->attributes());

        svg_renderer.render(*ras_ptr, sl, renb, mtx, opacity, bbox);
    }
    else
    {
        double width = (*marker.get_bitmap_data())->width();
        double height = (*marker.get_bitmap_data())->height();
        if (std::fabs(1.0 - common_.scale_factor_) < 0.001 && tr.is_identity())
        {
            double cx = 0.5 * width;
            double cy = 0.5 * height;
            composite(current_buffer_->data(), **marker.get_bitmap_data(),
                      comp_op, opacity,
                      boost::math::iround(pos.x - cx),
                      boost::math::iround(pos.y - cy),
                      false);
        }
        else
        {

            double p[8];
            double x0 = pos.x - 0.5 * width;
            double y0 = pos.y - 0.5 * height;
            p[0] = x0;         p[1] = y0;
            p[2] = x0 + width; p[3] = y0;
            p[4] = x0 + width; p[5] = y0 + height;
            p[6] = x0;         p[7] = y0 + height;

            agg::trans_affine marker_tr;

            marker_tr *= agg::trans_affine_translation(-pos.x,-pos.y);
            marker_tr *= tr;
            marker_tr *= agg::trans_affine_scaling(common_.scale_factor_);
            marker_tr *= agg::trans_affine_translation(pos.x,pos.y);

            marker_tr.transform(&p[0], &p[1]);
            marker_tr.transform(&p[2], &p[3]);
            marker_tr.transform(&p[4], &p[5]);
            marker_tr.transform(&p[6], &p[7]);

            ras_ptr->move_to_d(p[0],p[1]);
            ras_ptr->line_to_d(p[2],p[3]);
            ras_ptr->line_to_d(p[4],p[5]);
            ras_ptr->line_to_d(p[6],p[7]);


            agg::span_allocator<color_type> sa;
            agg::image_filter_bilinear filter_kernel;
            agg::image_filter_lut filter(filter_kernel, false);

            image_data_32 const& src = **marker.get_bitmap_data();
            agg::rendering_buffer marker_buf((unsigned char *)src.getBytes(),
                                             src.width(),
                                             src.height(),
                                             src.width()*4);
            agg::pixfmt_rgba32_pre marker_pixf(marker_buf);
            using img_accessor_type = agg::image_accessor_clone<agg::pixfmt_rgba32_pre>;
            using interpolator_type = agg::span_interpolator_linear<agg::trans_affine>;
            using span_gen_type = agg::span_image_filter_rgba_2x2<img_accessor_type,
                                                                  interpolator_type>;
            using renderer_type = agg::renderer_scanline_aa_alpha<renderer_base,
                                                                  agg::span_allocator<agg::rgba8>,
                                                                  span_gen_type>;
            img_accessor_type ia(marker_pixf);
            interpolator_type interpolator(agg::trans_affine(p, 0, 0, width, height) );
            span_gen_type sg(ia, interpolator, filter);
            renderer_type rp(renb,sa, sg, unsigned(opacity*255));
            agg::render_scanlines(*ras_ptr, sl, rp);
        }
    }
}