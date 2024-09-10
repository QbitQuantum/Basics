void synthesise(
  kiss_fft_cfg fft_inv_cfg, 
  float  Sn_[],		/* time domain synthesised signal              */
  MODEL *model,		/* ptr to model parameters for this frame      */
  float  Pn[],		/* time domain Parzen window                   */
  int    shift          /* flag used to handle transition frames       */
)
{
    int   i,l,j,b;	/* loop variables */
    COMP  Sw_[FFT_DEC];	/* DFT of synthesised signal */
    COMP  sw_[FFT_DEC];	/* synthesised signal */

    if (shift) {
	/* Update memories */
	for(i=0; i<N-1; i++) {
	    Sn_[i] = Sn_[i+N];
	}
	Sn_[N-1] = 0.0;
    }

    for(i=0; i<FFT_DEC; i++) {
	Sw_[i].real = 0.0;
	Sw_[i].imag = 0.0;
    }

    /*
      Nov 2010 - found that synthesis using time domain cos() functions
      gives better results for synthesis frames greater than 10ms.  Inverse
      FFT synthesis using a 512 pt FFT works well for 10ms window.  I think
      (but am not sure) that the problem is related to the quantisation of
      the harmonic frequencies to the FFT bin size, e.g. there is a 
      8000/512 Hz step between FFT bins.  For some reason this makes
      the speech from longer frame > 10ms sound poor.  The effect can also
      be seen when synthesising test signals like single sine waves, some
      sort of amplitude modulation at the frame rate.

      Another possibility is using a larger FFT size (1024 or 2048).
    */

#define FFT_SYNTHESIS
#ifdef FFT_SYNTHESIS
    /* Now set up frequency domain synthesised speech */
    for(l=1; l<=model->L; l++) {
    //for(l=model->L/2; l<=model->L; l++) {
    //for(l=1; l<=model->L/4; l++) {
	b = (int)(l*model->Wo*FFT_DEC/TWO_PI + 0.5);
	if (b > ((FFT_DEC/2)-1)) {
		b = (FFT_DEC/2)-1;
	}
	Sw_[b].real = model->A[l]*cosf(model->phi[l]);
	Sw_[b].imag = model->A[l]*sinf(model->phi[l]);
	Sw_[FFT_DEC-b].real = Sw_[b].real;
	Sw_[FFT_DEC-b].imag = -Sw_[b].imag;
    }

    /* Perform inverse DFT */

    kiss_fft(fft_inv_cfg, (kiss_fft_cpx *)Sw_, (kiss_fft_cpx *)sw_);
#else
    /*
       Direct time domain synthesis using the cos() function.  Works
       well at 10ms and 20ms frames rates.  Note synthesis window is
       still used to handle overlap-add between adjacent frames.  This
       could be simplified as we don't need to synthesise where Pn[]
       is zero.
    */
    for(l=1; l<=model->L; l++) {
	for(i=0,j=-N+1; i<N-1; i++,j++) {
	    Sw_[FFT_DEC-N+1+i].real += 2.0*model->A[l]*cos(j*model->Wo*l + model->phi[l]);
	}
 	for(i=N-1,j=0; i<2*N; i++,j++)
	    Sw_[j].real += 2.0*model->A[l]*cos(j*model->Wo*l + model->phi[l]);
    }	
#endif

    /* Overlap add to previous samples */

    for(i=0; i<N-1; i++) {
	Sn_[i] += sw_[FFT_DEC-N+1+i].real*Pn[i];
    }

    if (shift)
	for(i=N-1,j=0; i<2*N; i++,j++)
	    Sn_[i] = sw_[j].real*Pn[i];
    else
	for(i=N-1,j=0; i<2*N; i++,j++)
	    Sn_[i] += sw_[j].real*Pn[i];
}