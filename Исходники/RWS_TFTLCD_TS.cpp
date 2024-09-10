void     RWS_TFTLCD_TS::leftCR(void)
{
  if(_CRscrCurrent < _CRstartX + _CRsX - 8) fillRect(_CRscrCurrent - _CRjumpX, _CRstartY, 9+_CRjumpX, _CRsY, _CRbg);
  _CRscrCurrent = _CRstartX;
}