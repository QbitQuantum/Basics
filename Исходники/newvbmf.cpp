int
FilterParams::MakeExoFilt()
{
  if (!exofiltname.size())
    return 0;
  double total=0;
  VB_Vector exofilt(orderg);
  int i;
  VB_Vector IRF;

  if (kernelname.size()) {
    Vec xxx;
    xxx.ReadFile(kernelname.c_str());
    string trline=GetHeader(xxx.header,"TR(msecs)");
    if (trline.size()) {
      tokenlist tmpl;
      tmpl.ParseLine(trline);
      if (tmpl.size()>1)
        kerneltr=strtod(tmpl[1]);
    }
    printf("[I] vbmakefilter: using kernel TR of %.2f\n",kerneltr);
  }
  printf("[I] vbmakefilter: using data TR of %.2f\n",TR);

  for (i=0; i<orderg; i++)
    exofilt(i)=0.0;
  exofilt(0)=1.0;

  if (kernelname.size() > 0) {
    if (IRF.ReadFile(kernelname.c_str())) {
      printf("[E] vbmakefilter: couldn't read kernel file %s\n",kernelname.c_str());
      return 101;   // error!
    }
  }

  // interpolate the HRF to the resolution of your data
  if (kernelname.size()>0 && TR != kerneltr) {
    IRF=cspline_resize(IRF,kerneltr/TR);
  }

  // set exofilt to irf padded with zeros, scaled
  if (IRF.getLength()) {
    total=0.0;
    for (i=0; i<(int)IRF.getLength(); i++) {
      exofilt[i]=IRF[i];
      total+=IRF[i];
    }
    total /= orderg;
    for (i=0; i<orderg; i++)
      exofilt(i) -= total;
  }

  // do the notch filter

  // FIXME // FIXME!!! this is totally screwed up

  // note that the first element of the fft is the mean.  the second
  // and last elements are the first frequency.  etc.
  if (lows || highs || middles.size()) {
    int nfreq=orderg/2;
    VB_Vector realp(orderg),imagp(orderg);
    exofilt.fft(realp,imagp);
    realp(0)=imagp(0)=0.0;
    if (lows) {
      for (i=0; i<lows; i++) {
        if (i+1>nfreq) continue;
        realp(i+1)=imagp(i+1)=0.0;
        realp(orderg-i-1)=imagp(orderg-i-1)=0.0;
      }
    }
    for (size_t m=0; m<middles.size(); m++) {
      if (middles[m]>nfreq) continue;
      realp(middles[m])=imagp(middles[m])=0.0;
      int ind=orderg-middles[m];
      realp(ind)=imagp(ind)=0.0;
    }
    if (highs) {
      for (i=0; i<highs; i++) {
        int ind=nfreq-i;
        realp(ind)=imagp(ind)=0.0;
        ind=orderg-nfreq+i;
        realp(ind)=imagp(ind)=0.0;
      }
    }
    VB_Vector::complexIFFTReal(realp,imagp,exofilt);
  }

  // mean center it
  total=0.0;
  for (i=0; i<orderg; i++)
    total+=exofilt(i);
  total /= orderg;
  for (i=0; i<orderg; i++)
    exofilt(i)=exofilt(i)-total;

  // remove any phase component
  VB_Vector PS(exofilt.getLength());
  exofilt.getPS(PS);
  for (i=0; i<(int)PS.getLength(); i++)
    PS(i)=sqrt(PS(i));
  VB_Vector imagp(PS.getLength());
  PS.ifft(exofilt,imagp);

  // norm mag it
  exofilt.normMag();

  // write it out
  Vec tmpv(exofilt.getLength());
  MCopy(tmpv,exofilt);

  stringstream tmps;
  tmps.str("");
  tmps << "low frequencies filtered out: " << lows;
  tmpv.AddHeader(tmps.str());
  tmps.str("");
  tmps << "high frequencies filtered out: " << highs;
  tmpv.AddHeader(tmps.str());
  tmps.str("");
  tmps << "convolution kernel: " << kernelname;
  tmpv.AddHeader(tmps.str());

  tmpv.WriteFile(exofiltname.c_str());
  printf("[I] vbmakefilter: wrote filter %s\n",exofiltname.c_str());
  return 0;   // no error
}