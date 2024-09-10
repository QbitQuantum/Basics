void wxChartBackground::Draw(wxDouble x, 
                             wxDouble y, 
                             wxDouble width, 
                             wxDouble height,
                             wxGraphicsContext &gc)
{
    wxGraphicsPath path = gc.CreatePath();

    path.AddRoundedRectangle(x, y, width, height, m_options.GetCornerRadius());

    wxBrush brush(m_options.GetColor());
    gc.SetBrush(brush);
    gc.FillPath(path);
}