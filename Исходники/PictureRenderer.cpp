SkCanvas* TiledPictureRenderer::setupCanvas(int width, int height) {
    SkCanvas* canvas = this->INHERITED::setupCanvas(width, height);
    SkASSERT(fPicture);
    // Clip the tile to an area that is completely inside both the SkPicture and the viewport. This
    // is mostly important for tiles on the right and bottom edges as they may go over this area and
    // the picture may have some commands that draw outside of this area and so should not actually
    // be written.
    // Uses a clipRegion so that it will be unaffected by the scale factor, which may have been set
    // by INHERITED::setupCanvas.
    SkRegion clipRegion;
    clipRegion.setRect(0, 0, this->getViewWidth(), this->getViewHeight());
    canvas->clipRegion(clipRegion);
    return canvas;
}