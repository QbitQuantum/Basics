UShortInt::UShortInt(const ChrString& Str_):
ShortInt(Str_, FALSE, UShortInt::IsValue(Str_))
{
  Byte_t Valid_ = _Valid;
  _Uvalue = Valid_ ? Ushort(Str_.strtoul()):0;

  if (!Valid_)
  {
    SetAsNullObject();
    SetDataConversionError();
  }
}