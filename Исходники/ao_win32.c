// open & setup audio device
// return: 1=success 0=fail
static int init(int rate,int channels,int format,int flags)
{
	WAVEFORMATEXTENSIBLE wformat;      
	DWORD totalBufferSize = (BUFFER_SIZE + sizeof(WAVEHDR)) * BUFFER_COUNT;
	MMRESULT result;
	unsigned char* buffer;
	int i;
   
	switch(format){
		case AF_FORMAT_AC3:
		case AF_FORMAT_S24_LE:
		case AF_FORMAT_S16_LE:
		case AF_FORMAT_S8:
			break;
		default:
			mp_msg(MSGT_AO, MSGL_V,"ao_win32: format %s not supported defaulting to Signed 16-bit Little-Endian\n",af_fmt2str_short(format));
			format=AF_FORMAT_S16_LE;
	}   

	// FIXME multichannel mode is buggy
	if(channels > 2)
		channels = 2;
   
	//fill global ao_data 
	ao_data.channels=channels;
	ao_data.samplerate=rate;
	ao_data.format=format;
	ao_data.bps=channels*rate;
	if(format != AF_FORMAT_U8 && format != AF_FORMAT_S8)
	  ao_data.bps*=2;
	if(ao_data.buffersize==-1)
	{
		ao_data.buffersize=af_fmt2bits(format)/8;
        ao_data.buffersize*= channels;
		ao_data.buffersize*= SAMPLESIZE;
	}
	mp_msg(MSGT_AO, MSGL_V,"ao_win32: Samplerate:%iHz Channels:%i Format:%s\n",rate, channels, af_fmt2str_short(format));
    mp_msg(MSGT_AO, MSGL_V,"ao_win32: Buffersize:%d\n",ao_data.buffersize);
	
	//fill waveformatex
    ZeroMemory( &wformat, sizeof(WAVEFORMATEXTENSIBLE));
    wformat.Format.cbSize          = (channels>2)?sizeof(WAVEFORMATEXTENSIBLE)-sizeof(WAVEFORMATEX):0;
    wformat.Format.nChannels       = channels;                
    wformat.Format.nSamplesPerSec  = rate;            
    if(format == AF_FORMAT_AC3)
    {
        wformat.Format.wFormatTag      = WAVE_FORMAT_DOLBY_AC3_SPDIF;
        wformat.Format.wBitsPerSample  = 16;
        wformat.Format.nBlockAlign     = 4;
    }
    else 
    {
        wformat.Format.wFormatTag      = (channels>2)?WAVE_FORMAT_EXTENSIBLE:WAVE_FORMAT_PCM;
        wformat.Format.wBitsPerSample  = af_fmt2bits(format); 
        wformat.Format.nBlockAlign     = wformat.Format.nChannels * (wformat.Format.wBitsPerSample >> 3);
    }
	if(channels>2)
	{
        wformat.dwChannelMask = channel_mask[channels-3];
        wformat.SubFormat = KSDATAFORMAT_SUBTYPE_PCM;
	    wformat.Samples.wValidBitsPerSample=af_fmt2bits(format);
    }
  
    wformat.Format.nAvgBytesPerSec = wformat.Format.nSamplesPerSec * wformat.Format.nBlockAlign;
 	
    //open sound device
    //WAVE_MAPPER always points to the default wave device on the system
    result = waveOutOpen(&hWaveOut,WAVE_MAPPER,(WAVEFORMATEX*)&wformat,(DWORD_PTR)waveOutProc,0,CALLBACK_FUNCTION);
	if(result == WAVERR_BADFORMAT)
	{
		mp_msg(MSGT_AO, MSGL_ERR,"ao_win32: format not supported switching to default\n");
        ao_data.channels = wformat.Format.nChannels = 2;
	    ao_data.samplerate = wformat.Format.nSamplesPerSec = 44100;
	    ao_data.format = AF_FORMAT_S16_LE;
		ao_data.bps=ao_data.channels * ao_data.samplerate*2;
	    wformat.Format.wBitsPerSample=16;
        wformat.Format.wFormatTag=WAVE_FORMAT_PCM;
		wformat.Format.nBlockAlign     = wformat.Format.nChannels * (wformat.Format.wBitsPerSample >> 3);
        wformat.Format.nAvgBytesPerSec = wformat.Format.nSamplesPerSec * wformat.Format.nBlockAlign;
		ao_data.buffersize=(wformat.Format.wBitsPerSample>>3)*wformat.Format.nChannels*SAMPLESIZE;
        result = waveOutOpen(&hWaveOut,WAVE_MAPPER,(WAVEFORMATEX*)&wformat,(DWORD_PTR)waveOutProc,0,CALLBACK_FUNCTION);
	}