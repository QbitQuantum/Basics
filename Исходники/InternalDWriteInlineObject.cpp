    IFACEMETHODIMP DrawUnderline(
        Vector2 baselineOrigin,
        float width,
        float thickness,
        float offset,
        float runHeight,
        CanvasTextDirection textDirection,
        IInspectable* brush,
        CanvasTextMeasuringMode measuringMode,
        HSTRING locale,
        CanvasGlyphOrientation glyphOrientation)
    {
        return ExceptionBoundary(
            [&]
            {
                EnsureValidResource();

                DWRITE_UNDERLINE underline{};
                underline.width = width;
                underline.thickness = thickness;
                underline.offset = offset;
                underline.runHeight = runHeight;

                auto textDirectionLookup = DWriteToCanvasTextDirection::Lookup(textDirection);
                underline.flowDirection = textDirectionLookup->FlowDirection;
                underline.readingDirection = textDirectionLookup->ReadingDirection;
                underline.measuringMode = ToDWriteMeasuringMode(measuringMode);

                auto deviceContextLease = As<ICanvasDeviceInternal>(m_device)->GetResourceCreationDeviceContext();

                if (locale)
                    underline.localeName = WindowsGetStringRawBuffer(locale, nullptr);

                ThrowIfFailed(m_dwriteTextRenderer->DrawUnderline(
                    nullptr,
                    baselineOrigin.X,
                    baselineOrigin.Y,
                    ToDWriteGlyphOrientationAngle(glyphOrientation),
                    &underline,
                    DrawGlyphRunHelper::GetClientDrawingEffect(brush, deviceContextLease.Get()).Get()));
            });
    }