 void render_raster_marker(agg::trans_affine const& marker_tr)
 {
     double width  = src_.width();
     double height = src_.height();
     double p[8];
     p[0] = 0;     p[1] = 0;
     p[2] = width; p[3] = 0;
     p[4] = width; p[5] = height;
     p[6] = 0;     p[7] = height;
     marker_tr.transform(&p[0], &p[1]);
     marker_tr.transform(&p[2], &p[3]);
     marker_tr.transform(&p[4], &p[5]);
     marker_tr.transform(&p[6], &p[7]);
     ras_.move_to_d(p[0],p[1]);
     ras_.line_to_d(p[2],p[3]);
     ras_.line_to_d(p[4],p[5]);
     ras_.line_to_d(p[6],p[7]);
     RendererType ren(renb_);
     ren.color(color_type(feature_.id()));
     agg::render_scanlines(ras_, sl_, ren);
 }