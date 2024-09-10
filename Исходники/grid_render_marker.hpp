void render_raster_marker(RendererType ren,
                          RasterizerType & ras,
                          image_data_rgba8 & src,
                          mapnik::feature_impl const& feature,
                          agg::trans_affine const& marker_tr,
                          double opacity)
{
    using color_type = typename RendererType::color_type;
    agg::scanline_bin sl;
    double width  = src.width();
    double height = src.height();
    double p[8];
    p[0] = 0;     p[1] = 0;
    p[2] = width; p[3] = 0;
    p[4] = width; p[5] = height;
    p[6] = 0;     p[7] = height;
    marker_tr.transform(&p[0], &p[1]);
    marker_tr.transform(&p[2], &p[3]);
    marker_tr.transform(&p[4], &p[5]);
    marker_tr.transform(&p[6], &p[7]);
    ras.move_to_d(p[0],p[1]);
    ras.line_to_d(p[2],p[3]);
    ras.line_to_d(p[4],p[5]);
    ras.line_to_d(p[6],p[7]);
    ren.color(color_type(feature.id()));
    agg::render_scanlines(ras, sl, ren);
}