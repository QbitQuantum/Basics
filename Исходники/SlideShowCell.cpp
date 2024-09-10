void SlideShow::Draw(wxPoint point, int fontsize)
{
  MathCell::Draw(point, fontsize);
  m_images[m_displayed]->ViewportSize(
    Configuration::Get()->GetCanvasSize().x,
    Configuration::Get()->GetCanvasSize().y,
    Configuration::Get()->GetScale());

  // TODO: Enable this when unselecting text updates the right region.
  //if (!InUpdateRegion()) return;
  
  Configuration *configuration = Configuration::Get();
  wxDC& dc = configuration->GetDC();

  if (DrawThisCell(point) && (m_images[m_displayed] != NULL))
  {
    wxMemoryDC bitmapDC;
    double scale = configuration->GetScale();
    m_images[m_displayed]->ViewportSize(
      Configuration::Get()->GetCanvasSize().x,
      Configuration::Get()->GetCanvasSize().y,scale);
  
    m_height = (m_images[m_displayed]->m_height) + 2 * m_imageBorderWidth;
    m_width  = (m_images[m_displayed]->m_width)  + 2 * m_imageBorderWidth;
    m_center = m_height / 2;

    // Slide show cells have a red border except if they are selected
    if(m_drawBoundingBox)
      dc.SetBrush( *(wxTheBrushList->FindOrCreateBrush(configuration->GetColor(TS_SELECTION))));
    else
      dc.SetPen(*wxRED_PEN);

    // If we need a selection border on another redraw we will be informed by OnPaint() again.
    m_drawBoundingBox = false;

    dc.DrawRectangle(wxRect(point.x, point.y - m_center, m_width, m_height));  

    wxBitmap bitmap = m_images[m_displayed]->GetBitmap();
    bitmapDC.SelectObject(bitmap);
      
    dc.Blit(point.x + m_imageBorderWidth, point.y - m_center + m_imageBorderWidth, m_width - 2 * m_imageBorderWidth, m_height - 2 * m_imageBorderWidth, &bitmapDC, 0, 0);
  }
  else
    // The cell isn't drawn => No need to keep it's image cache for now.
    ClearCache();
}