TexturePod OverlayText(string message)
{
    InitializeGdi();
    PezConfig cfg = PezGetConfig();

    // Skip GDI text generation if the string is unchanged:
    if (message == oc.PreviousMessage)
        return oc.MessageTexture;

    oc.PreviousMessage = message;

    // Create the GDI+ drawing context and set it up:
    Graphics* gfx = Graphics::FromImage(oc.GdiBitmap);
    gfx->Clear(Color::Transparent);
    gfx->SetSmoothingMode(SmoothingModeAntiAlias);
    gfx->SetInterpolationMode(InterpolationModeHighQualityBicubic);

    // Select a font:
    FontFamily fontFamily(L"Trebuchet MS");
    const float fontSize = 14;
    PointF origin(10.0f, 10.0f);
    StringFormat format(StringAlignmentNear);

    // Create a path along the outline of the glyphs:
    GraphicsPath path;
    path.AddString(
        wstring(message.begin(), message.end()).c_str(),
        -1,
        &fontFamily,
        FontStyleRegular,
        fontSize,
        origin,
        &format);

    // Draw some glow to steer clear of crappy AA:
    for (float width = 0; width < 3; ++width) {
        Pen pen(Color(64, 0, 0, 0), width);
        pen.SetLineJoin(LineJoinRound);
        gfx->DrawPath(&pen, &path);
    }

    // Fill the glyphs:
    SolidBrush brush(Color(50, 100, 200));
    gfx->FillPath(&brush, &path);

    // Lock the raw pixel data and pass it to OpenGL:
    BitmapData data;
    oc.GdiBitmap->LockBits(0, ImageLockModeRead, PixelFormat32bppARGB, &data);
    _ASSERT(data.Stride == sizeof(unsigned int) * cfg.Width);
    glBindTexture(GL_TEXTURE_2D, oc.MessageTexture.Handle);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, cfg.Width, cfg.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.Scan0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    oc.GdiBitmap->UnlockBits(&data);

    return oc.MessageTexture;
}