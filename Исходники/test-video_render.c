int main(int argc, char** argv) {

	OMX_PORT_PARAM_TYPE param;
	OMX_PARAM_PORTDEFINITIONTYPE sPortDef;
	OMX_AUDIO_PORTDEFINITIONTYPE sAudioPortDef;
	OMX_AUDIO_PARAM_PORTFORMATTYPE sAudioPortFormat;
	OMX_AUDIO_PARAM_PCMMODETYPE sPCMMode;
	OMX_BUFFERHEADERTYPE **inBuffers[2];

	char *componentName = "OMX.broadcom.video_render";
	unsigned char name[OMX_MAX_STRINGNAME_SIZE];
	OMX_UUIDTYPE uid;
	int startPortNumber;
	int nPorts;
	int i, n;

	bcm_host_init();

	fprintf(stderr, "Thread id is %p\n", pthread_self());
	if(argc < 2){
		display_help(argv);
		exit(1);
	}

	fd = open(argv[1], O_RDONLY);
	if(fd < 0){
		perror("Error opening input file\n");
		exit(1);
	}
	filesize = getFileSize(fd);


	err = OMX_Init();
	if(err != OMX_ErrorNone) {
		fprintf(stderr, "OMX_Init() failed\n", 0);
		exit(1);
	}
	/** Ask the core for a handle to the audio render component
	 */
	err = OMX_GetHandle(&handle, componentName, NULL /*app private data */, &callbacks);
	if(err != OMX_ErrorNone) {
		fprintf(stderr, "OMX_GetHandle failed\n", 0);
		exit(1);
	}
	err = OMX_GetComponentVersion(handle, name, &compVersion, &specVersion, &uid);
	if(err != OMX_ErrorNone) {
		fprintf(stderr, "OMX_GetComponentVersion failed\n", 0);
		exit(1);
	}

	/** disable other ports */
	disablePort(OMX_IndexParamOtherInit);

	/** Get audio port information */
	setHeader(&param, sizeof(OMX_PORT_PARAM_TYPE));
	err = OMX_GetParameter(handle, OMX_IndexParamVideoInit, &param);
	if(err != OMX_ErrorNone){
		fprintf(stderr, "Error in getting OMX_PORT_PARAM_TYPE parameter\n", 0);
		exit(1);
	}
	startPortNumber = ((OMX_PORT_PARAM_TYPE)param).nStartPortNumber;
	nPorts = ((OMX_PORT_PARAM_TYPE)param).nPorts;
	if (nPorts > 2) {
		fprintf(stderr, "Image device has more than one port\n");
		exit(1);
	}

	for (i = 0; i < nPorts; i++) {
		/* Get and check port information */
		setHeader(&sPortDef, sizeof(OMX_PARAM_PORTDEFINITIONTYPE));
		sPortDef.nPortIndex = startPortNumber + i;
		err = OMX_GetParameter(handle, OMX_IndexParamPortDefinition, &sPortDef);

		if(err != OMX_ErrorNone) {
			fprintf(stderr, "Error in getting OMX_PORT_DEFINITION_TYPE parameter\n", 0);
			exit(1);
		}
		if (sPortDef.eDomain != OMX_PortDomainVideo) {
			fprintf(stderr, "Port %d is not a video port\n", sPortDef.nPortIndex);
			exit(1);
		}

		if (sPortDef.eDir == OMX_DirInput)
			fprintf(stdout, "Port %d is an input port\n", sPortDef.nPortIndex);
		else
			fprintf(stdout, "Port %d is an output port\n", sPortDef.nPortIndex);

		if (sPortDef.format.video.eColorFormat == OMX_COLOR_FormatYUV420PackedPlanar)
			fprintf(stderr, "Port color Format is YUV420PackedPlanar\n");
		else
			fprintf(stderr, "Port has unknown color format\n");

		/* Set Image Format -- FIXME: hardcoded */
		sPortDef.format.video.nFrameWidth = 1920;
		sPortDef.format.video.nFrameHeight = 1080;
		sPortDef.format.video.nStride =
			ALIGN(sPortDef.format.video.nFrameWidth, 32);
		sPortDef.format.image.nSliceHeight =
			ALIGN(sPortDef.format.video.nFrameHeight, 16);
		sPortDef.nBufferSize = sPortDef.format.image.nStride *
			sPortDef.format.image.nSliceHeight * 3 / 2;

		/* Create minimum number of buffers for the port */
		nBuffers = sPortDef.nBufferCountActual = sPortDef.nBufferCountMin;
		fprintf(stderr, "Number of bufers is %d\n", nBuffers);
		err = OMX_SetParameter(handle, OMX_IndexParamPortDefinition, &sPortDef);
		if(err != OMX_ErrorNone){
			fprintf(stderr, "Error in setting OMX_PORT_PARAM_TYPE parameter\n", 0);
			exit(1);
		}
		if (sPortDef.bEnabled) {
			fprintf(stderr, "Port %d is enabled\n", sPortDef.nPortIndex);
		} else {
			fprintf(stderr, "Port %d is not enabled\n", sPortDef.nPortIndex);
		}
	}

	/* call to put state into idle before allocating buffers */
	printf("OMX_CommandStateSet, OMX_StateIdle\n");
	err = OMX_SendCommand(handle, OMX_CommandStateSet, OMX_StateIdle, NULL);
	if (err != OMX_ErrorNone) {
		fprintf(stderr, "Error on setting state to idle\n");
		exit(1);
	}

	for (i = 0; i < nPorts; i++) {
		/* Get and check port information */
		setHeader(&sPortDef, sizeof(OMX_PARAM_PORTDEFINITIONTYPE));
		sPortDef.nPortIndex = startPortNumber + i;
		err = OMX_GetParameter(handle, OMX_IndexParamPortDefinition, &sPortDef);

		if(err != OMX_ErrorNone) {
			fprintf(stderr, "Error in getting OMX_PORT_DEFINITION_TYPE parameter\n", 0);
			exit(1);
		}

		if (!sPortDef.bEnabled) {
			printf("OMX_CommandPortEnable, %d\n", startPortNumber);
			err = OMX_SendCommand(handle, OMX_CommandPortEnable, startPortNumber, NULL);
			if (err != OMX_ErrorNone) {
				fprintf(stderr, "Error on setting port to enabled\n");
				exit(1);
			}
		}
	}

	/* Configure buffers for the port */
	for (i = 0; i < nPorts; i++) {
		setHeader(&sPortDef, sizeof(OMX_PARAM_PORTDEFINITIONTYPE));
		sPortDef.nPortIndex = startPortNumber + i;
		err = OMX_GetParameter(handle, OMX_IndexParamPortDefinition, &sPortDef);

		nBufferSize = sPortDef.nBufferSize;
		fprintf(stderr, "Port %d has %d buffers of size %d\n", sPortDef.nPortIndex,
				nBuffers, nBufferSize);

		inBuffers[i] = malloc(nBuffers * sizeof(OMX_BUFFERHEADERTYPE *));
		if (inBuffers[i] == NULL) {
			fprintf(stderr, "Can't allocate buffers\n");
			exit(1);
		}

		for (n = 0; n < nBuffers; n++) {
			err = OMX_AllocateBuffer(handle, inBuffers[i] + n, startPortNumber + i, NULL,
						 nBufferSize);
			if (err != OMX_ErrorNone) {
				fprintf(stderr, "Error on AllocateBuffer in 1%i\n", err);
				exit(1);
			}
		}
	}

	printf("Transition to Idle\n");
	/* Make sure we've reached Idle state */
	waitFor(OMX_StateIdle);

	printf("Transition to Executing\n");
	/* Now try to switch to Executing state */
	err = OMX_SendCommand(handle, OMX_CommandStateSet, OMX_StateExecuting, NULL);
	if(err != OMX_ErrorNone){
		exit(1);
	}

	/* One buffer is the minimum for Broadcom component, so use that */
	pEmptyBuffer = inBuffers[0][0];
	emptyState = 1;
	/* Fill and empty buffer */
	for (;;) {
		int data_read = read(fd, pEmptyBuffer->pBuffer, nBufferSize);
		pEmptyBuffer->nFilledLen = data_read;
		pEmptyBuffer->nOffset = 0;
		filesize -= data_read;
		if (filesize <= 0) {
			pEmptyBuffer->nFlags = OMX_BUFFERFLAG_EOS;
		}
		fprintf(stderr, "Emptying again buffer %p %d bytes, %d to go\n", pEmptyBuffer, data_read, filesize);
		err = OMX_EmptyThisBuffer(handle, pEmptyBuffer);
		waitForEmpty();
		fprintf(stderr, "Waited for empty\n");
		if (bEOS) {
			fprintf(stderr, "Exiting loop\n");
			break;
		}
	}
	fprintf(stderr, "Buffers emptied\n");
	exit(0);
}