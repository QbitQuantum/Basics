static void
gdi_softpipe_present(struct pipe_screen *screen,
                     struct pipe_surface *surface,
                     HDC hDC)
{
    struct softpipe_texture *texture;
    struct gdi_softpipe_buffer *buffer;
    BITMAPINFO bmi;

    texture = softpipe_texture(surface->texture);
                                               
    buffer = gdi_softpipe_buffer(texture->buffer);

    memset(&bmi, 0, sizeof(BITMAPINFO));
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = texture->stride[surface->level] / pf_get_size(surface->format);
    bmi.bmiHeader.biHeight= -(long)surface->height;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = pf_get_bits(surface->format);
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biSizeImage = 0;
    bmi.bmiHeader.biXPelsPerMeter = 0;
    bmi.bmiHeader.biYPelsPerMeter = 0;
    bmi.bmiHeader.biClrUsed = 0;
    bmi.bmiHeader.biClrImportant = 0;

    StretchDIBits(hDC,
                  0, 0, surface->width, surface->height,
                  0, 0, surface->width, surface->height,
                  buffer->data, &bmi, 0, SRCCOPY);
}