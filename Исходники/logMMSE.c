void LogMmse(LogMMSE* logmmse,float* Y,float* Xest)
{

		int i=nFFT-1,j;
		int psiNTdB,gammadB;
		float temp,vk,eivk;
		float gamma[nFFT],psi[nFFT],psiNT[nFFT],SafetyNetPmin[nFFT],NoiseEst[nFFT],smoothpost[nFFT];
		double Speechpresenceprob[nFFT];

		//*******Initial Noise variance Estimation assuming 1st 6 frames are noise********//
		if(framecounter <= 6)
		{
			do
			{
				logmmse->noiseMu[i]+= sqrt(Y[i]);          // Noise mean
				i--;
			}while(i>=0);

			i=nFFT-1;
			do
			{
				logmmse->noiseVar[i] = (float)logmmse->noiseMu[i]*logmmse->noiseMu[i]*2.777777777777778e-02; 	//(abs(fft)/6)^2
				i--;
			}while(i>=0);
		}

		i=nFFT-1;
		do
		{
			gamma[i] = min((Y[i]/logmmse->noiseVar[i]),40);

			if(framecounter == 1)
			{
				psi[i] = 0.98 + 0.02*max((gamma[i]-1),0);
				psiNT[i] = max((0.98 + 0.02*gamma[i]),0.003162277660168);
				logmmse->SafetyNetP[i][SafetyNetInd] = 0.9*Y[i];
			}
			else
			{
				psi[i] = 0.98*(double)logmmse->X[i]/logmmse->noiseVar[i] + 0.02*max((gamma[i]-1),0);
				psi[i] = max(psi[i],0.003162277660168);  														// limiting psi to -25dB
				psiNT[i] = max((0.98*logmmse->Yprev[i]/logmmse->noiseVar[i]+0.02*gamma[i]),0.003162277660168);
				if(SafetyNetInd > 0) logmmse->SafetyNetP[i][SafetyNetInd] = 0.1*logmmse->SafetyNetP[i][SafetyNetInd-1]+0.9*Y[i];
				else logmmse->SafetyNetP[i][SafetyNetInd] = 0.1*logmmse->SafetyNetP[i][numWinPmin]+0.9*Y[i];
			}

			//*******Setting SafetynetPmin********//
			temp = logmmse->SafetyNetP[i][0];
			j=numWinPmin-1;
			do{
				if(temp>logmmse->SafetyNetP[i][j]) temp = logmmse->SafetyNetP[i][j];
				j--;
			}while(j>=0);
			SafetyNetPmin[i] = temp;

			//*******Fetching Noise Estimate********//
			logmmse->Yprev[i] = Y[i];
			psiNTdB = round(max(min(10.0*log10f(psiNT[i]),40),-19))+19;
			gammadB = round(max(min(10.0*log10f(gamma[i]),40),-30))+30;
			NoiseEst[i] = GainTable[classdecision][71*psiNTdB+gammadB]*Y[i];

			i--;
		}while(i >= 0);

		//*******Frequency Smoothing********//
		smoothpost[0] = (gamma[0]+gamma[1])/2;
		i = nFFT-2;
		do
		{
			smoothpost[i] = (gamma[i-1]+gamma[i]+gamma[i+1])/3;
			i--;
		}while(i>0);
		smoothpost[nFFT-1] = (gamma[nFFT-1]+gamma[nFFT-2])/2;

		i=nFFT-1;
		do
		{
			//*******Updating NoiseVariance for next frame********//
			if(framecounter == 1) Speechpresenceprob[i] = (double)0.9;
			else Speechpresenceprob[i] =  (double)0.1*Speechpresenceprob[i]+(double)0.9*(smoothpost[i]>4);

			alphas = 0.85 + 0.15 * Speechpresenceprob[i];
			logmmse->noiseVar[i] = alphas*logmmse->noiseVar[i] + (1-alphas)*NoiseEst[i];

			if((1.5*SafetyNetPmin[i]) > logmmse->noiseVar[i])
			{
				Speechpresenceprob[i] = 0;
				logmmse->noiseVar[i] = 1.5*SafetyNetPmin[i];
			}

			//*******log MMSE Estimator********//
			temp = psi[i]/(1+psi[i]);
			vk = gamma[i]*temp;
			expint(&vk,&eivk);                                  //Evaluating the exponential integral part
			Xest[i] = temp*exp(eivk);
			logmmse->X[i] = Y[i]*Xest[i]*Xest[i];

			i--;
		}while(i>=0);

		SafetyNetInd = SafetyNetInd+1;
		if(SafetyNetInd>=numWinPmin) SafetyNetInd = 0;
		framecounter++;
}