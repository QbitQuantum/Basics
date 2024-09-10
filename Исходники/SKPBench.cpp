void SKPBench::getGpuStats(SkCanvas* canvas, SkTArray<SkString>* keys, SkTArray<double>* values) {
#if SK_SUPPORT_GPU
    // we do a special single draw and then dump the key / value pairs
    GrContext* context = canvas->getGrContext();
    if (!context) {
        return;
    }

    // TODO refactor this out if we want to test other subclasses of skpbench
    context->flush();
    context->freeGpuResources();
    context->resetContext();
    context->getGpu()->resetShaderCacheForTesting();
    draw_pic_for_stats(canvas, context, fPic, keys, values, "first_frame");

    // draw second frame
    draw_pic_for_stats(canvas, context, fPic, keys, values, "second_frame");

#endif
}