void palPertue( double date, double u[13], int *jstat ) {

  /*  Distance from EMB at which Earth and Moon are treated separately */
  const double RNE=1.0;

  /*  Coincidence with major planet distance */
  const double COINC=0.0001;

  /*  Coefficient relating timestep to perturbing force */
  const double TSC=1e-4;

  /*  Minimum and maximum timestep (days) */
  const double TSMIN = 0.01;
  const double TSMAX = 10.0;

  /*  Age limit for major-planet state vector (days) */
  const double AGEPMO=5.0;

  /*  Age limit for major-planet mean elements (days) */
  const double AGEPEL=50.0;

  /*  Margin for error when deciding whether to renew the planetary data */
  const double TINY=1e-6;

  /*  Age limit for the body's osculating elements (before rectification) */
  const double AGEBEL=100.0;

  /*  Gaussian gravitational constant squared */
  const double GCON2 = PAL__GCON * PAL__GCON;

  /*  The final epoch */
  double TFINAL;

  /*  The body's current universal elements */
  double UL[13];

  /*  Current reference epoch */
  double T0;

  /*  Timespan from latest orbit rectification to final epoch (days) */
  double TSPAN;

  /*  Time left to go before integration is complete */
  double TLEFT;

  /*  Time direction flag: +1=forwards, -1=backwards */
  double FB;

  /*  First-time flag */
  int FIRST = 0;

  /*
   *  The current perturbations
   */

  /*  Epoch (days relative to current reference epoch) */
  double RTN;
  /*  Position (AU) */
  double PERP[3];
  /*  Velocity (AU/d) */
  double PERV[3];
  /*  Acceleration (AU/d/d) */
  double PERA[3];

  /*  Length of current timestep (days), and half that */
  double TS,HTS;

  /*  Epoch of middle of timestep */
  double T;

  /*  Epoch of planetary mean elements */
  double TPEL = 0.0;

  /*  Planet number (1=Mercury, 2=Venus, 3=EMB...8=Neptune) */
  int NP;

  /*  Planetary universal orbital elements */
  double UP[8][13];

  /*  Epoch of planetary state vectors */
  double TPMO = 0.0;

  /*  State vectors for the major planets (AU,AU/s) */
  double PVIN[8][6];

  /*  Earth velocity and position vectors (AU,AU/s) */
  double VB[3],PB[3],VH[3],PE[3];

  /*  Moon geocentric state vector (AU,AU/s) and position part */
  double PVM[6],PM[3];

  /*  Date to J2000 de-precession matrix */
  double PMAT[3][3];

  /*
   *  Correction terms for extrapolated major planet vectors
   */

  /*  Sun-to-planet distances squared multiplied by 3 */
  double R2X3[8];
  /*  Sunward acceleration terms, G/2R^3 */
  double GC[8];
  /*  Tangential-to-circular correction factor */
  double FC;
  /*  Radial correction factor due to Sunwards acceleration */
  double FG;

  /*  The body's unperturbed and perturbed state vectors (AU,AU/s) */
  double PV0[6],PV[6];

  /*  The body's perturbed and unperturbed heliocentric distances (AU) cubed */
  double R03,R3;

  /*  The perturbating accelerations, indirect and direct */
  double FI[3],FD[3];

  /*  Sun-to-planet vector, and distance cubed */
  double RHO[3],RHO3;

  /*  Body-to-planet vector, and distance cubed */
  double DELTA[3],DELTA3;

  /*  Miscellaneous */
  int I,J;
  double R2,W,DT,DT2,R,FT;
  int NE;

  /*  Planetary inverse masses, Mercury through Neptune then Earth and Moon */
  const double AMAS[10] = {
    6023600., 408523.5, 328900.5, 3098710.,
    1047.355, 3498.5, 22869., 19314.,
    332946.038, 27068709.
  };

  /*  Preset the status to OK. */
  *jstat = 0;

  /*  Copy the final epoch. */
  TFINAL = date;

  /*  Copy the elements (which will be periodically updated). */
  for (I=0; I<13; I++) {
    UL[I] = u[I];
  }

/*  Initialize the working reference epoch. */
  T0=UL[2];

  /*  Total timespan (days) and hence time left. */
  TSPAN = TFINAL-T0;
  TLEFT = TSPAN;

  /*  Warn if excessive. */
  if (fabs(TSPAN) > 36525.0) *jstat=101;

  /*  Time direction: +1 for forwards, -1 for backwards. */
  FB = COPYSIGN(1.0,TSPAN);

  /*  Initialize relative epoch for start of current timestep. */
  RTN = 0.0;

  /*  Reset the perturbations (position, velocity, acceleration). */
  for (I=0; I<3; I++) {
    PERP[I] = 0.0;
    PERV[I] = 0.0;
    PERA[I] = 0.0;
  }

  /*  Set "first iteration" flag. */
  FIRST = 1;

  /*  Step through the time left. */
  while (FB*TLEFT > 0.0) {

    /*     Magnitude of current acceleration due to planetary attractions. */
    if (FIRST) {
      TS = TSMIN;
    } else {
      R2 = 0.0;
      for (I=0; I<3; I++) {
        W = FD[I];
        R2 = R2+W*W;
      }
      W = sqrt(R2);

      /*        Use the acceleration to decide how big a timestep can be tolerated. */
      if (W != 0.0) {
        TS = DMIN(TSMAX,DMAX(TSMIN,TSC/W));
      } else {
        TS = TSMAX;
      }
    }
    TS = TS*FB;

    /*     Override if final epoch is imminent. */
    TLEFT = TSPAN-RTN;
    if (fabs(TS) > fabs(TLEFT)) TS=TLEFT;

    /*     Epoch of middle of timestep. */
    HTS = TS/2.0;
    T = T0+RTN+HTS;

    /*     Is it time to recompute the major-planet elements? */
    if (FIRST || fabs(T-TPEL)-AGEPEL >= TINY) {

      /*        Yes: go forward in time by just under the maximum allowed. */
      TPEL = T+FB*AGEPEL;

      /*        Compute the state vector for the new epoch. */
      for (NP=1; NP<=8; NP++) {
        palPlanet(TPEL,NP,PV,&J);

        /*           Warning if remote epoch, abort if error. */
        if (J == 1) {
          *jstat = 102;
        } else if (J != 0) {
          goto ABORT;
        }

        /*           Transform the vector into universal elements. */
        palPv2ue(PV,TPEL,0.0,&(UP[NP-1][0]),&J);
        if (J != 0) goto ABORT;
      }
    }

    /*     Is it time to recompute the major-planet motions? */
    if (FIRST || fabs(T-TPMO)-AGEPMO >= TINY) {

      /*        Yes: look ahead. */
      TPMO = T+FB*AGEPMO;

      /*        Compute the motions of each planet (AU,AU/d). */
      for (NP=1; NP<=8; NP++) {

        /*           The planet's position and velocity (AU,AU/s). */
        palUe2pv(TPMO,&(UP[NP-1][0]),&(PVIN[NP-1][0]),&J);
        if (J != 0) goto ABORT;

        /*           Scale velocity to AU/d. */
        for (J=3; J<6; J++) {
          PVIN[NP-1][J] = PVIN[NP-1][J]*PAL__SPD;
        }

        /*           Precompute also the extrapolation correction terms. */
        R2 = 0.0;
        for (I=0; I<3; I++) {
          W = PVIN[NP-1][I];
          R2 = R2+W*W;
        }
        R2X3[NP-1] = R2*3.0;
        GC[NP-1] = GCON2/(2.0*R2*sqrt(R2));
      }
    }

    /*     Reset the first-time flag. */
    FIRST = 0;

    /*     Unperturbed motion of the body at middle of timestep (AU,AU/s). */
    palUe2pv(T,UL,PV0,&J);
    if (J != 0) goto ABORT;

    /*     Perturbed position of the body (AU) and heliocentric distance cubed. */
    R2 = 0.0;
    for (I=0; I<3; I++) {
      W = PV0[I]+PERP[I]+(PERV[I]+PERA[I]*HTS/2.0)*HTS;
      PV[I] = W;
      R2 = R2+W*W;
    }
    R3 = R2*sqrt(R2);

    /*     The body's unperturbed heliocentric distance cubed. */
    R2 = 0.0;
    for (I=0; I<3; I++) {
      W = PV0[I];
      R2 = R2+W*W;
    }
    R03 = R2*sqrt(R2);

    /*     Compute indirect and initialize direct parts of the perturbation. */
    for (I=0; I<3; I++) {
      FI[I] = PV0[I]/R03-PV[I]/R3;
      FD[I] = 0.0;
    }

    /*     Ready to compute the direct planetary effects. */

    /*     Reset the "near-Earth" flag. */
    NE = 0;

    /*     Interval from state-vector epoch to middle of current timestep. */
    DT = T-TPMO;
    DT2 = DT*DT;

    /*     Planet by planet, including separate Earth and Moon. */
    for (NP=1; NP<10; NP++) {

      /*        Which perturbing body? */
      if (NP <= 8) {

        /*           Planet: compute the extrapolation in longitude (squared). */
        R2 = 0.0;
        for (J=3; J<6; J++) {
          W = PVIN[NP-1][J]*DT;
          R2 = R2+W*W;
        }

        /*           Hence the tangential-to-circular correction factor. */
        FC = 1.0+R2/R2X3[NP-1];

        /*           The radial correction factor due to the inwards acceleration. */
        FG = 1.0-GC[NP-1]*DT2;

        /*           Planet's position. */
        for (I=0; I<3; I++) {
          RHO[I] = FG*(PVIN[NP-1][I]+FC*PVIN[NP-1][I+3]*DT);
        }

      } else if (NE) {

        /*           Near-Earth and either Earth or Moon. */

        if (NP == 9) {

          /*              Earth: position. */
          palEpv(T,PE,VH,PB,VB);
          for (I=0; I<3; I++) {
            RHO[I] = PE[I];
          }

        } else {

          /*              Moon: position. */
          palPrec(palEpj(T),2000.0,PMAT);
          palDmoon(T,PVM);
          eraRxp(PMAT,PVM,PM);
          for (I=0; I<3; I++) {
            RHO[I] = PM[I]+PE[I];
          }
        }
      }

      /*        Proceed unless Earth or Moon and not the near-Earth case. */
      if (NP <= 8 || NE) {

        /*           Heliocentric distance cubed. */
        R2 = 0.0;
        for (I=0; I<3; I++) {
          W = RHO[I];
          R2 = R2+W*W;
        }
        R = sqrt(R2);
        RHO3 = R2*R;

        /*           Body-to-planet vector, and distance. */
        R2 = 0.0;
        for (I=0; I<3; I++) {
          W = RHO[I]-PV[I];
          DELTA[I] = W;
          R2 = R2+W*W;
        }
        R = sqrt(R2);

        /*           If this is the EMB, set the near-Earth flag appropriately. */
        if (NP == 3 && R < RNE) NE = 1;

        /*           Proceed unless EMB and this is the near-Earth case. */
        if ( ! (NE && NP == 3) ) {

          /*              If too close, ignore this planet and set a warning. */
          if (R < COINC) {
            *jstat = NP;

          } else {

            /*                 Accumulate "direct" part of perturbation acceleration. */
            DELTA3 = R2*R;
            W = AMAS[NP-1];
            for (I=0; I<3; I++) {
              FD[I] = FD[I]+(DELTA[I]/DELTA3-RHO[I]/RHO3)/W;
            }
          }
        }
      }
    }

    /*     Update the perturbations to the end of the timestep. */
    RTN += TS;
    for (I=0; I<3; I++) {
      W = (FI[I]+FD[I])*GCON2;
      FT = W*TS;
      PERP[I] = PERP[I]+(PERV[I]+FT/2.0)*TS;
      PERV[I] = PERV[I]+FT;
      PERA[I] = W;
    }

    /*     Time still to go. */
    TLEFT = TSPAN-RTN;

    /*     Is it either time to rectify the orbit or the last time through? */
    if (fabs(RTN) >= AGEBEL || FB*TLEFT <= 0.0) {

      /*        Yes: update to the end of the current timestep. */
      T0 += RTN;
      RTN = 0.0;

      /*        The body's unperturbed motion (AU,AU/s). */
      palUe2pv(T0,UL,PV0,&J);
      if (J != 0) goto ABORT;

      /*        Add and re-initialize the perturbations. */
      for (I=0; I<3; I++) {
        J = I+3;
        PV[I] = PV0[I]+PERP[I];
        PV[J] = PV0[J]+PERV[I]/PAL__SPD;
        PERP[I] = 0.0;
        PERV[I] = 0.0;
        PERA[I] = FD[I]*GCON2;
      }

      /*        Use the position and velocity to set up new universal elements. */
      palPv2ue(PV,T0,0.0,UL,&J);
      if (J != 0) goto ABORT;

      /*        Adjust the timespan and time left. */
      TSPAN = TFINAL-T0;
      TLEFT = TSPAN;
    }

    /*     Next timestep. */
  }

  /*  Return the updated universal-element set. */
  for (I=0; I<13; I++) {
    u[I] = UL[I];
  }

  /*  Finished. */
  return;

  /*  Miscellaneous numerical error. */
 ABORT:
  *jstat = -1;
  return;
}