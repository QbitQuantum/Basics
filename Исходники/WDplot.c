unsigned int __stdcall PlotThread(void* data)
{
	uint32_t retVal= 0;
	WDPlot_t *plotData= (WDPlot_t *)data;
	int i, s=0, ntr, comma=0, c, npts=0, WaitTime;
	FILE *fplot;

	SetPlotOptions(plotData);
	fplot = fopen(PLOT_DATA_FILE, "w");
	if (fplot == NULL) {
		retVal= -1;
		goto exitPoint;
	}
	ntr = plotData->NumTraces;
	while(ntr > 0) {
		fprintf(fplot, "%d\t", s);
		for(i=0; i<plotData->NumTraces; i++) {
			if (s < plotData->TraceSize[i]) {
				fprintf(fplot, "%d\t", plotData->TraceData[i][s]);
				npts++;
			}
			if (plotData->TraceSize[i] == (s-1))
				ntr--;
		}
		s++;
		fprintf(fplot, "\n");
	}
	fclose(fplot);

	/* str contains the plot command for gnuplot */
	fprintf(gnuplot, "plot ");
	c = 2; /* first column of data */
	for(i=0; i<plotData->NumTraces; i++) {
		if (comma)
			fprintf(gnuplot, ", ");
		fprintf(gnuplot, "'%s' using ($1*%f):($%d*%f) title 'ch%d' with lines %d", PLOT_DATA_FILE, plotData->Xscale, c++, plotData->Yscale, i, i+1);
		comma = 1;
	}
	fprintf(gnuplot, "\n"); 
	fflush(gnuplot);

	/* wait for gnuplot to finish */
	// TODO verificare documentazione gnuPlot per vedere se c'è modo di capire quando gnuPlot ha finito
	WaitTime = npts/100;
	if (WaitTime < 100)
		WaitTime = 100;
	Sleep(WaitTime);

exitPoint:
	// Free the traces storage
	for(i=0; i<plotData->NumTraces; i++)
		free( plotData->TraceData[i]);
	plotData->NumTraces= 0;
	_endthreadex( retVal );
    return retVal;
}