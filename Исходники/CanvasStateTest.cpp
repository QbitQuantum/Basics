DEF_TEST(CanvasState_test_complex_clips, reporter) {
    const int WIDTH = 400;
    const int HEIGHT = 400;
    const int SPACER = 10;

    SkIRect layerRect = SkIRect::MakeWH(WIDTH, HEIGHT / 4);
    layerRect.inset(2*SPACER, 2*SPACER);

    SkIRect clipRect = layerRect;
    clipRect.fRight = clipRect.fLeft + (clipRect.width() / 2) - (2*SPACER);
    clipRect.outset(SPACER, SPACER);

    SkIRect regionBounds = clipRect;
    regionBounds.offset(clipRect.width() + (2*SPACER), 0);

    SkIRect regionInterior = regionBounds;
    regionInterior.inset(SPACER*3, SPACER*3);

    SkRegion clipRegion;
    clipRegion.setRect(regionBounds);
    clipRegion.op(regionInterior, SkRegion::kDifference_Op);


    const SkRegion::Op clipOps[] = { SkRegion::kIntersect_Op,
                                     SkRegion::kIntersect_Op,
                                     SkRegion::kReplace_Op,
    };
    const SkCanvas::SaveLayerFlags flags[] = {
        static_cast<SkCanvas::SaveLayerFlags>(SkCanvas::kDontClipToLayer_Legacy_SaveLayerFlag),
        0,
        static_cast<SkCanvas::SaveLayerFlags>(SkCanvas::kDontClipToLayer_Legacy_SaveLayerFlag),
    };
    REPORTER_ASSERT(reporter, sizeof(clipOps) == sizeof(flags));

    bool (*drawFn)(SkCanvasState* state, int32_t l, int32_t t,
                   int32_t r, int32_t b, int32_t clipOp,
                   int32_t regionRects, int32_t* rectCoords);

    OpenLibResult openLibResult(reporter);
    if (openLibResult.handle() != nullptr) {
        *(void**) (&drawFn) = dlsym(openLibResult.handle(),
                                    "complex_clips_draw_from_canvas_state");
    } else {
        drawFn = complex_clips_draw_from_canvas_state;
    }

    REPORTER_ASSERT(reporter, drawFn);
    if (!drawFn) {
        return;
    }

    SkBitmap bitmaps[2];
    for (int i = 0; i < 2; ++i) {
        bitmaps[i].allocN32Pixels(WIDTH, HEIGHT);

        SkCanvas canvas(bitmaps[i]);

        canvas.drawColor(SK_ColorRED);

        SkRegion localRegion = clipRegion;

        SkPaint paint;
        paint.setAlpha(128);
        for (size_t j = 0; j < SK_ARRAY_COUNT(flags); ++j) {
            SkRect layerBounds = SkRect::Make(layerRect);
            canvas.saveLayer(SkCanvas::SaveLayerRec(&layerBounds, &paint, flags[j]));

            if (i) {
                SkCanvasState* state = SkCanvasStateUtils::CaptureCanvasState(&canvas);
                REPORTER_ASSERT(reporter, state);

                SkRegion::Iterator iter(localRegion);
                SkTDArray<int32_t> rectCoords;
                for (; !iter.done(); iter.next()) {
                    const SkIRect& rect = iter.rect();
                    *rectCoords.append() = rect.fLeft;
                    *rectCoords.append() = rect.fTop;
                    *rectCoords.append() = rect.fRight;
                    *rectCoords.append() = rect.fBottom;
                }
                bool success = drawFn(state, clipRect.fLeft, clipRect.fTop,
                                      clipRect.fRight, clipRect.fBottom, clipOps[j],
                                      rectCoords.count() / 4, rectCoords.begin());
                REPORTER_ASSERT(reporter, success);

                SkCanvasStateUtils::ReleaseCanvasState(state);
            } else {
                complex_clips_draw(&canvas, clipRect.fLeft, clipRect.fTop,
                                   clipRect.fRight, clipRect.fBottom, clipOps[j],
                                   localRegion);
            }

            canvas.restore();

            // translate the canvas and region for the next iteration
            canvas.translate(0, SkIntToScalar(2*(layerRect.height() + (SPACER))));
            localRegion.translate(0, 2*(layerRect.height() + SPACER));
        }
    }

    // now we memcmp the two bitmaps
    REPORTER_ASSERT(reporter, bitmaps[0].getSize() == bitmaps[1].getSize());
    REPORTER_ASSERT(reporter, !memcmp(bitmaps[0].getPixels(),
                                      bitmaps[1].getPixels(),
                                      bitmaps[0].getSize()));
}