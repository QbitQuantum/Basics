//calculation function once FFT data ready
void KeyTrack_calculatekey(KeyTrack *unit, uint32 ibufnum)
{
	World *world = unit->mWorld;
	
    SndBuf *buf;
    
    if (ibufnum >= world->mNumSndBufs) { 
		int localBufNum = ibufnum - world->mNumSndBufs; 
		Graph *parent = unit->mParent; 
		if(localBufNum <= parent->localBufNum) { 
			buf = parent->mLocalSndBufs + localBufNum; 
		} else { 
			buf = world->mSndBufs; 
			if(unit->mWorld->mVerbosity > -1){ Print("KeyTrack error: Buffer number overrun: %i\n", ibufnum); } 
		} 
	} else { 
		buf = world->mSndBufs + ibufnum; 
	} 
    
	LOCK_SNDBUF(buf);
	int numbins = buf->samples - 2 >> 1;

	//assumed in this representation
	SCComplexBuf *p = ToComplexApx(buf);

	const float * data= buf->data;

	//memcpy(unit->m_FFTBuf, data, NOVER2);

	//to hold powers
	float * fftbuf= unit->m_FFTBuf;

	//get powers for bins
	//don't need to calculate past half Nyquist, because no indices involved of harmonics above 10000 Hz or so (see index data at top of file)
	for (int i=0; i<NOVER2; i+=2) {
		//i>>1 is i/2
		fftbuf[i>>1] = ((data[i] * data[i]) + (data[i+1] * data[i+1]));
	}


	float * chroma= unit->m_chroma;

	float sum;
	int indexbase, index;

	//experimental; added leaky integration on each note; also, only add to sum if harmonic, ie not a transient

	float * weights = unit->m_weights;
	int * bins = unit->m_bins;

	float chromaleak= ZIN0(2);

	//zero for new round (should add leaky integrator here!
	for (int i=0;i<12;++i)
		chroma[i] *= chromaleak;

	for (int i=0;i<60;++i) {
		int chromaindex = (i+9)%12; //starts at A1 up to G#6

		sum=0.0;

		indexbase= 12*i; //6 partials, 2 of each

		//transient sum, setting up last values too

		float phasesum=0.0;

		for(int j=0;j<12;++j) { //12 if 144 data points

			index=indexbase+j;

			//experimental transient detection code, not reliable
			//int binindex= unit->m_bins[index]-1;
			//SCPolar binnow= p->bin[binindex].ToPolarApx();
			//float phaseadvance= (binindex+1)*(TWOPI*0.5); //k * (512/44100) * (44100/1024) //convert bin number to frequency
			//float power= binnow.mag * binnow.mag; //(p->bin[binindex].real)*(p->bin[binindex].real) + (p->bin[binindex].imag)*(p->bin[binindex].imag); //(p->bin[binindex].mag);
			//power *= power;

			//int phaseindex= indexbase+j;
			//float phasenow= binnow.phase; //0.0; //(p->bin[binindex].phase);
			//float prevphase = fmod(unit->m_prevphase[index]+phaseadvance,TWOPI);
			//float a,b,tmp;
			//a=phasenow; b=prevphase;
			//b=phasenow; a=prevphase;

			//if(b<a) {b= b+TWOPI;}

			//float phasechange = sc_min(b-a,a+TWOPI-b); //more complicated, need mod 2pi and to know lower and upper
			//phasesum+= phasechange;
			//unit->m_prevphase[index]= phasenow;

			//((p->bin[index-1].mag) * (p->bin[index-1].mag))

			//printf("comparison %f %f \n",fftbuf[g_bins2[index]], power);
			//sum+= (unit->m_weights[index])* power;

			sum+= (weights[index])* (fftbuf[bins[index]]);
		}


		//transient test here too?
		//if(phasesum>(5*PI)){sum=0.0;}

		//if((i>5) && (i<15))
		//printf("test phasesum %f \n", phasesum);
		//unit->m_leaknote[i] = (0.8*unit->m_leaknote[i]) + sum;

		chroma[chromaindex]+= sum; //unit->m_leaknote[i]; //sum;
	}

	float* key = unit->m_key;

	//major
	for (int i=0;i<12;++i) {

		sum=0.0;
		for (int j=0;j<7;++j) {
			indexbase=g_major[j];

			index=(i+indexbase)%12;
			//sum+=(chroma[index]*g_kkmajor[indexbase]);

			sum+=(chroma[index]*g_diatonicmajor[indexbase]);

		}

		key[i]=sum; //10*log10(sum+1);
	}

	//minor
	for (int i=0;i<12;++i) {

		sum=0.0;
		for (int j=0;j<7;++j) {
			indexbase=g_minor[j];

			index=(i+indexbase)%12;
			//sum+=(chroma[index]*g_kkminor[indexbase]);

			sum+=(chroma[index]*g_diatonicminor[indexbase]);

		}

		key[12+i]=sum;
	}

	float keyleak= ZIN0(1); //fade parameter to 0.01 for histogram in seconds, convert to FFT frames

	//keyleak in seconds, convert to drop time in FFT hop frames (FRAMEPERIOD)
	keyleak= sc_max(0.001f,keyleak/unit->m_frameperiod); //FRAMEPERIOD;

	//now number of frames, actual leak param is decay exponent to reach 0.01 in x seconds, ie 0.01 = leakparam ** (x/ffthopsize)
	//0.01 is -40dB
	keyleak= pow(0.01f,(1.f/keyleak));

	float * histogram= unit->m_histogram;

	int bestkey=0;
	float bestscore=0.0;

	for (int i=0;i<24;++i) {
		histogram[i]= (keyleak*histogram[i])+key[i];

		if(histogram[i]>bestscore) {
			bestscore=histogram[i];
			bestkey=i;
		}

	//printf("%f ",histogram[i]);
	}

	//should find secondbest and only swap if win by a margin

	//printf(" best %d \n\n",bestkey);
	//what is winning currently? find max in histogram
	unit->m_currentKey=bestkey;

	//about 5 times per second
	//if((unit->m_triggerid) && ((unit->m_frame%2==0))) SendTrigger(&unit->mParent->mNode, unit->m_triggerid, bestkey);
}