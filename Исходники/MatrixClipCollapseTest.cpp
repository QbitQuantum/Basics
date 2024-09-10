// TODO: expand the testing to include the different ops & AA types!
static void emit_clip(SkCanvas* canvas, ClipType clip) {
    switch (clip) {
        case kNone_ClipType:
            break;
        case kRect_ClipType: {
            SkRect r = SkRect::MakeLTRB(10, 10, 90, 90);
            canvas->clipRect(r, SkRegion::kIntersect_Op, true);
            break;
        }
        case kRRect_ClipType: {
            SkRect r = SkRect::MakeLTRB(10, 10, 90, 90);
            SkRRect rr;
            rr.setRectXY(r, 10, 10);
            canvas->clipRRect(rr, SkRegion::kIntersect_Op, true);
            break;
        }
        case kPath_ClipType: {
            SkPath p;
            p.moveTo(5.0f, 5.0f);
            p.lineTo(50.0f, 50.0f);
            p.lineTo(100.0f, 5.0f);
            p.close();
            canvas->clipPath(p, SkRegion::kIntersect_Op, true);
            break;
        }
        case kRegion_ClipType: {
            SkIRect rects[2] = {
                { 1, 1, 55, 55 },
                { 45, 45, 99, 99 },
            };
            SkRegion r;
            r.setRects(rects, 2);
            canvas->clipRegion(r, SkRegion::kIntersect_Op);
            break;
        }
        default:
            SkASSERT(0);
    }
}