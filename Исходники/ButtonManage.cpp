std::wstring ButtonManage::RectToString(CRect& rc)
{
  wchar_t s[10];
  std::wstring str;
  int left = rc.left;
  _itow(left, s, 10);
  str =str + s + L",";
  int top  = rc.top;
  _itow(top, s, 10);
  str =str + s + L",";
  int right = rc.right;
  _itow(right, s, 10);
  str =str + s + L",";
  int bottom = rc.bottom;
  _itow(bottom, s ,10);
  str += s;

  return str;
}