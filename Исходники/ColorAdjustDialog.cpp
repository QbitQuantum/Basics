////////////////////////////////////////////////////////////////////////////////
//#include "../../../code/image_proc/image/hsi.hpp"
bool
CColorAdjustDialog::DrawPreview(CPaintDC& dc, RECT* rect)
{
  if (!m_blit_tile || m_blit_tile->GetPixels() == NULL || rect == NULL) {
    return false;
  }
  /////////////////////////////////////////////////////////
  const int width  = m_blit_tile->GetWidth();
  const int height = m_blit_tile->GetHeight();
  int current_width = m_Width;
  if (current_width > width)
    current_width = width;
  int current_height = m_Height;
  if (current_height > height)
    current_height = height;
  BGRA* pixels = (BGRA*) m_blit_tile->GetPixels();
  for (int iy = 0; iy < current_height; iy++) {
    for (int ix = 0; ix < current_width; ix++) {
      pixels[iy * width + ix].red   = m_Pixels[iy * m_Width + ix].red;
      pixels[iy * width + ix].green = m_Pixels[iy * m_Width + ix].green;
      pixels[iy * width + ix].blue  = m_Pixels[iy * m_Width + ix].blue;
      pixels[iy * width + ix].alpha = m_Pixels[iy * m_Width + ix].alpha;
    }
  }
  /////////////////////////////////////////////////////////
  int red_value   = GetRedValue();
  int green_value = GetGreenValue();
  int blue_value  = GetBlueValue();
  int alpha_value = GetAlphaValue();
  int use_red   = ShouldUseRedChannel();
  int use_green = ShouldUseGreenChannel();
  int use_blue  = ShouldUseBlueChannel();
  int use_alpha = ShouldUseAlphaChannel();
  int method = 0;
  if (method == 0)
  {
    for (int iy = 0; iy < current_height; iy++) {
      for (int ix = 0; ix < current_width; ix++) {
        if (use_red)   pixels[iy * width + ix].red   += red_value;
        if (use_green) pixels[iy * width + ix].green += green_value;
        if (use_blue)  pixels[iy * width + ix].blue  += blue_value;
        if (use_alpha) pixels[iy * width + ix].alpha += alpha_value;
      }
    } 
  }
  /*
  else
  {
    double h_value = ((double)red_value   / (double)255.0) * ((double)2.0 * 3.14);
    double s_value = ((double)green_value / (double)255.0);
    double i_value = ((double)blue_value  / (double)255.0);
    for (int iy = 0; iy < current_height; iy++) {
      for (int ix = 0; ix < current_width; ix++) {
        double r = pixels[iy * width + ix].red   / 255.0;
        double g = pixels[iy * width + ix].green / 255.0;
        double b = pixels[iy * width + ix].blue  / 255.0;
        double h, s, i;
        RGBtoHSI(r, g, b, &h, &s, &i);
        if (use_red)   h += h_value;
        if (use_green) s += s_value;
        if (use_blue)  i += i_value;
        if (use_alpha) pixels[iy * width + ix].alpha += alpha_value;
        HSItoRGB(h, s, i, &r, &g, &b);
        pixels[iy * width + ix].red   = r * 255;
        pixels[iy * width + ix].green = g * 255;
        pixels[iy * width + ix].blue  = b * 255;
      }
    } 
  }
  */
  /////////////////////////////////////////////////////////
  dc.BitBlt(rect->left, rect->top, current_width, current_height, CDC::FromHandle(m_blit_tile->GetDC()), 0, 0, SRCCOPY);
  if (1) {
    rect->left += current_width;
    dc.FillRect(rect, CBrush::FromHandle((HBRUSH)GetStockObject(BLACK_BRUSH)));
    rect->left -= current_width;
    rect->top += current_height;
    dc.FillRect(rect, CBrush::FromHandle((HBRUSH)GetStockObject(BLACK_BRUSH)));
    rect->top -= current_height;
  }
  return true;
}