// (4)
//==============================================================================
CString CDiskItem::getExtension() const
{
  wchar_t drive[_MAX_DRIVE];
  wchar_t dir[_MAX_DIR];
  wchar_t fname[_MAX_FNAME];
  wchar_t ext[_MAX_EXT];

  _wsplitpath_s( m_strName, drive, dir, fname, ext );
  if( *ext == 0 )  // empty string
    return ext;
  else
    return ext+1; // exclude the period (.)
}