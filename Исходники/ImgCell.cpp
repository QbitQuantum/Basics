void ImgCell::Draw(wxPoint point, int fontsize)
{
  MathCell::Draw(point, fontsize);

  // TODO: Enable this when unselecting text updates the right region.
  //if (!InUpdateRegion()) return;

  CellParser *parser = CellParser::Get();
  wxDC& dc = parser->GetDC();
  if (DrawThisCell(point) && (m_image != NULL))
  {
    wxMemoryDC bitmapDC;

    if(m_drawBoundingBox)
      dc.SetBrush( *(wxTheBrushList->FindOrCreateBrush(parser->GetColor(TS_SELECTION))));
    else
      SetPen();
    
    if (m_drawRectangle || m_drawBoundingBox)
      dc.DrawRectangle(wxRect(point.x, point.y - m_center, m_width, m_height));
    
    wxBitmap bitmap = m_image->GetBitmap();
    bitmapDC.SelectObject(bitmap);

    if ((m_drawBoundingBox == false) || (m_imageBorderWidth > 0))
      dc.Blit(point.x + m_imageBorderWidth, point.y - m_center + m_imageBorderWidth, m_width - 2 * m_imageBorderWidth, m_height - 2 * m_imageBorderWidth, &bitmapDC, 0, 0);
    else
      dc.StretchBlit(point.x + 5, point.y - m_center + 5, m_width - 2 * 5, m_height - 2 * 5, &bitmapDC, 0, 0, m_width, m_height);
  }
  else
    // The cell isn't drawn => No need to keep it's image cache for now.
    ClearCache();
  
  // The next time we need to draw a bounding box we will be informed again.
  m_drawBoundingBox = false;
}