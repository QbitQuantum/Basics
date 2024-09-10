HRESULT RenderAreaMessageHandler::OnRender()
{
    using namespace Concurrency;

    ComPtr<IWindow> window;

    HRESULT hr = GetWindow(&window);

    RECT rect;
    if (SUCCEEDED(hr))
    {
        hr = window->GetClientRect(&rect);
    }

    if (SUCCEEDED(hr))
    {
        double d = 1 / m_scale;

        const unsigned int width = rect.right;
        const unsigned int height = rect.bottom;

        double dx = d * width / 640;
        double dy = d * height / 640;

        std::vector<unsigned int> data(width * height);

        array_view<unsigned int, 2> arrayview(height, width, data);

        static const unsigned int max_iter = 4096;

        if (m_useDouble)
        {
            generate_mandelbrot<double>(
                arrayview, 
                std::min(static_cast<unsigned int>(64 * log(1 + m_scale) * 4), max_iter), 
                static_cast<double>(m_centerx - dx), 
                static_cast<double>(m_centery - dy), 
                static_cast<double>(m_centerx + dx), 
                static_cast<double>(m_centery + dy));
        }
        else
        {
            generate_mandelbrot<float>(
                arrayview, 
                std::min(static_cast<unsigned int>(64 * log(1 + m_scale) * 4), max_iter), 
                static_cast<float>(m_centerx - dx), 
                static_cast<float>(m_centery - dy), 
                static_cast<float>(m_centerx + dx), 
                static_cast<float>(m_centery + dy));
        }

        arrayview.synchronize();

        ComPtr<ID2D1Bitmap> bitmap;
        hr = m_renderTarget->CreateBitmap(
            D2D1::SizeU(width, height),
            static_cast<void*>(data.data()),
            width * 4,
            D2D1::BitmapProperties(
            D2D1::PixelFormat(
            DXGI_FORMAT_B8G8R8A8_UNORM,
            D2D1_ALPHA_MODE_IGNORE
            )),
            &bitmap);

        if (SUCCEEDED(hr))
        {
            m_renderTarget->BeginDraw();
            m_renderTarget->Clear();

            m_renderTarget->DrawBitmap(bitmap, 
                D2D1::RectF(0.0, 0.0, static_cast<float>(width), static_cast<float>(height)));

            m_renderTarget->EndDraw();
        }
    }
    return hr;
}