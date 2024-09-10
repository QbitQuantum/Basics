void
ffi_pl_perl_to_complex_float(SV *sv, float *ptr)
{
  if(sv_isobject(sv) && sv_derived_from(sv, "Math::Complex"))
  {
    ptr[0] = decompose(sv, 0);
    ptr[1] = decompose(sv, 1);
  }
  else if(SvROK(sv) && SvTYPE(SvRV(sv)) == SVt_PVAV)
  {
    AV *av = (AV*) SvRV(sv);
    SV **real_sv, **imag_sv;
    real_sv = av_fetch(av, 0, 0);
    imag_sv = av_fetch(av, 1, 0);
    ptr[0] = real_sv != NULL ? SvNV(*real_sv) : 0.0;
    ptr[1]= imag_sv != NULL ? SvNV(*imag_sv) : 0.0;
  }
  else if(SvOK(sv))
  {
    ptr[0] = SvNV(sv);
    ptr[1] = 0.0;
  }
  else
  {
    ptr[0] = 0.0;
    ptr[1] = 0.0;
  }
}