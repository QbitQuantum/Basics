void LinkHighlight::paintContents(WebCanvas* canvas, const WebRect&, WebContentLayerClient::PaintingControlSetting paintingControl)
{
    if (!m_node || !m_node->layoutObject())
        return;

    SkPaint paint;
    paint.setStyle(SkPaint::kFill_Style);
    paint.setFlags(SkPaint::kAntiAlias_Flag);
    paint.setColor(m_node->layoutObject()->style()->tapHighlightColor().rgb());
    canvas->drawPath(m_path.skPath(), paint);
}