void CoreAudioOutDriver::open(device_id_t device,
			      int sample_rate,
			      sample_format form,
			      int channels,
			      int num_samples,
			      int num_periods)
{
  if (this->is_open())
    throw std::logic_error("Device already open");


  if (form != SF_16LE)
    throw std::invalid_argument("Unknown sample format");

  m_impl->m_logger = logger;

  AudioDeviceID devid = GetDeviceID(logger, device);

  if (devid == kAudioDeviceUnknown)
    throw std::invalid_argument("Unknown device id");

  OSStatus err;
  const bool isInput = false;
  UInt32 propsize;
  
  AudioValueRange bufferRange;

  // check that the desired value is within the allowed range
  propsize = sizeof(bufferRange);
  err = AudioDeviceGetProperty(devid, 0, false,
			       kAudioDevicePropertyBufferFrameSizeRange,
			       &propsize,
			       &bufferRange);


  if (err != kAudioHardwareNoError)
    {
      throw std::runtime_error("Could not get buffer range");
    }

  propsize = sizeof(UInt32);
  UInt32 frames = my_min<int>(my_max<int>(num_samples,
					  (int) bufferRange.mMinimum),
			      (int) bufferRange.mMaximum);

  err = AudioDeviceSetProperty(devid, NULL, 0, isInput,
			       kAudioDevicePropertyBufferFrameSize,
			       propsize, &frames);
    
  if (err != kAudioHardwareNoError)
    {
      throw std::runtime_error("Could not set buffer size");
    }


  propsize = sizeof(frames);
  err = AudioDeviceGetProperty(devid, 0, isInput,
			       kAudioDevicePropertyBufferFrameSize,
			       &propsize, &frames);
    
  if (err != kAudioHardwareNoError)
    {
      throw std::runtime_error("Could not read buffer size");
    }

  char bbc[256] = {0};
  sprintf(bbc, "Buffer size in frames: %i", frames);
  logger(2, bbc);

  Float64 sampleRate = sample_rate;
  propsize = sizeof(sampleRate);
  err = AudioDeviceSetProperty(devid, NULL, 0, isInput,
			       kAudioDevicePropertyNominalSampleRate,
			       propsize, &sampleRate);
    
  if (err != kAudioHardwareNoError)
    {
      throw std::runtime_error("Could not set sample rate");
    }

  print_info(devid, logger, isInput);

  propsize = sizeof(m_impl->m_format);
  err = AudioDeviceGetProperty(devid, 0, isInput,
			       kAudioDevicePropertyStreamFormat,
			       &propsize,
			       &m_impl->m_format);

  if (err != kAudioHardwareNoError)
    {
      throw std::runtime_error("Could not get audio format");
    }


  // Desired format
  memset(&m_impl->m_input_format, 0, sizeof(m_impl->m_input_format));
  

  // set channels, format to SF_16LE

  m_impl->m_input_format.mSampleRate       = sample_rate;
  m_impl->m_input_format.mFormatID         = kAudioFormatLinearPCM;
  m_impl->m_input_format.mFormatFlags
         = kLinearPCMFormatFlagIsSignedInteger |
           kLinearPCMFormatFlagIsPacked;

  m_impl->m_input_format.mBytesPerPacket   = 2*channels;
  m_impl->m_input_format.mFramesPerPacket  = 1;
  m_impl->m_input_format.mBytesPerFrame    = m_impl->m_input_format.mBytesPerPacket;
  m_impl->m_input_format.mChannelsPerFrame = channels;
  m_impl->m_input_format.mBitsPerChannel   = 16;

#define USE_COMPLEX_AUDIO_CONVERTER
  //#define USE_SIMPLE_AUDIO_CONVERTER

#if defined(USE_SIMPLE_AUDIO_CONVERTER)
  m_impl->m_converter = new SimpleConverter(m_impl->m_input_format,
					    m_impl->m_format);
#elif defined (USE_COMPLEX_AUDIO_CONVERTER)
  m_impl->m_converter = new ComplexConverter(m_impl->m_input_format,
					     m_impl->m_format);
#else
    // TODO: this works only for 2 channels float to 1 channel mono 16LE!
  m_impl->m_converter = new Mono16LEPCMToStereoFloat;
#endif

  print_format pf1(logger, "Device Format\n");
  pf1(m_impl->m_format);

  print_format pf2(logger, "Input Format\n");
  pf2(m_impl->m_input_format);

  // Set the buffer latency (audio output is only started after
  // the buffer contains m_min_buffer samples).
  m_impl->m_min_buffer = num_samples*num_periods;
  m_impl->m_ID = devid;

  AudioDeviceAddIOProc(devid, Impl::OutputIOProc, m_impl.get());
}