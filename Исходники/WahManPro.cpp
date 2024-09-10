static void DoWork(float *pin, float *pout, mi *pmi, int c, CTrack *trk)
{
  float ai=(float)(10*exp(-trk->Inertia*9.0));
  for (int i=0; i<c; i+=64) // pow(2,CurCutoff/48.0)
  {
    float LFO=0.0;
    float Phs=(float)fmod(trk->LFOPhase,(float)(2*PI));
    trk->ThevFactor=(float)(pmi->aval.thevfactor/20.0);
    switch(trk->LFOShape)
    {
      case 0: LFO=(float)sin(Phs); break;
      case 1: LFO=(float)(((Phs-PI)/PI-0.5f)*2.0f); break;
      case 2: LFO=(float)(((Phs-PI)/PI-0.5f)*-2.0f); break;
      case 3: LFO=(Phs<PI)?1.0f:-1.0f; break;
      case 4: LFO=(float)(((Phs<PI?(Phs/PI):(2.0-Phs/PI))-0.5)*2); break;
      case 5: LFO=(float)sin(trk->LFOPhase+PI/4*sin(trk->LFOPhase)); break;
      case 6: LFO=(float)sin(trk->LFOPhase+PI/6*sin(2*trk->LFOPhase)); break;
      case 7: LFO=(float)sin(2*trk->LFOPhase+PI*cos(3*trk->LFOPhase)); break;
      case 8: LFO=(float)(0.5*sin(2*trk->LFOPhase)+0.5*cos(3*trk->LFOPhase)); break;
    }
    float DestCutoff=(float)(trk->Cutoff+trk->LFODepth*LFO/2); // pow(2.0,trk->LFODepth*sin(trk->LFOPhase)/100.0);
    if (fabs(trk->CurCutoff-DestCutoff)<ai)
      trk->CurCutoff=DestCutoff;
    else
      trk->CurCutoff+=(float)_copysign(ai,DestCutoff-trk->CurCutoff);
    if (trk->FilterType==0) trk->CalcCoeffs1();
    if (trk->FilterType==1) trk->CalcCoeffs2();
    if (trk->FilterType==2) trk->CalcCoeffs3();
    if (trk->FilterType==3) trk->CalcCoeffs4();
    if (trk->FilterType==4) trk->CalcCoeffs5();

    int jmax=__min(i+64,c);
    if (trk->FilterType<3)
    {
      for (int j=i; j<jmax; j++)
      {
        pout[j]=trk->m_filter.ProcessSample(pin[j]);
      }
    }
    else
    {
      for (int j=i; j<jmax; j++)
      {
        pout[j]=trk->m_filter2.ProcessSample(trk->m_filter.ProcessSample(pin[j]));
      }
    }
    trk->LFOPhase+=(jmax-i)*trk->DeltaPhase;
  }
}