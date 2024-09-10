void CaretBase::paintCaret(Node* node,
                           GraphicsContext& context,
                           const LayoutPoint& paintOffset,
                           DisplayItem::Type displayItemType) const {
    if (DrawingRecorder::useCachedDrawingIfPossible(context, *this,
            displayItemType))
        return;

    LayoutRect drawingRect = localCaretRectWithoutUpdate();
    if (LayoutBlock* layoutObject = caretLayoutObject(node))
        layoutObject->flipForWritingMode(drawingRect);
    drawingRect.moveBy(paintOffset);

    const Color caretColor = node->layoutObject()->resolveColor(CSSPropertyColor);
    IntRect paintRect = pixelSnappedIntRect(drawingRect);
    DrawingRecorder drawingRecorder(context, *this, DisplayItem::kCaret,
                                    paintRect);
    context.fillRect(paintRect, caretColor);
}