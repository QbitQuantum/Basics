void LALInferenceTemplateROQ(LALInferenceModel *model)
{
double m1,m2,mc,eta,q,iota=0;
/* Prefer m1 and m2 if available (i.e. for injection template) */
  if(LALInferenceCheckVariable(model->params,"mass1")&&LALInferenceCheckVariable(model->params,"mass2"))
  {
    m1=*(REAL8 *)LALInferenceGetVariable(model->params,"mass1");
    m2=*(REAL8 *)LALInferenceGetVariable(model->params,"mass2");
    eta=m1*m2/((m1+m2)*(m1+m2));
    mc=pow(eta , 0.6)*(m1+m2);
  }
  else
  {
    if (LALInferenceCheckVariable(model->params,"q")) {
      q = *(REAL8 *)LALInferenceGetVariable(model->params,"q");
      q2eta(q, &eta);
    }
    else
      eta = *(REAL8*) LALInferenceGetVariable(model->params, "eta");
    mc       = *(REAL8*) LALInferenceGetVariable(model->params, "chirpmass");
    mc2masses(mc, eta, &m1, &m2);
  }

  iota = acos(LALInferenceGetREAL8Variable(model->params, "costheta_jn"));     /* zenith angle between J and N in radians */

  double cosiota = cos(iota);
  double plusCoef  = 0.5 * (1.0 + cosiota*cosiota);
  double crossCoef = cosiota;
  /* external: SI; internal: solar masses */
  const REAL8 m = m1 + m2;
  const REAL8 m_sec = m * LAL_MTSUN_SI;  /* total mass in seconds */
  const REAL8 etap2 = eta * eta;
  const REAL8 etap3 = etap2 * eta;
  const REAL8 piM = LAL_PI * m_sec;
  const REAL8 mSevenBySix = -7./6.;
  const REAL8 phic = *(REAL8 *)LALInferenceGetVariable(model->params,"phase");
  const REAL8 r = 1e6*LAL_PC_SI;
  REAL8 logv0 = log(1.); //the standard tf2 definition is log(v0), but I've changed it to reflect Scott's convention
  REAL8 shft, amp0;//, f_max;
  REAL8 psiNewt, psi2, psi3, psi4, psi5, psi6, psi6L, psi7, psi3S, psi4S, psi5S;
  REAL8 eta_fac = -113. + 76. * eta;
  REAL8 chi=0; //NOTE: chi isn't used here yet, so we just set it to zero
  gsl_complex h_i;

  /* extrinsic parameters */
  amp0 = -pow(m_sec, 5./6.) * sqrt(5.*eta / 24.) / (Pi_p2by3 * r / LAL_C_SI);
  shft = 0;//LAL_TWOPI * (tStart.gpsSeconds + 1e-9 * tStart.gpsNanoSeconds);

  /* spin terms in the amplitude and phase (in terms of the reduced
   * spin parameter */
  psi3S = 113.*chi/3.;
  psi4S = 63845.*(-81. + 4.*eta)*chi*chi/(8. * eta_fac * eta_fac);
  psi5S = -565.*(-146597. + 135856.*eta + 17136.*etap2)*chi/(2268.*eta_fac);

  /* coefficients of the phase at PN orders from 0 to 3.5PN */
  psiNewt = 3./(128.*eta);
  psi2 = 3715./756. + 55.*eta/9.;
  psi3 = psi3S - 16.*LAL_PI;
  psi4 = 15293365./508032. + 27145.*eta/504. + 3085.*eta*eta/72. + psi4S;
  psi5 = (38645.*LAL_PI/756. - 65.*LAL_PI*eta/9. + psi5S);
  psi6 = 11583231236531./4694215680. - (640.*Pi_p2)/3. - (6848.*LAL_GAMMA)/21.
           + (-5162.983708047263 + 2255.*Pi_p2/12.)*eta
           + (76055.*etap2)/1728. - (127825.*etap3)/1296.;
  psi6L = -6848./21.;
  psi7 = (77096675.*LAL_PI)/254016. + (378515.*LAL_PI*eta)/1512.
           - (74045.*LAL_PI*eta*eta)/756.;

  for (unsigned int i = 0; i < model->roq->frequencyNodes->size; i++) {
    /* fourier frequency corresponding to this bin */
    const REAL8 f = gsl_vector_get(model->roq->frequencyNodes, i);
    const REAL8 v3 = piM*f;

    /* PN expansion parameter */
    REAL8 v, v2, v4, v5, v6, v7, logv, Psi, amp;
    v = cbrt(v3);
    v2 = v*v; v4 = v3*v; v5 = v4*v; v6 = v3*v3; v7 = v6*v;
    logv = log(v);

    /* compute the phase and amplitude */
    Psi = psiNewt / v5 * (1.
         + psi2 * v2 + psi3 * v3 + psi4 * v4
         + psi5 * v5 * (1. + 3. * (logv - logv0))
         + (psi6 + psi6L * (log4 + logv)) * v6 + psi7 * v7);

    amp = amp0 * pow(f, mSevenBySix);

    GSL_SET_COMPLEX(&h_i, amp * cos(Psi + shft * f - 2.*phic - LAL_PI_4), - amp * sin(Psi + shft * f - 2.*phic - LAL_PI_4));

    gsl_vector_complex_set(model->roq->hplus, i, gsl_complex_mul_real(h_i,plusCoef));
    gsl_vector_complex_set(model->roq->hcross, i, gsl_complex_mul_real(gsl_complex_mul_imag(h_i,-1.0),crossCoef));

  }
	return;
}