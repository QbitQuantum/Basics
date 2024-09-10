void Graphics::FillRoundRectangle(Brush* brush, const RectF& rc, float d) {
    Gdiplus::Graphics* g = reinterpret_cast<Gdiplus::Graphics*>(_private);
    Gdiplus::Brush* gdiBrush = reinterpret_cast<Gdiplus::Brush*>(brush->_private);

    Gdiplus::GraphicsPath gp;
    Gdiplus::RectF r(rc.GetLeft()-1.0f, rc.GetTop()-1.0f, rc.GetWidth(), rc.GetHeight());

    gp.AddArc(r.X, r.Y, d, d, 180.0f, 90.0f);
    gp.AddArc(r.X + r.Width - d, r.Y, d, d, 270.0f, 90.0f);
    gp.AddArc(r.X + r.Width - d, r.Y + r.Height - d, d, d, 0.0f, 90.0f);
    gp.AddArc(r.X, r.Y + r.Height - d, d, d, 90.0f, 90.0f);
    gp.AddLine(r.X, r.Y + r.Height - d, r.X, r.Y + d / 2.0f);

    g->FillPath(gdiBrush, &gp);
}