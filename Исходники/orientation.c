void initPredicates()
{
 static char a_c=0;
 double hf, ck, lc;
 int e_o;

 if (a_c) return; else a_c = 1;

#ifdef SPECIFY_FP_PRECISION
 unsigned int old_cfp;
 _controlfp_s(&old_cfp, _PC_53, MCW_PC);
#endif
 
 e_o = 1;
 _eps = _spl = ck = 1.0;
 hf = 0.5;

 do
 {
  lc=ck;
  _eps *= hf;
  if (e_o) _spl *= 2.0;
  e_o = !e_o;
  ck = 1.0 + _eps;
 } while ((ck != 1.0) && (ck != lc));
 _spl += 1.0;

  _reb = (3.0 + 8.0 * _eps) * _eps;
  _ccwebA = (3.0 + 16.0 * _eps) * _eps;
  _ccwebB = (2.0 + 12.0 * _eps) * _eps;
  _ccwebC = (9.0 + 64.0 * _eps) * _eps * _eps;
  _o3ebA = (7.0 + 56.0 * _eps) * _eps;
  _o3ebB = (3.0 + 28.0 * _eps) * _eps;
  _o3ebC = (26.0 + 288.0 * _eps) * _eps * _eps;
  _iccebA = (10.0 + 96.0 * _eps) * _eps;
  _iccebB = (4.0 + 48.0 * _eps) * _eps;
  _iccebC = (44.0 + 576.0 * _eps) * _eps * _eps;
  _ispebA = (16.0 + 224.0 * _eps) * _eps;
  _ispebB = (5.0 + 72.0 * _eps) * _eps;
  _ispebC = (71.0 + 1408.0 * _eps) * _eps * _eps;

#ifdef SPECIFY_FP_PRECISION
  _controlfp_s(&old_cfp, _CW_DEFAULT, MCW_PC);
#endif
}