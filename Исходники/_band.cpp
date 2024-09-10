void cheReactionUpdate() {
	framesSinceLastReset++;

	int i;

	if( Band_signalOmega != oldOmega ) {
		cheReactionReset();
	}

	avgBuf[avgBufCount++] = (float)outputHits;
	if( avgBufCount == avgBufSize ) {
		float sum = 0.f;
		for( i=0; i<avgBufCount; i++ ) {
			sum += avgBuf[i];
		}
		fftBuf[fftBufCount] = sum / (float)avgBufCount;
		fftBufCount++;
		avgBufCount = 0;
		if( fftBufCount == fftBufSize ) {
			FFT fft( fftBuf, fftBufSize );
			fft.fft();
			float *p = fft.computePowerSpectrum();
			for( i=0; i<fftBufCount/2-1; i++ ) {
				cumPowerSpectrum[i] += p[i];
				cumPowerSpectrumLog[i] = logf( 1.f + cumPowerSpectrum[i] );
			}
			fftBufCount = 0;
			cumPowerSpectrumCount++;
			FILE *file = fopen( ZTmpStr("/transfer/fft/fft-diff-%d.txt",cumPowerSpectrumCount), "wt" );
			for( i=1; i<100; i++ ) {
				fprintf( file, "%f\n", cumPowerSpectrum[i] / (float)cumPowerSpectrumCount );
			}
			fclose( file );
		}
	}

	if( !(simulationFrameNumber % 100 ) ) {
		spatialHistogramCount++;
		for( int x=0; x<DIMX; x++ ) {
			for( int y=0; y<DIMY; y++ ) {
				Part *p = partAt( IVec2(x,y) );
				if( p && p->type == TYPE_CHEYP ) {
					spatialHistogram[x]++;
				}
			}
		}
	}

	outputHistory.setAvgWindow( Band_plotWindowRadius );
	outputHistory.add( (float)outputHits );

	// COMPUTE input signal
	signal = Band_signal;
	if( Band_useSinSignal ) {
		signal = (float)( Band_signalTop * 0.5*( 1.0+sin( Band_signalOmega * (double)simulationFrameNumber ) ) );
	}
	inputHistory.add( signal );

	// SETUP for next computation
	outputHits = 0;
}