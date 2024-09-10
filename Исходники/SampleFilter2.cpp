        virtual void onDrawContent(SkCanvas* canvas)
            {
            canvas->translate(SkIntToScalar(10), SkIntToScalar(50));

            const SkScalar W = SkIntToScalar(fBitmaps[0].width() + 1);
            const SkScalar H = SkIntToScalar(fBitmaps[0].height() + 1);
            SkPaint paint;

            const SkScalar scale = SkFloatToScalar(0.897917f);
            canvas->scale(SK_Scalar1, scale);

            for (int k = 0; k < 2; k++)
                {
                paint.setFilterBitmap(k == 1);
                for (int j = 0; j < 2; j++)
                    {
                    paint.setDither(j == 1);
                    for (int i = 0; i < fBitmapCount; i++)
                        {
                        SkScalar x = (k * fBitmapCount + j) * W;
                        SkScalar y = i * H;
                        x = SkIntToScalar(SkScalarRound(x));
                        y = SkIntToScalar(SkScalarRound(y));
                        canvas->drawBitmap(fBitmaps[i], x, y, &paint);
                        if (i == 0)
                            {
                            SkPaint p;
                            p.setAntiAlias(true);
                            p.setTextAlign(SkPaint::kCenter_Align);
                            p.setTextSize(SkIntToScalar(18));
                            SkString s("dither=");
                            s.appendS32(paint.isDither());
                            s.append(" filter=");
                            s.appendS32(paint.isFilterBitmap());
                            canvas->drawText(s.c_str(), s.size(), x + W/2,
                                             y - p.getTextSize(), p);
                            }
                        if (k+j == 2)
                            {
                            SkPaint p;
                            p.setAntiAlias(true);
                            p.setTextSize(SkIntToScalar(18));
                            SkString s;
                            s.append(" depth=");
                            s.appendS32(fBitmaps[i].config() == SkBitmap::kRGB_565_Config ? 16 : 32);
                            canvas->drawText(s.c_str(), s.size(), x + W + SkIntToScalar(4),
                                             y + H/2, p);
                            }
                        }
                    }
                }
            }