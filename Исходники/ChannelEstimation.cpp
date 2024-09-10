void CChannelEstimation::GetTransferFunction(CVector<_REAL>& vecrData,
											 CVector<_REAL>& vecrGrpDly)
{
	/* Init output vectors */
	vecrData.Init(iNumCarrier, (_REAL) 0.0);
	vecrGrpDly.Init(iNumCarrier, (_REAL) 0.0);

	/* Do copying of data only if vector is of non-zero length which means that
	   the module was already initialized */
	if (iNumCarrier != 0)
	{
		_REAL rDiffPhase, rOldPhase;

		/* Lock resources */
		Lock();

		/* Init constant for normalization */
		const _REAL rTu = (CReal) iFFTSizeN / SOUNDCRD_SAMPLE_RATE;

		/* Copy data in output vector and set scale 
		   (carrier index as x-scale) */
		for (int i = 0; i < iNumCarrier; i++)
		{
			/* Transfer function */
			CReal rNormChanEst = Abs(veccChanEst[i]) / (CReal) iNumCarrier;
				
			if (rNormChanEst > 0)
				vecrData[i] = (CReal) 20.0 * Log10(rNormChanEst);
			else
				vecrData[i] = RET_VAL_LOG_0;

			/* Group delay */
			if (i == 0)
			{
				/* At position 0 we cannot calculate a derivation -> use
				   the same value as position 0 */
				rDiffPhase = Angle(veccChanEst[1]) - Angle(veccChanEst[0]);
			}
			else
				rDiffPhase = Angle(veccChanEst[i]) - rOldPhase;

			/* Take care of wrap around of angle() function */
			if (rDiffPhase > WRAP_AROUND_BOUND_GRP_DLY)
				rDiffPhase -= 2.0 * crPi;
			if (rDiffPhase < -WRAP_AROUND_BOUND_GRP_DLY)
				rDiffPhase += 2.0 * crPi;

			/* Apply normalization */
			vecrGrpDly[i] = rDiffPhase * rTu * 1000.0 /* ms */;

			/* Store old phase */
			rOldPhase = Angle(veccChanEst[i]);

		}

		/* Release resources */
		Unlock();
	}
}