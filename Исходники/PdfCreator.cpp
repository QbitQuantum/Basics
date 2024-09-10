static fz_image *render_to_pixmap(fz_context *ctx, HBITMAP hbmp, SizeI size)
{
    int w = size.dx, h = size.dy;
    int stride = ((w * 3 + 3) / 4) * 4;

    unsigned char *data = (unsigned char *)fz_malloc(ctx, stride * h);

    BITMAPINFO bmi = { 0 };
    bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
    bmi.bmiHeader.biWidth = w;
    bmi.bmiHeader.biHeight = -h;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 24;
    bmi.bmiHeader.biCompression = BI_RGB;

    HDC hDC = GetDC(nullptr);
    int res = GetDIBits(hDC, hbmp, 0, h, data, &bmi, DIB_RGB_COLORS);
    ReleaseDC(nullptr, hDC);
    if (!res) {
        fz_free(ctx, data);
        fz_throw(ctx, FZ_ERROR_GENERIC, "GetDIBits failed");
    }

    // convert BGR with padding to RGB without padding
    unsigned char *out = data;
    bool is_grayscale = true;
    for (int y = 0; y < h; y++) {
        const unsigned char *in = data + y * stride;
        unsigned char green, blue;
        for (int x = 0; x < w; x++) {
            is_grayscale = is_grayscale && in[0] == in[1] && in[0] == in[2];
            blue = *in++;
            green = *in++;
            *out++ = *in++;
            *out++ = green;
            *out++ = blue;
        }
    }
    // convert grayscale RGB to proper grayscale
    if (is_grayscale) {
        const unsigned char *in = out = data;
        for (int i = 0; i < w * h; i++) {
            *out++ = *in++;
            in += 2;
        }
    }

    fz_compressed_buffer *buf = nullptr;
    fz_var(buf);

    fz_try(ctx) {
        buf = fz_malloc_struct(ctx, fz_compressed_buffer);
        buf->buffer = fz_new_buffer(ctx, w * h * 4 + 10);
        buf->params.type = FZ_IMAGE_FLATE;
        buf->params.u.flate.predictor = 1;

        z_stream zstm = { 0 };
        zstm.next_in = data;
        zstm.avail_in = out - data;
        zstm.next_out = buf->buffer->data;
        zstm.avail_out = buf->buffer->cap;

        res = deflateInit(&zstm, 9);
        if (res != Z_OK)
            fz_throw(ctx, FZ_ERROR_GENERIC, "deflate failure %d", res);
        res = deflate(&zstm, Z_FINISH);
        if (res != Z_STREAM_END)
            fz_throw(ctx, FZ_ERROR_GENERIC, "deflate failure %d", res);
        buf->buffer->len = zstm.total_out;
        res = deflateEnd(&zstm);
        if (res != Z_OK)
            fz_throw(ctx, FZ_ERROR_GENERIC, "deflate failure %d", res);
    }
    fz_always(ctx) {
        fz_free(ctx, data);
    }
    fz_catch(ctx) {
        fz_free_compressed_buffer(ctx, buf);
        fz_rethrow(ctx);
    }

    fz_colorspace *cs = is_grayscale ? fz_device_gray(ctx) : fz_device_rgb(ctx);
    return fz_new_image(ctx, w, h, 8, cs, 96, 96, 0, 0, nullptr, nullptr, buf, nullptr);
}