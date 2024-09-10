    void copyFromDevice(KisView2 *view, KisPaintDeviceSP device) {
        KisImageWSP image = view->image();
        KisSelectionSP selection = view->selection();

        QRect rc = (selection) ? selection->selectedExactRect() : image->bounds();

        KisPaintDeviceSP clip = new KisPaintDevice(device->colorSpace());
        Q_CHECK_PTR(clip);

        const KoColorSpace *cs = clip->colorSpace();

        // TODO if the source is linked... copy from all linked layers?!?

        // Copy image data
        KisPainter gc;
        gc.begin(clip);
        gc.setCompositeOp(COMPOSITE_COPY);
        gc.bitBlt(0, 0, device, rc.x(), rc.y(), rc.width(), rc.height());
        gc.end();

        if (selection) {
            // Apply selection mask.
            KisPaintDeviceSP selectionProjection = selection->projection();
            KisHLineIteratorSP layerIt = clip->createHLineIteratorNG(0, 0, rc.width());
            KisHLineConstIteratorSP selectionIt = selectionProjection->createHLineIteratorNG(rc.x(), rc.y(), rc.width());

            for (qint32 y = 0; y < rc.height(); y++) {

                for (qint32 x = 0; x < rc.width(); x++) {

                    cs->applyAlphaU8Mask(layerIt->rawData(), selectionIt->oldRawData(), 1);

                    layerIt->nextPixel();
                    selectionIt->nextPixel();
                }
                layerIt->nextRow();
                selectionIt->nextRow();
            }
        }

        KisClipboard::instance()->setClip(clip, rc.topLeft());
    }