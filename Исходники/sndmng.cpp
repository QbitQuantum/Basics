void CSoundManager::Streaming()
{
	// revisa si hay bloques pendientes que se terminaron: 
	for(int i=0;i<cant_bloques;++i)
	{
		if(waveOutUnprepareHeader(hWaveOut, bloques_pendientes[i], sizeof(WAVEHDR))
			!=WAVERR_STILLPLAYING)
		{
			// ya termino de procesarse, (o dio un error, sea como sea: )
			// libero la memoria
			delete bloques_pendientes[i]->lpData;
			delete bloques_pendientes[i];
			// marco el bloque para borrar
			bloques_pendientes[i] = NULL;
		}
	}

	int ant_cant = cant_bloques;
	// pack de bloques
	cant_bloques = 0;
	for(i=0;i<ant_cant;++i)
		if(bloques_pendientes[i]!=NULL)
			bloques_pendientes[cant_bloques++] = bloques_pendientes[i];
}