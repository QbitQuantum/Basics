void pvcDecodeTimeSlot(PVC_STATIC_DATA *pPvcStaticData,
                       PVC_DYNAMIC_DATA *pPvcDynamicData,
                       FIXP_DBL **qmfSlotReal, FIXP_DBL **qmfSlotImag,
                       const int qmfExponent, const int pvcBorder0,
                       const int timeSlotNumber, FIXP_DBL predictedEsgSlot[],
                       int *predictedEsg_exp) {
  int i, band, ksg, ksg_start = 0;
  int RATE = pPvcDynamicData->RATE;
  int Esg_index = pPvcStaticData->Esg_slot_index;
  const SCHAR *sg_borders = pPvcDynamicData->sg_offset_low;
  FIXP_DBL *pEsg = pPvcStaticData->Esg[Esg_index];
  FIXP_DBL E[PVC_NBLOW] = {0};

  /* Subband grouping in QMF subbands below SBR range */
  /* Within one timeslot ( i = [0...(RATE-1)] QMF subsamples) calculate energy
     E(ib,t) and group them to Esg(ksg,t). Then transfer values to logarithmical
     domain and store them for time domain smoothing. (7.5.6.3 Subband grouping
     in QMF subbands below SBR range)
  */
  for (ksg = 0; sg_borders[ksg] < 0; ksg++) {
    pEsg[ksg] = FL2FXCONST_DBL(-10.0 / (1 << PVC_ESG_EXP)); /* 10*log10(0.1) */
    ksg_start++;
  }

  for (i = 0; i < RATE; i++) {
    FIXP_DBL *qmfR, *qmfI;
    qmfR = qmfSlotReal[i];
    qmfI = qmfSlotImag[i];
    for (ksg = ksg_start; ksg < PVC_NBLOW; ksg++) {
      for (band = sg_borders[ksg]; band < sg_borders[ksg + 1]; band++) {
        /* The division by 8 == (RATE*lbw) is required algorithmically */
        E[ksg] += (fPow2Div2(qmfR[band]) + fPow2Div2(qmfI[band])) >> 2;
      }
    }
  }
  for (ksg = ksg_start; ksg < PVC_NBLOW; ksg++) {
    if (E[ksg] > (FIXP_DBL)0) {
      /* 10/log2(10) = 0.752574989159953 * 2^2 */
      int exp_log;
      FIXP_DBL nrg = CalcLog2(E[ksg], 2 * qmfExponent, &exp_log);
      nrg = fMult(nrg, FL2FXCONST_SGL(LOG10FAC));
      nrg = scaleValue(nrg, exp_log - PVC_ESG_EXP + 2);
      pEsg[ksg] = fMax(nrg, FL2FXCONST_DBL(-10.0 / (1 << PVC_ESG_EXP)));
    } else {
      pEsg[ksg] =
          FL2FXCONST_DBL(-10.0 / (1 << PVC_ESG_EXP)); /* 10*log10(0.1) */
    }
  }

  /* Time domain smoothing of subband-grouped energy */
  {
    int idx = pPvcStaticData->Esg_slot_index;
    FIXP_DBL *pEsg_filt;
    FIXP_SGL SCcoeff;

    E[0] = E[1] = E[2] = (FIXP_DBL)0;
    for (i = 0; i < pPvcDynamicData->ns; i++) {
      SCcoeff = pPvcDynamicData->pSCcoeffs[i];
      pEsg_filt = pPvcStaticData->Esg[idx];
      /* Div2 is compensated by scaling of coeff table */
      E[0] = fMultAddDiv2(E[0], pEsg_filt[0], SCcoeff);
      E[1] = fMultAddDiv2(E[1], pEsg_filt[1], SCcoeff);
      E[2] = fMultAddDiv2(E[2], pEsg_filt[2], SCcoeff);
      if (i >= pPvcDynamicData->pastEsgSlotsAvail) {
        /* if past Esg values are not available use the ones from the last valid
         * slot */
        continue;
      }
      if (idx > 0) {
        idx--;
      } else {
        idx += PVC_NS_MAX - 1;
      }
    }
  }

  /* SBR envelope scalefactor prediction */
  {
    int E_high_exp[PVC_NBHIGH_MAX];
    int E_high_exp_max = 0;
    int pvcTab1ID;
    int pvcTab2ID = (int)pPvcDynamicData->pPvcID[timeSlotNumber];
    const UCHAR *pTab1, *pTab2;
    if (pvcTab2ID < pPvcDynamicData->pPVCTab1_dp[0]) {
      pvcTab1ID = 0;
    } else if (pvcTab2ID < pPvcDynamicData->pPVCTab1_dp[1]) {
      pvcTab1ID = 1;
    } else {
      pvcTab1ID = 2;
    }
    pTab1 = &(pPvcDynamicData
                  ->pPVCTab1[pvcTab1ID * PVC_NBLOW * pPvcDynamicData->nbHigh]);
    pTab2 = &(pPvcDynamicData->pPVCTab2[pvcTab2ID * pPvcDynamicData->nbHigh]);
    for (ksg = 0; ksg < pPvcDynamicData->nbHigh; ksg++) {
      FIXP_SGL predCoeff;
      FIXP_DBL accu;
      int predCoeff_exp, kb;
      E_high_exp[ksg] = 0;

      /* residual part */
      accu = ((LONG)(SCHAR)*pTab2++) << (DFRACT_BITS - 8 - PVC_ESG_EXP +
                                         pPvcDynamicData->pScalingCoef[3]);

      /* linear combination of lower grouped energies part */
      for (kb = 0; kb < PVC_NBLOW; kb++) {
        predCoeff = (FIXP_SGL)(
            (SHORT)(SCHAR)pTab1[kb * pPvcDynamicData->nbHigh + ksg] << 8);
        predCoeff_exp = pPvcDynamicData->pScalingCoef[kb] +
                        1; /* +1 to compensate for Div2 */
        accu += fMultDiv2(E[kb], predCoeff) << predCoeff_exp;
      }
      /* convert back to linear domain */
      accu = fMult(accu, FL2FXCONST_SGL(LOG10FAC_INV));
      accu = f2Pow(
          accu, PVC_ESG_EXP - 1,
          &predCoeff_exp); /* -1 compensates for exponent of LOG10FAC_INV */
      predictedEsgSlot[ksg] = accu;
      E_high_exp[ksg] = predCoeff_exp;
      if (predCoeff_exp > E_high_exp_max) {
        E_high_exp_max = predCoeff_exp;
      }
    }

    /* rescale output vector according to largest exponent */
    for (ksg = 0; ksg < pPvcDynamicData->nbHigh; ksg++) {
      int scale = E_high_exp[ksg] - E_high_exp_max;
      predictedEsgSlot[ksg] = scaleValue(predictedEsgSlot[ksg], scale);
    }
    *predictedEsg_exp = E_high_exp_max;
  }

  pPvcStaticData->Esg_slot_index =
      (pPvcStaticData->Esg_slot_index + 1) & (PVC_NS_MAX - 1);
  pPvcDynamicData->pastEsgSlotsAvail =
      fMin(pPvcDynamicData->pastEsgSlotsAvail + 1, PVC_NS_MAX - 1);
  return;
}