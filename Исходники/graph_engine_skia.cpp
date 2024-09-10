void mbe_stroke(mbe_t *canvas) {
    SkPath *path = canvas->path;
    SkPaint *paint = canvas->paint;

    ASSERT(ptn);
    ASSERT(path);
    ASSERT(paint);

    if(!canvas->subpath->isEmpty())
	_update_path(canvas);

    _prepare_paint(canvas, SkPaint::kStroke_Style);

    canvas->canvas->drawPath(*path, *paint);

    _finish_paint(canvas);

    path->rewind();
    canvas->subpath->rewind();
}