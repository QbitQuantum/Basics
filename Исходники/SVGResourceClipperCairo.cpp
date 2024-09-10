void SVGResourceClipper::applyClip(GraphicsContext* context, const FloatRect& boundingBox) const
{
    cairo_t* cr = context->platformContext();
    if (m_clipData.clipData().size() < 1)
        return;

    cairo_reset_clip(cr);
    context->beginPath();

    for (unsigned int x = 0; x < m_clipData.clipData().size(); x++) {
        ClipData data = m_clipData.clipData()[x];

        Path path = data.path;
        if (path.isEmpty())
            continue;
        path.closeSubpath();

        if (data.bboxUnits) {
            // Make use of the clipping units
            AffineTransform transform;
            transform.translate(boundingBox.x(), boundingBox.y());
            transform.scale(boundingBox.width(), boundingBox.height());
            path.transform(transform);
        }
        cairo_path_t* clipPath = cairo_copy_path(path.platformPath()->m_cr);
        cairo_append_path(cr, clipPath);

        cairo_set_fill_rule(cr, data.windRule == RULE_EVENODD ? CAIRO_FILL_RULE_EVEN_ODD : CAIRO_FILL_RULE_WINDING);
    }

    cairo_clip(cr);
}