void LinkHighlightImpl::paintContents(WebDisplayItemList* webDisplayItemList, const WebRect& webClipRect, WebContentLayerClient::PaintingControlSetting paintingControl)
{
    if (!m_node || !m_node->layoutObject())
        return;

    SkPictureRecorder recorder;
    SkCanvas* canvas = recorder.beginRecording(webClipRect.width, webClipRect.height);
    canvas->translate(-webClipRect.x, -webClipRect.y);

    SkPaint paint;
    paint.setStyle(SkPaint::kFill_Style);
    paint.setFlags(SkPaint::kAntiAlias_Flag);
    paint.setColor(m_node->layoutObject()->style()->tapHighlightColor().rgb());
    canvas->drawPath(m_path.skPath(), paint);

    RefPtr<const SkPicture> picture = adoptRef(recorder.endRecording());
    // TODO(wkorman): Pass actual visual rect with the drawing item.
    webDisplayItemList->appendDrawingItem(IntRect(), picture.get());
}