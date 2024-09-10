void cairo_context::add_image(agg::trans_affine const& tr, image_rgba8 const& data, double opacity)
{
    cairo_pattern pattern(data);
    if (!tr.is_identity())
    {
        double m[6];
        tr.store_to(m);
        cairo_matrix_t cairo_matrix;
        cairo_matrix_init(&cairo_matrix,m[0],m[1],m[2],m[3],m[4],m[5]);
        cairo_matrix_invert(&cairo_matrix);
        pattern.set_matrix(cairo_matrix);
    }
    cairo_save(cairo_.get());
    cairo_set_source(cairo_.get(), const_cast<cairo_pattern_t*>(pattern.pattern()));
    cairo_paint_with_alpha(cairo_.get(), opacity);
    cairo_restore(cairo_.get());
    check_object_status_and_throw_exception(*this);
}