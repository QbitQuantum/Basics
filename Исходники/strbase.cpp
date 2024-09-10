void StringImp::RightJustify(Subscript FieldWidth_, char Pad_)
{
  if (_StrData->_Size < FieldWidth_)
  {
    StrRev();
    ReallocateData(FieldWidth_);
  }
  else
    StrRev();

  Subscript Index_;
  for (Index_ = strlen(); Index_ < FieldWidth_; Index_++)
    (*_StrData)[Index_] = Pad_;

  TerminateString(Index_);
  StrRev();
}