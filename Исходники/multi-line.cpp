int
sk_test_multi_line(caskbench_context_t *ctx)
{
    int w = ctx->canvas_width;
    int h = ctx->canvas_height;
    double x = (double)rnd()/RAND_MAX * w;
    double y = (double)rnd()/RAND_MAX * h;
    SkPath path;

    path.moveTo(x, y);
    for (int i=0; i<ctx->size; i++) {
        x = (double)rnd()/RAND_MAX * w;
        y = (double)rnd()/RAND_MAX * h;

        path.lineTo(x, y);
    }

    skiaRandomizePaintColor(ctx);
    ctx->skia_canvas->drawPath(path, *(ctx->skia_paint));

    return 1;
}