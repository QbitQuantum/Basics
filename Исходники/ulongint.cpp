ULongInt::ULongInt(const ChrString& Str_):
LongInt(Str_, FALSE, ULongInt::IsValue(Str_))
{
  Byte_t Valid_ = _Valid;
  _Uvalue = Valid_ ? Str_.strtoul():0UL;

  if (!Valid_)
  {
    SetAsNullObject();
    SetDataConversionError();
  }    
}