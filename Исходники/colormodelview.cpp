void ColorModelView::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    auto mainBounds = mainAreaBounds();
    auto sideBounds = sideAreaBounds();

    if (mainImage_.isNull()) {
        // FIXME: support other color model?
        QImage img(256, 256, QImage::Format_RGB32);
        auto *pixels = reinterpret_cast<quint32 *>(img.bits());
        auto basecolor = QColor::fromHsv(value_.hsvHue(), 255, 255);
        auto basecolorMM = _mm_setr_epi32(basecolor.blue(), basecolor.green(), basecolor.red(), 0);
        basecolorMM = _mm_add_epi32(basecolorMM, _mm_srli_epi32(basecolorMM, 7)); // map [0, 255] to [0, 256]
        auto white = _mm_set1_epi32(256 * 255);
        auto dX = _mm_sub_epi32(basecolorMM, _mm_set1_epi32(256));
        for (int y = 0; y < 256; ++y) {
            auto brightness = _mm_set1_epi32(256 - y - (y >> 7));
            auto col = white; // [0, 256 * 255]
            for (int x = 0; x < 256; ++x) {
                auto c = _mm_mullo_epi16(_mm_srli_epi32(col, 8), brightness);
                c = _mm_srli_epi16(c, 8); // [0, 255]
                c = _mm_packs_epi32(c, c);
                c = _mm_packus_epi16(c, c);

                _mm_store_ss(reinterpret_cast<float *>(&pixels[x + y * 256]),
                        _mm_castsi128_ps(c));

                col = _mm_add_epi32(col, dX);
            }
        }
        mainImage_ = QPixmap::fromImage(img);
    }