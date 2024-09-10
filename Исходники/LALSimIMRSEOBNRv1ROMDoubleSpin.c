/*
 * Core function for computing the ROM waveform.
 * Interpolate projection coefficient data and evaluate coefficients at desired (q, chi).
 * Construct 1D splines for amplitude and phase.
 * Compute strain waveform from amplitude and phase.
*/
static int SEOBNRv1ROMDoubleSpinCore(
  COMPLEX16FrequencySeries **hptilde,
  COMPLEX16FrequencySeries **hctilde,
  double phiRef,
  double fRef,
  double distance,
  double inclination,
  double Mtot_sec,
  double q,
  double chi1,
  double chi2,
  const REAL8Sequence *freqs_in, /* Frequency points at which to evaluate the waveform (Hz) */
  double deltaF
  /* If deltaF > 0, the frequency points given in freqs are uniformly spaced with
   * spacing deltaF. Otherwise, the frequency points are spaced non-uniformly.
   * Then we will use deltaF = 0 to create the frequency series we return. */
  )
{
  /* Check output arrays */
  if(!hptilde || !hctilde)
    XLAL_ERROR(XLAL_EFAULT);
  SEOBNRROMdataDS *romdata=&__lalsim_SEOBNRv1ROMDS_data;
  if(*hptilde || *hctilde) {
    XLALPrintError("(*hptilde) and (*hctilde) are supposed to be NULL, but got %p and %p",(*hptilde),(*hctilde));
    XLAL_ERROR(XLAL_EFAULT);
  }
  int retcode=0;

  // 'Nudge' parameter values to allowed boundary values if close by
  if (q < 1.0)     nudge(&q, 1.0, 1e-6);
  if (q > 10.0)    nudge(&q, 10.0, 1e-6);
  if (chi1 < -1.0) nudge(&chi1, -1.0, 1e-6);
  if (chi1 > 0.6)  nudge(&chi1, 0.6, 1e-6);
  if (chi2 < -1.0) nudge(&chi2, -1.0, 1e-6);
  if (chi2 > 0.6)  nudge(&chi2, 0.6, 1e-6);

  /* If either spin > 0.6, model not available, exit */
  if ( chi1 < -1.0 || chi2 < -1.0 || chi1 > 0.6 || chi2 > 0.6 ) {
    XLALPrintError( "XLAL Error - %s: chi1 or chi2 smaller than -1 or larger than 0.6!\nSEOBNRv1ROMDoubleSpin is only available for spins in the range -1 <= a/M <= 0.6.\n", __func__);
    XLAL_ERROR( XLAL_EDOM );
  }

  if (q > 10) {
    XLALPrintError( "XLAL Error - %s: q=%lf larger than 10!\nSEOBNRv1ROMDoubleSpin is only available for q in the range 1 <= q <= 10.\n", __func__, q);
    XLAL_ERROR( XLAL_EDOM );
  }

  /* Find frequency bounds */
  if (!freqs_in) XLAL_ERROR(XLAL_EFAULT);
  double fLow  = freqs_in->data[0];
  double fHigh = freqs_in->data[freqs_in->length - 1];

  if(fRef==0.0)
    fRef=fLow;

  /* Convert to geometric units for frequency */
  double Mf_ROM_min = fmax(gA[0], gPhi[0]);               // lowest allowed geometric frequency for ROM
  double Mf_ROM_max = fmin(gA[nk_amp-1], gPhi[nk_phi-1]); // highest allowed geometric frequency for ROM
  double fLow_geom = fLow * Mtot_sec;
  double fHigh_geom = fHigh * Mtot_sec;
  double fRef_geom = fRef * Mtot_sec;
  double deltaF_geom = deltaF * Mtot_sec;

  // Enforce allowed geometric frequency range
  if (fLow_geom < Mf_ROM_min)
    XLAL_ERROR(XLAL_EDOM, "Starting frequency Mflow=%g is smaller than lowest frequency in ROM Mf=%g.\n", fLow_geom, Mf_ROM_min);
  if (fHigh_geom == 0)
    fHigh_geom = Mf_ROM_max;
  else if (fHigh_geom > Mf_ROM_max) {
    XLALPrintWarning("Maximal frequency Mf_high=%g is greater than highest ROM frequency Mf_ROM_Max=%g. Using Mf_high=Mf_ROM_Max.", fHigh_geom, Mf_ROM_max);
    fHigh_geom = Mf_ROM_max;
  }
  else if (fHigh_geom < Mf_ROM_min)
    XLAL_ERROR(XLAL_EDOM, "End frequency %g is smaller than starting frequency %g!\n", fHigh_geom, fLow_geom);
  if (fRef_geom > Mf_ROM_max) {
    XLALPrintWarning("Reference frequency Mf_ref=%g is greater than maximal frequency in ROM Mf=%g. Starting at maximal frequency in ROM.\n", fRef_geom, Mf_ROM_max);
    fRef_geom = Mf_ROM_max; // If fref > fhigh we reset fref to default value of cutoff frequency.
  }
  if (fRef_geom < Mf_ROM_min) {
    XLALPrintWarning("Reference frequency Mf_ref=%g is smaller than lowest frequency in ROM Mf=%g. Starting at lowest frequency in ROM.\n", fRef_geom, Mf_ROM_min);
    fRef_geom = Mf_ROM_min;
  }

  /* Internal storage for w.f. coefficiencts */
  SEOBNRROMdataDS_coeff *romdata_coeff=NULL;
  SEOBNRROMdataDS_coeff_Init(&romdata_coeff);
  REAL8 amp_pre;

  /* Interpolate projection coefficients and evaluate them at (q,chi1,chi2) */
  retcode=TP_Spline_interpolation_3d(
    q,                         // Input: q-value for which projection coefficients should be evaluated
    chi1,                      // Input: chi1-value for which projection coefficients should be evaluated
    chi2,                      // Input: chi2-value for which projection coefficients should be evaluated
    romdata->cvec_amp,         // Input: data for spline coefficients for amplitude
    romdata->cvec_phi,         // Input: data for spline coefficients for phase
    romdata->cvec_amp_pre,     // Input: data for spline coefficients for amplitude prefactor
    romdata_coeff->c_amp,      // Output: interpolated projection coefficients for amplitude
    romdata_coeff->c_phi,      // Output: interpolated projection coefficients for phase
    &amp_pre                   // Output: interpolated amplitude prefactor
  );

  if(retcode!=0) {
    SEOBNRROMdataDS_coeff_Cleanup(romdata_coeff);
    XLAL_ERROR(retcode, "Parameter-space interpolation failed.");
  }

  // Compute function values of amplitude an phase on sparse frequency points by evaluating matrix vector products
  // amp_pts = B_A^T . c_A
  // phi_pts = B_phi^T . c_phi
  gsl_vector* amp_f = gsl_vector_alloc(nk_amp);
  gsl_vector* phi_f = gsl_vector_alloc(nk_phi);
  gsl_blas_dgemv(CblasTrans, 1.0, romdata->Bamp, romdata_coeff->c_amp, 0.0, amp_f);
  gsl_blas_dgemv(CblasTrans, 1.0, romdata->Bphi, romdata_coeff->c_phi, 0.0, phi_f);

  // Setup 1d splines in frequency
  gsl_interp_accel *acc_amp = gsl_interp_accel_alloc();
  gsl_spline *spline_amp = gsl_spline_alloc(gsl_interp_cspline, nk_amp);
  gsl_spline_init(spline_amp, gA, gsl_vector_const_ptr(amp_f,0), nk_amp);

  gsl_interp_accel *acc_phi = gsl_interp_accel_alloc();
  gsl_spline *spline_phi = gsl_spline_alloc(gsl_interp_cspline, nk_phi);
  gsl_spline_init(spline_phi, gPhi, gsl_vector_const_ptr(phi_f,0), nk_phi);


  size_t npts = 0;
  LIGOTimeGPS tC = {0, 0};
  UINT4 offset = 0; // Index shift between freqs and the frequency series
  REAL8Sequence *freqs = NULL;
  if (deltaF > 0)  { // freqs contains uniform frequency grid with spacing deltaF; we start at frequency 0
    /* Set up output array with size closest power of 2 */
    npts = NextPow2(fHigh_geom / deltaF_geom) + 1;
    if (fHigh_geom < fHigh * Mtot_sec) /* Resize waveform if user wants f_max larger than cutoff frequency */
      npts = NextPow2(fHigh * Mtot_sec / deltaF_geom) + 1;

    XLALGPSAdd(&tC, -1. / deltaF);  /* coalesce at t=0 */
    *hptilde = XLALCreateCOMPLEX16FrequencySeries("hptilde: FD waveform", &tC, 0.0, deltaF, &lalStrainUnit, npts);
    *hctilde = XLALCreateCOMPLEX16FrequencySeries("hctilde: FD waveform", &tC, 0.0, deltaF, &lalStrainUnit, npts);

    // Recreate freqs using only the lower and upper bounds
    // Use fLow, fHigh and deltaF rather than geometric frequencies for numerical accuracy
    double fHigh_temp = fHigh_geom / Mtot_sec;
    UINT4 iStart = (UINT4) ceil(fLow / deltaF);
    UINT4 iStop = (UINT4) ceil(fHigh_temp / deltaF);
    freqs = XLALCreateREAL8Sequence(iStop - iStart);
    if (!freqs) {
      XLAL_ERROR(XLAL_EFUNC, "Frequency array allocation failed.");
    }
    for (UINT4 i=iStart; i<iStop; i++)
      freqs->data[i-iStart] = i*deltaF_geom;

    offset = iStart;
  } else { // freqs contains frequencies with non-uniform spacing; we start at lowest given frequency
    npts = freqs_in->length;
    *hptilde = XLALCreateCOMPLEX16FrequencySeries("hptilde: FD waveform", &tC, fLow, 0, &lalStrainUnit, npts);
    *hctilde = XLALCreateCOMPLEX16FrequencySeries("hctilde: FD waveform", &tC, fLow, 0, &lalStrainUnit, npts);
    offset = 0;

    freqs = XLALCreateREAL8Sequence(freqs_in->length);
    if (!freqs) {
      XLAL_ERROR(XLAL_EFUNC, "Frequency array allocation failed.");
    }
    for (UINT4 i=0; i<freqs_in->length; i++)
      freqs->data[i] = freqs_in->data[i] * Mtot_sec;
  }


  if (!(*hptilde) || !(*hctilde))
  {
      XLALDestroyREAL8Sequence(freqs);

      gsl_spline_free(spline_amp);
      gsl_spline_free(spline_phi);
      gsl_interp_accel_free(acc_amp);
      gsl_interp_accel_free(acc_phi);
      gsl_vector_free(amp_f);
      gsl_vector_free(phi_f);
      SEOBNRROMdataDS_coeff_Cleanup(romdata_coeff);
      XLAL_ERROR(XLAL_EFUNC, "Waveform allocation failed.");
  }
  memset((*hptilde)->data->data, 0, npts * sizeof(COMPLEX16));
  memset((*hctilde)->data->data, 0, npts * sizeof(COMPLEX16));

  XLALUnitMultiply(&(*hptilde)->sampleUnits, &(*hptilde)->sampleUnits, &lalSecondUnit);
  XLALUnitMultiply(&(*hctilde)->sampleUnits, &(*hctilde)->sampleUnits, &lalSecondUnit);

  COMPLEX16 *pdata=(*hptilde)->data->data;
  COMPLEX16 *cdata=(*hctilde)->data->data;

  REAL8 cosi = cos(inclination);
  REAL8 pcoef = 0.5*(1.0 + cosi*cosi);
  REAL8 ccoef = cosi;

  REAL8 s = 0.5; // Scale polarization amplitude so that strain agrees with FFT of SEOBNRv1
  double Mtot = Mtot_sec / LAL_MTSUN_SI;
  double amp0 = Mtot * amp_pre * Mtot_sec * LAL_MRSUN_SI / (distance); // Correct overall amplitude to undo mass-dependent scaling used in ROM

  // Evaluate reference phase for setting phiRef correctly
  double phase_change = gsl_spline_eval(spline_phi, fRef_geom, acc_phi) - 2*phiRef;

  // Assemble waveform from aplitude and phase
  for (UINT4 i=0; i<freqs->length; i++) { // loop over frequency points in sequence
    double f = freqs->data[i];
    if (f > Mf_ROM_max) continue; // We're beyond the highest allowed frequency; since freqs may not be ordered, we'll just skip the current frequency and leave zero in the buffer
    int j = i + offset; // shift index for frequency series if needed
    double A = gsl_spline_eval(spline_amp, f, acc_amp);
    double phase = gsl_spline_eval(spline_phi, f, acc_phi) - phase_change;
    COMPLEX16 htilde = s*amp0*A * cexp(I*phase);
    pdata[j] =      pcoef * htilde;
    cdata[j] = -I * ccoef * htilde;
  }

  /* Correct phasing so we coalesce at t=0 (with the definition of the epoch=-1/deltaF above) */

  // Get SEOBNRv1 ringdown frequency for 22 mode
  double Mf_final = SEOBNRROM_Ringdown_Mf_From_Mtot_q(Mtot_sec, q, chi1, chi2, SEOBNRv1);

  UINT4 L = freqs->length;
  // prevent gsl interpolation errors
  if (Mf_final > freqs->data[L-1])
    Mf_final = freqs->data[L-1];
  if (Mf_final < freqs->data[0])
  {
      XLALDestroyREAL8Sequence(freqs);

      gsl_spline_free(spline_amp);
      gsl_spline_free(spline_phi);
      gsl_interp_accel_free(acc_amp);
      gsl_interp_accel_free(acc_phi);
      gsl_vector_free(amp_f);
      gsl_vector_free(phi_f);
      SEOBNRROMdataDS_coeff_Cleanup(romdata_coeff);
      XLAL_ERROR(XLAL_EDOM, "f_ringdown < f_min");
  }

  // Time correction is t(f_final) = 1/(2pi) dphi/df (f_final)
  // We compute the dimensionless time correction t/M since we use geometric units.
  REAL8 t_corr = gsl_spline_eval_deriv(spline_phi, Mf_final, acc_phi) / (2*LAL_PI);

  // Now correct phase
  for (UINT4 i=0; i<freqs->length; i++) { // loop over frequency points in sequence
    double f = freqs->data[i] - fRef_geom;
    int j = i + offset; // shift index for frequency series if needed
    pdata[j] *= cexp(-2*LAL_PI * I * f * t_corr);
    cdata[j] *= cexp(-2*LAL_PI * I * f * t_corr);
  }

  XLALDestroyREAL8Sequence(freqs);

  gsl_spline_free(spline_amp);
  gsl_spline_free(spline_phi);
  gsl_interp_accel_free(acc_amp);
  gsl_interp_accel_free(acc_phi);
  gsl_vector_free(amp_f);
  gsl_vector_free(phi_f);
  SEOBNRROMdataDS_coeff_Cleanup(romdata_coeff);

  return(XLAL_SUCCESS);
}