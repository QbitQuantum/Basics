static void test_conversion(const struct bitmap_data *src, const struct bitmap_data *dst, const char *name, BOOL todo)
{
    BitmapTestSrc *src_obj;
    IWICBitmapSource *dst_bitmap;
    HRESULT hr;

    CreateTestBitmap(src, &src_obj);

    hr = WICConvertBitmapSource(dst->format, &src_obj->IWICBitmapSource_iface, &dst_bitmap);
    if (todo)
        todo_wine ok(SUCCEEDED(hr), "WICConvertBitmapSource(%s) failed, hr=%x\n", name, hr);
    else
        ok(SUCCEEDED(hr), "WICConvertBitmapSource(%s) failed, hr=%x\n", name, hr);

    if (SUCCEEDED(hr))
    {
        compare_bitmap_data(dst, dst_bitmap, name);

        IWICBitmapSource_Release(dst_bitmap);
    }

    DeleteTestBitmap(src_obj);
}