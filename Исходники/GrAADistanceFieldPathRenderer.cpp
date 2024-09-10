    bool addPathToAtlas(GrVertexBatch::Target* target,
                        FlushInfo* flushInfo,
                        GrBatchAtlas* atlas,
                        ShapeData* shapeData,
                        const GrShape& shape,
                        bool antiAlias,
                        uint32_t dimension,
                        SkScalar scale) const {
        const SkRect& bounds = shape.bounds();

        // generate bounding rect for bitmap draw
        SkRect scaledBounds = bounds;
        // scale to mip level size
        scaledBounds.fLeft *= scale;
        scaledBounds.fTop *= scale;
        scaledBounds.fRight *= scale;
        scaledBounds.fBottom *= scale;
        // move the origin to an integer boundary (gives better results)
        SkScalar dx = SkScalarFraction(scaledBounds.fLeft);
        SkScalar dy = SkScalarFraction(scaledBounds.fTop);
        scaledBounds.offset(-dx, -dy);
        // get integer boundary
        SkIRect devPathBounds;
        scaledBounds.roundOut(&devPathBounds);
        // pad to allow room for antialiasing
        const int intPad = SkScalarCeilToInt(kAntiAliasPad);
        // pre-move origin (after outset, will be 0,0)
        int width = devPathBounds.width();
        int height = devPathBounds.height();
        devPathBounds.fLeft = intPad;
        devPathBounds.fTop = intPad;
        devPathBounds.fRight = intPad + width;
        devPathBounds.fBottom = intPad + height;
        devPathBounds.outset(intPad, intPad);

        // draw path to bitmap
        SkMatrix drawMatrix;
        drawMatrix.setTranslate(-bounds.left(), -bounds.top());
        drawMatrix.postScale(scale, scale);
        drawMatrix.postTranslate(kAntiAliasPad, kAntiAliasPad);

        // setup bitmap backing
        SkASSERT(devPathBounds.fLeft == 0);
        SkASSERT(devPathBounds.fTop == 0);
        SkAutoPixmapStorage dst;
        if (!dst.tryAlloc(SkImageInfo::MakeA8(devPathBounds.width(),
                                              devPathBounds.height()))) {
            return false;
        }
        sk_bzero(dst.writable_addr(), dst.getSafeSize());

        // rasterize path
        SkPaint paint;
        paint.setStyle(SkPaint::kFill_Style);
        paint.setAntiAlias(antiAlias);

        SkDraw draw;
        sk_bzero(&draw, sizeof(draw));

        SkRasterClip rasterClip;
        rasterClip.setRect(devPathBounds);
        draw.fRC = &rasterClip;
        draw.fMatrix = &drawMatrix;
        draw.fDst = dst;

        SkPath path;
        shape.asPath(&path);
        draw.drawPathCoverage(path, paint);

        // generate signed distance field
        devPathBounds.outset(SK_DistanceFieldPad, SK_DistanceFieldPad);
        width = devPathBounds.width();
        height = devPathBounds.height();
        // TODO We should really generate this directly into the plot somehow
        SkAutoSMalloc<1024> dfStorage(width * height * sizeof(unsigned char));

        // Generate signed distance field
        SkGenerateDistanceFieldFromA8Image((unsigned char*)dfStorage.get(),
                                           (const unsigned char*)dst.addr(),
                                           dst.width(), dst.height(), dst.rowBytes());

        // add to atlas
        SkIPoint16 atlasLocation;
        GrBatchAtlas::AtlasID id;
       if (!atlas->addToAtlas(&id, target, width, height, dfStorage.get(), &atlasLocation)) {
            this->flush(target, flushInfo);
            if (!atlas->addToAtlas(&id, target, width, height, dfStorage.get(), &atlasLocation)) {
                return false;
            }
        }

        // add to cache
        shapeData->fKey.set(shape, dimension);
        shapeData->fScale = scale;
        shapeData->fID = id;
        // change the scaled rect to match the size of the inset distance field
        scaledBounds.fRight = scaledBounds.fLeft +
            SkIntToScalar(devPathBounds.width() - 2*SK_DistanceFieldInset);
        scaledBounds.fBottom = scaledBounds.fTop +
            SkIntToScalar(devPathBounds.height() - 2*SK_DistanceFieldInset);
        // shift the origin to the correct place relative to the distance field
        // need to also restore the fractional translation
        scaledBounds.offset(-SkIntToScalar(SK_DistanceFieldInset) - kAntiAliasPad + dx,
                            -SkIntToScalar(SK_DistanceFieldInset) - kAntiAliasPad + dy);
        shapeData->fBounds = scaledBounds;
        // origin we render from is inset from distance field edge
        atlasLocation.fX += SK_DistanceFieldInset;
        atlasLocation.fY += SK_DistanceFieldInset;
        shapeData->fAtlasLocation = atlasLocation;

        fShapeCache->add(shapeData);
        fShapeList->addToTail(shapeData);
#ifdef DF_PATH_TRACKING
        ++g_NumCachedPaths;
#endif
        return true;
    }