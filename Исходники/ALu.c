ALUAPI ALvoid ALUAPIENTRY aluMixData(ALvoid *context,ALvoid *buffer,ALsizei size,ALenum format)
{
	ALfloat Pitch,DrySend[OUTPUTCHANNELS],WetSend[OUTPUTCHANNELS];
	static float DryBuffer[BUFFERSIZE][OUTPUTCHANNELS];
	static float WetBuffer[BUFFERSIZE][OUTPUTCHANNELS];
	ALuint BlockAlign,BytesPerSample,BufferSize;
	ALuint DataSize,DataPosInt,DataPosFrac;
	ALuint Channels,Bits,Frequency,ulExtraSamples;
	ALint Looping,increment,State;
	ALuint Buffer,fraction;
	ALCcontext *ALContext;
	ALuint SamplesToDo;
	ALsource *ALSource;
	ALbuffer *ALBuffer;
	ALfloat value;
	ALshort *Data;
	ALuint i,j,k;
	ALenum Error;
	ALbufferlistitem *BufferListItem;
	ALuint loop;
	__int64 DataSize64,DataPos64;
	unsigned int fpuState;

	if (context)
	{
		ALContext=((ALCcontext *)context);
		SuspendContext(ALContext);

	//Save FPU state
	fpuState=_controlfp(0,0);
	//Change FPU rounding mode
	_controlfp(_RC_CHOP,_MCW_RC);


		if ((buffer)&&(size))
		{
			//Figure output format variables
			switch (format)
			{
				case AL_FORMAT_MONO8:
					BlockAlign=1;
					BytesPerSample=1;
					break;
				case AL_FORMAT_STEREO8:
					BlockAlign=2;
					BytesPerSample=1;
					break;
				case AL_FORMAT_MONO16:
					BlockAlign=2;
					BytesPerSample=2;
					break;
				case AL_FORMAT_STEREO16:
				default:
					BlockAlign=4;
					BytesPerSample=2;
					break;
			}
			//Setup variables
			ALSource=ALContext->Source;
			SamplesToDo=((size/BlockAlign)<BUFFERSIZE?(size/BlockAlign):BUFFERSIZE);
			//Clear mixing buffer
			memset(DryBuffer,0,SamplesToDo*OUTPUTCHANNELS*sizeof(ALfloat));
			memset(WetBuffer,0,SamplesToDo*OUTPUTCHANNELS*sizeof(ALfloat));
			//Actual mixing loop
			for (i=0;i<ALContext->SourceCount;i++)
			{
				j=0;
				State = ALSource->state;
				while ((State==AL_PLAYING)&&(j<SamplesToDo))
				{
                    aluCalculateSourceParameters((ALuint)ALSource->source,ALContext->Frequency,ALContext->Channels,DrySend,WetSend,&Pitch);
					//Get buffer info
					if (Buffer = ALSource->ulBufferID)
					{
                        ALBuffer = (ALbuffer*)ALTHUNK_LOOKUPENTRY(Buffer);

						Data = ALBuffer->data;
						Bits = (((ALBuffer->format==AL_FORMAT_MONO8)||(ALBuffer->format==AL_FORMAT_STEREO8))?8:16);
						DataSize = ALBuffer->size;
						Channels = (((ALBuffer->format==AL_FORMAT_MONO8)||(ALBuffer->format==AL_FORMAT_MONO16))?1:2);
						Frequency = ALBuffer->frequency;

						Pitch=((Pitch*Frequency)/ALContext->Frequency);
						DataSize=(DataSize/(Bits*Channels/8));
						//Get source info
						DataPosInt=ALSource->position;
						DataPosFrac=ALSource->position_fraction;
						//Compute 18.14 fixed point step
						increment=aluF2L(Pitch*(1L<<FRACTIONBITS));
						if (increment > (MAX_PITCH<<FRACTIONBITS)) increment=(MAX_PITCH<<FRACTIONBITS);
						//Figure out how many samples we can mix.
						//Pitch must be <= 4 (the number below !)
						DataSize64=DataSize+MAX_PITCH;
						DataSize64<<=FRACTIONBITS;
						DataPos64=DataPosInt;
						DataPos64<<=FRACTIONBITS;
						DataPos64+=DataPosFrac;
						//FIX DEVIDE BY ZERO (NUMMER)
						if (increment == 0)
							increment = 1;
						BufferSize=(ALuint)((DataSize64-DataPos64)/increment);
						BufferListItem = ALSource->queue;
						for (loop = 0; loop < ALSource->BuffersAddedToDSBuffer; loop++)
							if (BufferListItem)
								BufferListItem = BufferListItem->next;
						if (BufferListItem) 
						{
							if (BufferListItem->next)
							{
								if (Channels==2)
								{
									if (((ALbuffer*)ALTHUNK_LOOKUPENTRY(BufferListItem->next->buffer))->data)
									{
										ulExtraSamples = min(((ALbuffer*)ALTHUNK_LOOKUPENTRY(BufferListItem->next->buffer))->size, 32);
										memcpy(&Data[DataSize*2], ((ALbuffer*)ALTHUNK_LOOKUPENTRY(BufferListItem->next->buffer))->data, ulExtraSamples);
									}
								}
								else
								{
									if (((ALbuffer*)ALTHUNK_LOOKUPENTRY(BufferListItem->next->buffer))->data)
									{
										ulExtraSamples = min(((ALbuffer*)ALTHUNK_LOOKUPENTRY(BufferListItem->next->buffer))->size, 16);
										memcpy(&Data[DataSize], ((ALbuffer*)ALTHUNK_LOOKUPENTRY(BufferListItem->next->buffer))->data, ulExtraSamples);
									}
								}
							}
							else if (ALSource->bLooping)
							{
								if (ALSource->queue->buffer)
								{										
									if (Channels==2)
									{
										if (((ALbuffer*)ALTHUNK_LOOKUPENTRY(ALSource->queue->buffer))->data)
										{
											ulExtraSamples = min(((ALbuffer*)ALTHUNK_LOOKUPENTRY(ALSource->queue->buffer))->size, 32);
											memcpy(&Data[DataSize*2], ((ALbuffer*)ALTHUNK_LOOKUPENTRY(ALSource->queue->buffer))->data, ulExtraSamples);
										}
									}
									else
									{
										if (((ALbuffer*)ALTHUNK_LOOKUPENTRY(ALSource->queue->buffer))->data)
										{
											ulExtraSamples = min(((ALbuffer*)ALTHUNK_LOOKUPENTRY(ALSource->queue->buffer))->size, 16);
											memcpy(&Data[DataSize], ((ALbuffer*)ALTHUNK_LOOKUPENTRY(ALSource->queue->buffer))->data, ulExtraSamples);
										}
									}
								}
							}
						}
						BufferSize=(BufferSize<(SamplesToDo-j)?BufferSize:(SamplesToDo-j));
						//Actual sample mixing loop
						Data+=DataPosInt*Channels;
						while (BufferSize--)
						{
							k=DataPosFrac>>FRACTIONBITS; fraction=DataPosFrac&FRACTIONMASK;
							if (Channels==1) 
							{
                                //First order interpolator
								value=(ALfloat)((ALshort)(((Data[k]*((1L<<FRACTIONBITS)-fraction))+(Data[k+1]*(fraction)))>>FRACTIONBITS));
								//Direct path final mix buffer and panning
								DryBuffer[j][0]+=value*DrySend[0];
								DryBuffer[j][1]+=value*DrySend[1];
								//Room path final mix buffer and panning
								WetBuffer[j][0]+=value*WetSend[0];
								WetBuffer[j][1]+=value*WetSend[1];
							}
							else
							{
                                //First order interpolator (left)
                                value=(ALfloat)((ALshort)(((Data[k*2  ]*((1L<<FRACTIONBITS)-fraction))+(Data[k*2+2]*(fraction)))>>FRACTIONBITS));
								//Direct path final mix buffer and panning (left)
								DryBuffer[j][0]+=value*DrySend[0];
								//Room path final mix buffer and panning (left)
								WetBuffer[j][0]+=value*WetSend[0];
                                //First order interpolator (right)
                                value=(ALfloat)((ALshort)(((Data[k*2+1]*((1L<<FRACTIONBITS)-fraction))+(Data[k*2+3]*(fraction)))>>FRACTIONBITS));
								//Direct path final mix buffer and panning (right)
								DryBuffer[j][1]+=value*DrySend[1];
								//Room path final mix buffer and panning (right)
								WetBuffer[j][1]+=value*WetSend[1];
							}
							DataPosFrac+=increment;
							j++;
						}
						DataPosInt+=(DataPosFrac>>FRACTIONBITS);
						DataPosFrac=(DataPosFrac&FRACTIONMASK);
						//Update source info
						ALSource->position=DataPosInt;
						ALSource->position_fraction=DataPosFrac;
					}
					//Handle looping sources
					if ((!Buffer)||(DataPosInt>=DataSize))
					{
						//queueing
						if (ALSource->queue)
						{
							Looping = ALSource->bLooping;
							if (ALSource->BuffersAddedToDSBuffer < (ALSource->BuffersInQueue-1))
							{
								BufferListItem = ALSource->queue;
								for (loop = 0; loop <= ALSource->BuffersAddedToDSBuffer; loop++)
								{
									if (BufferListItem)
									{
										if (!Looping)
											BufferListItem->bufferstate=PROCESSED;
										BufferListItem = BufferListItem->next;
									}
								}
								if (!Looping)
									ALSource->BuffersProcessed++;
								if (BufferListItem)
									ALSource->ulBufferID=BufferListItem->buffer;
								ALSource->position=DataPosInt-DataSize;
								ALSource->position_fraction=DataPosFrac;
								ALSource->BuffersAddedToDSBuffer++;
							}
							else
							{
								alSourceStop((ALuint)ALSource->source);
								if (Looping)
								{
                                    alSourceRewind((ALuint)ALSource->source);
                                    alSourcePlay((ALuint)ALSource->source);
									ALSource->position=DataPosInt-DataSize;
									ALSource->position_fraction=DataPosFrac;
								}
							}
						}
					}
					//Get source state
					State = ALSource->state;
				}
				ALSource=ALSource->next;
			}