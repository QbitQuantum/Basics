MicrophoneRecorder::MicrophoneRecorder(int frequency, int channels, FMOD_SOUND_FORMAT format)
    : m_fmodsnd(nullptr)
    , m_fmodsys(nullptr)
    , m_dataLength(0)
    , m_byteSize(0)
    , m_frequency(frequency)
    , m_channels(channels)
{
    switch (format)
    {
        case FMOD_SOUND_FORMAT_PCM8: m_byteSize = 1; break;
        case FMOD_SOUND_FORMAT_PCM16: m_byteSize = 2; break;
        case FMOD_SOUND_FORMAT_PCM24: m_byteSize = 3; break;
        case FMOD_SOUND_FORMAT_PCM32: m_byteSize = 4; break;
        case FMOD_SOUND_FORMAT_PCMFLOAT: m_byteSize = 4; break;
    }

    CHECK(m_byteSize > 0);

	FMOD::System * fmodSys = SoundMngr::Get()->GetSys();

	FMOD_CREATESOUNDEXINFO exinfo;
	memset(&exinfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
	exinfo.cbsize           = sizeof(FMOD_CREATESOUNDEXINFO);
	exinfo.numchannels      = channels;
	exinfo.format           = format;
	exinfo.defaultfrequency = frequency;
	exinfo.length           = exinfo.defaultfrequency * m_byteSize * exinfo.numchannels * 2;

	unsigned int flags = FMOD_SOFTWARE | FMOD_2D | FMOD_OPENUSER;
	FMOD_ERRCHECK(fmodSys->createSound(0, flags, &exinfo, &m_fmodsnd));

	m_fmodsys = fmodSys;

    m_data.resize(channels);
}