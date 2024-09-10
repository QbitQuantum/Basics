static void PrintProfile(const Fprec *ProfileCounts, int nProfileSteps,
                         const T_StdPeak *StdPeak)
{
  int          iPS;
  Fprec        TT, Counts, ScaleF, MaxScaledCounts, ESD;


  Fprintf(stdout, ">Begin stepscan\n");

  Fprintf(stdout, "@with g0\n");

  ScaleF = ProfileScaleFactor(ProfileCounts, nProfileSteps, StdPeak);

  MaxScaledCounts = 0.;

  for (iPS = 0; iPS < nProfileSteps; iPS++)
  {
        TT = iPS * ProfileStep;
    if (TT + ProfileStep * .5 < ProfileStart)
      continue;
    if (TT - ProfileStep * .5 > ProfileEnd)
      break;

    Counts = ProfileBackground + ProfileCounts[iPS] * ScaleF;

        ESD = AppSqrt(Counts);
    if (ESD < 0.001)
        ESD = 0.001;

    Fprintf(stdout, "%12.3f %12.2f %12.3f\n",
      TT, Counts, ESD);

    if (MaxScaledCounts < Counts)
        MaxScaledCounts = Counts;
  }

  if (MaxScaledCounts == 0.)
      MaxScaledCounts = ProfileReferenceMax;
  if (MaxScaledCounts == 0.)
      MaxScaledCounts = 1.;

  Fprintf(stdout, "&\n");
  Fprintf(stdout, "@autoscale\n");

  Fprintf(stdout, "@ world xmin %.6g\n", ProfileStart);
  Fprintf(stdout, "@ world xmax %.6g\n", ProfileEnd);
  Fprintf(stdout, "@ world ymin %.6g\n", 0.);
  Fprintf(stdout, "@ world ymax %.6g\n", MaxScaledCounts);

  Fprintf(stdout, ">End stepscan\n");
  putc('\n', stdout);
}