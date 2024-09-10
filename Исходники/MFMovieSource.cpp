/*static */HRESULT MFMovieSource::GetDuration( IMFSourceReader* reader, UINT64& duration )
{
  // https://msdn.microsoft.com/ja-jp/library/windows/desktop/ms702060(v=vs.85).aspx
  HRESULT hr;
  PROPVARIANT var={};
  PropVariantInit( &var );
  hr=reader->GetPresentationAttribute(
    (DWORD)MF_SOURCE_READER_MEDIASOURCE,
    MF_PD_DURATION,
    &var );
  if( SUCCEEDED( hr ) )
  {
    long long tmp = 0;
    PropVariantToInt64( var, &tmp );
    duration = (UINT64)std::max(tmp, 0LL);
    PropVariantClear( &var );
  }
  return hr;
}