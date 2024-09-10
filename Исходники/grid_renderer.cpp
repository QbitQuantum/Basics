void grid_renderer<T>::render_marker(mapnik::feature_impl & feature, unsigned int step, pixel_position const& pos, marker const& marker, agg::trans_affine const& tr, double opacity, composite_mode_e comp_op)
{
    if (marker.is_vector())
    {
        typedef coord_transform<CoordTransform,geometry_type> path_type;
        typedef agg::renderer_base<mapnik::pixfmt_gray32> ren_base;
        typedef agg::renderer_scanline_bin_solid<ren_base> renderer;
        agg::scanline_bin sl;

        grid_rendering_buffer buf(pixmap_.raw_data(), width_, height_, width_);
        mapnik::pixfmt_gray32 pixf(buf);

        ren_base renb(pixf);
        renderer ren(renb);

        ras_ptr->reset();

        box2d<double> const& bbox = (*marker.get_vector_data())->bounding_box();
        coord<double,2> c = bbox.center();
        // center the svg marker on '0,0'
        agg::trans_affine mtx = agg::trans_affine_translation(-c.x,-c.y);
        // apply symbol transformation to get to map space
        mtx *= tr;
        mtx *= agg::trans_affine_scaling(scale_factor_*(1.0/step));
        // render the marker at the center of the marker box
        mtx.translate(pos.x, pos.y);
        using namespace mapnik::svg;
        vertex_stl_adapter<svg_path_storage> stl_storage((*marker.get_vector_data())->source());
        svg_path_adapter svg_path(stl_storage);
        svg_renderer_agg<svg_path_adapter,
            agg::pod_bvector<path_attributes>,
            renderer,
            mapnik::pixfmt_gray32> svg_renderer(svg_path,
                                                (*marker.get_vector_data())->attributes());

        svg_renderer.render_id(*ras_ptr, sl, renb, feature.id(), mtx, opacity, bbox);

    }
    else
    {
        image_data_32 const& data = **marker.get_bitmap_data();
        double width = data.width();
        double height = data.height();
        double cx = 0.5 * width;
        double cy = 0.5 * height;
        if (step == 1 && (std::fabs(1.0 - scale_factor_) < 0.001 && tr.is_identity()))
        {
            // TODO - support opacity
            pixmap_.set_rectangle(feature.id(), data,
                                  boost::math::iround(pos.x - cx),
                                  boost::math::iround(pos.y - cy));
        }
        else
        {
            // TODO - remove support for step != or add support for agg scaling with opacity
            double ratio = (1.0/step);
            image_data_32 target(ratio * data.width(), ratio * data.height());
            mapnik::scale_image_agg<image_data_32>(target,data, SCALING_NEAR,
                                                   scale_factor_, 0.0, 0.0, 1.0, ratio);
            pixmap_.set_rectangle(feature.id(), target,
                                  boost::math::iround(pos.x - cx),
                                  boost::math::iround(pos.y - cy));
        }
    }
    pixmap_.add_feature(feature);
}