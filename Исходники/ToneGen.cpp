bool EffectToneGen::MakeTone(float *buffer, sampleCount len)
{
   double throwaway = 0;        //passed to modf but never used
   sampleCount i;
   double f = 0.0;
   double a,b;
   int k;

   double frequencyQuantum;
   double BlendedFrequency;
   double BlendedAmplitude;
   double BlendedLogFrequency = 0.0f;

   // calculate delta, and reposition from where we left
   double amplitudeQuantum = (amplitude[1]-amplitude[0]) / numSamples;
   BlendedAmplitude = amplitude[0] + amplitudeQuantum * mSample;

   // precalculations:
   double pre2PI = 2 * M_PI;
   double pre4divPI = 4. / M_PI;

   // initial setup should calculate deltas
   if( mbLogInterpolation )
   {
      // this for log interpolation
      logFrequency[0] = log10( frequency[0] );
      logFrequency[1] = log10( frequency[1] );
      // calculate delta, and reposition from where we left
      frequencyQuantum = (logFrequency[1]-logFrequency[0]) / numSamples;
      BlendedLogFrequency = logFrequency[0] + frequencyQuantum * mSample;
      BlendedFrequency = pow( 10.0, (double)BlendedLogFrequency );
   } else {
      // this for regular case, linear interpolation
      frequencyQuantum = (frequency[1]-frequency[0]) / numSamples;
      BlendedFrequency = frequency[0] + frequencyQuantum * mSample;
   }

   // synth loop
   for (i = 0; i < len; i++) {
      switch (waveform) {
      case 0:    //sine
         f = (float) sin(pre2PI * mPositionInCycles/mCurRate);
         break;
      case 1:    //square
         f = (modf(mPositionInCycles/mCurRate, &throwaway) < 0.5) ? 1.0f :-1.0f;
         break;
      case 2:    //sawtooth
         f = (2 * modf(mPositionInCycles/mCurRate+0.5f, &throwaway)) -1.0f;
         break;
      case 3:    //square, no alias.  Good down to 110Hz @ 44100Hz sampling.
         //do fundamental (k=1) outside loop
         b = (1. + cos((pre2PI * BlendedFrequency)/mCurRate))/pre4divPI;  //scaling
         f = (float) pre4divPI * sin(pre2PI * mPositionInCycles/mCurRate);
         for(k=3; (k<200) && (k * BlendedFrequency < mCurRate/2.); k+=2)
            {
               //Hanning Window in freq domain
               a = 1. + cos((pre2PI * k * BlendedFrequency)/mCurRate);
               //calc harmonic, apply window, scale to amplitude of fundamental
               f += (float) a * sin(pre2PI * mPositionInCycles/mCurRate * k)/(b*k);
            }
      }
      // insert value in buffer
      buffer[i] = BlendedAmplitude * f;
      // update freq,amplitude
      mPositionInCycles += BlendedFrequency;
      BlendedAmplitude += amplitudeQuantum;
      if (mbLogInterpolation) {
         BlendedLogFrequency += frequencyQuantum;
         BlendedFrequency = pow( 10.0, (double)BlendedLogFrequency);
      } else {
         BlendedFrequency += frequencyQuantum;
      }
   }

   // update external placeholder
   mSample += len;
   return true;
}