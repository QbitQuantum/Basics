glyph glyph::hilite(nc_color back)
{
  if (fg == back) {
    return invert();
  }
  glyph ret = (*this);
  
  ret.bg = back;
  return ret;
}