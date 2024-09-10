//---------------------------------------------------------------------------
// Windows algorithm is as follows (tested on W2k):
// right:
//   is_delimiter(current)
//     false:
//       right(left(current) + 1)
//     true:
//       right(right(current) + 1)
// left:
//   right(left(current) + 1)
int CALLBACK PathWordBreakProc(wchar_t * Ch, int Current, int Len, int Code)
{
  int Result;
  UnicodeString ACh(Ch, Len);
  if (Code == WB_ISDELIMITER)
  {
    // we return negacy of what WinAPI docs says
    Result = !IsPathWordDelimiter(ACh[Current + 1]);
  }
  else if (Code == WB_LEFT)
  {
    // skip consecutive delimiters
    while ((Current > 0) &&
           IsPathWordDelimiter(ACh[Current]))
    {
      Current--;
    }
    Result = ACh.SubString(1, Current - 1).LastDelimiter(PathWordDelimiters);
  }
  else if (Code == WB_RIGHT)
  {
    if (Current == 0)
    {
      // will be called again with Current == 1
      Result = 0;
    }
    else
    {
      const wchar_t * P = wcspbrk(ACh.c_str() + Current - 1, PathWordDelimiters);
      if (P == NULL)
      {
        Result = Len;
      }
      else
      {
        Result = P - ACh.c_str() + 1;
        // skip consecutive delimiters
        while ((Result < Len) &&
               IsPathWordDelimiter(ACh[Result + 1]))
        {
          Result++;
        }
      }
    }
  }
  else
  {
    assert(false);
    Result = 0;
  }
  return Result;
}