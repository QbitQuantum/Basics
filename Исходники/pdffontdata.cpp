wxArrayInt
wxPdfFontData::GetKerningWidthArray(const wxString& s) const
{
  bool translateChar2Glyph = m_type.IsSameAs(wxT("TrueTypeUnicode")) || 
                             m_type.IsSameAs(wxT("OpenTypeUnicode"));
  wxArrayInt widths;
  int pos = 0;
  if (m_kp != NULL && s.length())
  {
    wxPdfKernPairMap::const_iterator kpIter;
    wxPdfKernWidthMap::const_iterator kwIter;
    wxUint32 ch1, ch2;
    wxString::const_iterator ch = s.begin();
    ch1 = (wxUint32) (*ch);
    if (translateChar2Glyph && m_gn != NULL)
    {
      wxPdfChar2GlyphMap::const_iterator glyphIter;
      glyphIter = m_gn->find(ch1);
      if (glyphIter != m_gn->end())
      {
        ch1 = glyphIter->second;
      }
    }
    for (++ch; ch != s.end(); ++ch)
    {
      ch2 = (wxUint32) (*ch);
      if (translateChar2Glyph && m_gn != NULL)
      {
        wxPdfChar2GlyphMap::const_iterator glyphIter;
        glyphIter = m_gn->find(ch2);
        if (glyphIter != m_gn->end())
        {
          ch2 = glyphIter->second;
        }
      }
      kpIter = (*m_kp).find(ch1);
      if (kpIter != (*m_kp).end())
      {
        kwIter = kpIter->second->find(ch2);
        if (kwIter != kpIter->second->end())
        {
          widths.Add(pos);
          widths.Add(-kwIter->second);
        }
      }
      ch1 = ch2;
      ++pos;
    }
  }
  return widths;
}