static void test_clip(void)
{
    IDXGISwapChain *swapchain;
    D2D1_MATRIX_3X2_F matrix;
    D2D1_SIZE_U pixel_size;
    ID2D1RenderTarget *rt;
    ID3D10Device1 *device;
    IDXGISurface *surface;
    D2D1_POINT_2F point;
    D2D1_COLOR_F color;
    float dpi_x, dpi_y;
    D2D1_RECT_F rect;
    D2D1_SIZE_F size;
    HWND window;
    HRESULT hr;
    static const D2D1_MATRIX_3X2_F identity =
    {
        1.0f, 0.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
    };

    if (!(device = create_device()))
    {
        skip("Failed to create device, skipping tests.\n");
        return;
    }
    window = CreateWindowA("static", "d2d1_test", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            0, 0, 640, 480, NULL, NULL, NULL, NULL);
    swapchain = create_swapchain(device, window, TRUE);
    hr = IDXGISwapChain_GetBuffer(swapchain, 0, &IID_IDXGISurface, (void **)&surface);
    ok(SUCCEEDED(hr), "Failed to get buffer, hr %#x.\n", hr);
    rt = create_render_target(surface);
    ok(!!rt, "Failed to create render target.\n");

    ID2D1RenderTarget_GetDpi(rt, &dpi_x, &dpi_y);
    ok(dpi_x == 96.0f, "Got unexpected dpi_x %.8e.\n", dpi_x);
    ok(dpi_y == 96.0f, "Got unexpected dpi_x %.8e.\n", dpi_y);
    size = ID2D1RenderTarget_GetSize(rt);
    ok(size.width == 640.0f, "Got unexpected width %.8e.\n", size.width);
    ok(size.height == 480.0f, "Got unexpected height %.8e.\n", size.height);
    pixel_size = ID2D1RenderTarget_GetPixelSize(rt);
    ok(pixel_size.width == 640, "Got unexpected width %u.\n", pixel_size.width);
    ok(pixel_size.height == 480, "Got unexpected height %u.\n", pixel_size.height);

    ID2D1RenderTarget_GetTransform(rt, &matrix);
    ok(!memcmp(&matrix, &identity, sizeof(matrix)),
            "Got unexpected matrix {%.8e, %.8e, %.8e, %.8e, %.8e, %.8e}.\n",
            matrix._11, matrix._12, matrix._21, matrix._22, matrix._31, matrix._32);

    ID2D1RenderTarget_BeginDraw(rt);

    set_color(&color, 1.0f, 1.0f, 0.0f, 1.0f);
    ID2D1RenderTarget_Clear(rt, &color);

    ID2D1RenderTarget_SetDpi(rt, 48.0f, 192.0f);
    ID2D1RenderTarget_GetDpi(rt, &dpi_x, &dpi_y);
    ok(dpi_x == 48.0f, "Got unexpected dpi_x %.8e.\n", dpi_x);
    ok(dpi_y == 192.0f, "Got unexpected dpi_x %.8e.\n", dpi_y);
    size = ID2D1RenderTarget_GetSize(rt);
    ok(size.width == 1280.0f, "Got unexpected width %.8e.\n", size.width);
    ok(size.height == 240.0f, "Got unexpected height %.8e.\n", size.height);
    pixel_size = ID2D1RenderTarget_GetPixelSize(rt);
    ok(pixel_size.width == 640, "Got unexpected width %u.\n", pixel_size.width);
    ok(pixel_size.height == 480, "Got unexpected height %u.\n", pixel_size.height);

    /* The effective clip rect is the intersection of all currently pushed
     * clip rects. Clip rects are in DIPs. */
    set_rect(&rect, 0.0f, 0.0f, 1280.0f, 80.0f);
    ID2D1RenderTarget_PushAxisAlignedClip(rt, &rect, D2D1_ANTIALIAS_MODE_ALIASED);
    set_rect(&rect, 0.0f, 0.0f, 426.0f, 240.0f);
    ID2D1RenderTarget_PushAxisAlignedClip(rt, &rect, D2D1_ANTIALIAS_MODE_ALIASED);

    set_color(&color, 0.0f, 1.0f, 0.0f, 1.0f);
    ID2D1RenderTarget_Clear(rt, &color);
    ID2D1RenderTarget_PopAxisAlignedClip(rt);
    ID2D1RenderTarget_PopAxisAlignedClip(rt);

    ID2D1RenderTarget_SetDpi(rt, 0.0f, 0.0f);
    ID2D1RenderTarget_GetDpi(rt, &dpi_x, &dpi_y);
    ok(dpi_x == 96.0f, "Got unexpected dpi_x %.8e.\n", dpi_x);
    ok(dpi_y == 96.0f, "Got unexpected dpi_y %.8e.\n", dpi_y);

    /* Transformations apply to clip rects, the effective clip rect is the
     * (axis-aligned) bounding box of the transformed clip rect. */
    set_point(&point, 320.0f, 240.0f);
    D2D1MakeRotateMatrix(30.0f, point, &matrix);
    ID2D1RenderTarget_SetTransform(rt, &matrix);
    set_rect(&rect, 215.0f, 208.0f, 425.0f, 272.0f);
    ID2D1RenderTarget_PushAxisAlignedClip(rt, &rect, D2D1_ANTIALIAS_MODE_ALIASED);
    set_color(&color, 1.0f, 1.0f, 1.0f, 1.0f);
    ID2D1RenderTarget_Clear(rt, &color);
    ID2D1RenderTarget_PopAxisAlignedClip(rt);

    /* Transformations are applied when pushing the clip rect, transformations
     * set afterwards have no effect on the current clip rect. This includes
     * SetDpi(). */
    ID2D1RenderTarget_SetTransform(rt, &identity);
    set_rect(&rect, 427.0f, 320.0f, 640.0f, 480.0f);
    ID2D1RenderTarget_PushAxisAlignedClip(rt, &rect, D2D1_ANTIALIAS_MODE_ALIASED);
    ID2D1RenderTarget_SetTransform(rt, &matrix);
    ID2D1RenderTarget_SetDpi(rt, 48.0f, 192.0f);
    set_color(&color, 1.0f, 0.0f, 0.0f, 1.0f);
    ID2D1RenderTarget_Clear(rt, &color);
    ID2D1RenderTarget_PopAxisAlignedClip(rt);

    hr = ID2D1RenderTarget_EndDraw(rt, NULL, NULL);
    ok(SUCCEEDED(hr), "Failed to end draw, hr %#x.\n", hr);
    ok(compare_surface(surface, "035a44d4198d6e422e9de6185b5b2c2bac5e33c9"), "Surface does not match.\n");

    ID2D1RenderTarget_Release(rt);
    IDXGISurface_Release(surface);
    IDXGISwapChain_Release(swapchain);
    ID3D10Device1_Release(device);
    DestroyWindow(window);
}