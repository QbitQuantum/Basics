void ZLQtImageData::copyFrom(const ZLImageData &source, unsigned int targetX, unsigned int targetY) {
    bitBlt(this, targetX, targetY, (const ZLQtImageData*)&source, 0, 0);
}