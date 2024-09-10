void NRStyle::applyStroke(Inkscape::DrawingContext &dc)
{
    dc.setSource(stroke_pattern);
    dc.setLineWidth(stroke_width);
    dc.setLineCap(line_cap);
    dc.setLineJoin(line_join);
    dc.setMiterLimit(miter_limit);
    cairo_set_dash(dc.raw(), dash, n_dash, dash_offset); // fixme
}