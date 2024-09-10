/*===========================================================================
 *
 * Class CSrFile Method - bool Printf (pString, ...);
 *
 *=========================================================================*/
bool CSrFile::Printf  (const SSCHAR* pString, ...) {
  va_list Args;
  bool    Result;

  va_start(Args, pString);
  Result = VPrintf(pString, Args);
  va_end(Args);

  return (Result);
 }