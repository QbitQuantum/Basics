void SVGResourceClipper::applyClip(GraphicsContext* context, const FloatRect& boundingBox) const
{
    if (m_clipData.clipData().isEmpty())
        return;

    bool heterogenousClipRules = false;
    WindRule clipRule = m_clipData.clipData()[0].windRule;

    context->beginPath();

    for (unsigned x = 0; x < m_clipData.clipData().size(); x++) {
        ClipData clipData = m_clipData.clipData()[x];
        if (clipData.windRule != clipRule)
            heterogenousClipRules = true;
        
        Path clipPath = clipData.path;

        if (clipData.bboxUnits) {
            AffineTransform transform;
            transform.translate(boundingBox.x(), boundingBox.y());
            transform.scale(boundingBox.width(), boundingBox.height());
            clipPath.transform(transform);
        }
        context->addPath(clipPath);
    }

    // FIXME!
    // We don't currently allow for heterogenous clip rules.
    // we would have to detect such, draw to a mask, and then clip
    // to that mask
    context->clipPath(clipRule);
}