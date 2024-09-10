bool CMusic::loadFromVideo(const CString& fileName)
{
    m_loaded = false;
    m_fileName = fileName;
    m_file = nullptr;
    m_fromVideo = true;

#ifdef T_SYSTEM_WINDOWS

    m_sampleCount = 0;
    ALenum error = alGetError();

    CApplication::getApp()->log(CString::fromUTF8("Chargement de la musique de la vidéo %1").arg(m_fileName));

    // Ouverture du flux audio
    if (AVIStreamOpenFromFile(&m_aviStream, m_fileName.toCharArray(), streamtypeAUDIO, 0, OF_READ, nullptr))
    {
        CApplication::getApp()->log("AVIStreamOpenFromFile : impossible de lire le flux audio", ILogger::Error);
        return false;
    }


    LONG buffer_size;
    AVIStreamRead(m_aviStream, AVIStreamStart(m_aviStream), (-1L), nullptr, 0, &buffer_size, nullptr);

    PBYTE tmp_format = new BYTE[buffer_size];
    AVIStreamReadFormat(m_aviStream, AVIStreamStart(m_aviStream), tmp_format, &buffer_size);
    LPWAVEFORMATEX wave_format = reinterpret_cast<LPWAVEFORMATEX>(tmp_format);

    // Lecture du nombre d'échantillons et du taux d'échantillonnage
    m_nbrSamples = AVIStreamLength(m_aviStream);
    m_sampleRate = wave_format->nSamplesPerSec;

    // Détermination du format en fonction du nombre de canaux
    switch (wave_format->nChannels)
    {
        case 1:
            m_format = AL_FORMAT_MONO16;
            break;

        case 2:
            m_format = AL_FORMAT_STEREO16;
            break;

        case 4:

            if (!CSoundEngine::isOALExtension("AL_EXT_MCFORMATS"))
            {
                return false;
            }

            m_format = alGetEnumValue("AL_FORMAT_QUAD16");
            break;

        case 6:

            if (!CSoundEngine::isOALExtension("AL_EXT_MCFORMATS"))
            {
                return false;
            }

            m_format = alGetEnumValue("AL_FORMAT_51CHN16");
            break;

        case 7:

            if (!CSoundEngine::isOALExtension("AL_EXT_MCFORMATS"))
            {
                return false;
            }

            m_format = alGetEnumValue("AL_FORMAT_61CHN16");
            break;

        case 8:

            if (!CSoundEngine::isOALExtension("AL_EXT_MCFORMATS"))
            {
                return false;
            }

            m_format = alGetEnumValue("AL_FORMAT_71CHN16");
            break;

        default:
            return false;
    }

    // Création des buffers OpenAL
    if (m_buffer[0] == 0 || m_buffer[1] == 0)
    {
        alGenBuffers(2, m_buffer);

        // Traitement des erreurs
        if ((error = alGetError()) != AL_NO_ERROR)
        {
            CSoundEngine::displayOpenALError(error, "alGenBuffers", __LINE__);
            return false;
        }

        // Les buffers sont invalides
        if (m_buffer[0] == 0 || m_buffer[1] == 0)
        {
            CApplication::getApp()->log("Les buffers audio sont invalides", ILogger::Error);
            return false;
        }
    }

    // Création d'une source
    if (m_source == 0)
    {
        alGenSources(1, &m_source);

        // Traitement des erreurs
        if ((error = alGetError()) != AL_NO_ERROR)
        {
            CSoundEngine::displayOpenALError(error, "alGenSources", __LINE__);
            return false;
        }

        // La source est invalide
        if (m_source == 0)
        {
            CApplication::getApp()->log("La source audio est invalide", ILogger::Error);
            return false;
        }
    }

    // On remplit les deux buffers
    readData(m_buffer[0], 44100);
    readData(m_buffer[1], 44100);

    // Remplissage avec les échantillons lus
    alSourceQueueBuffers(m_source, 2, m_buffer);

    // Traitement des erreurs
    if ((error = alGetError()) != AL_NO_ERROR)
    {
        CSoundEngine::displayOpenALError(error, "alSourceQueueBuffers", __LINE__);
        return false;
    }

    // Paramètres de la source
    alSourcei(m_source, AL_LOOPING, false);

    // Traitement des erreurs
    if ((error = alGetError()) != AL_NO_ERROR)
    {
        CSoundEngine::displayOpenALError(error, "alGetSourcei", __LINE__);
    }

    alSourcef(m_source, AL_PITCH, 1.0f);

    // Traitement des erreurs
    if ((error = alGetError()) != AL_NO_ERROR)
    {
        CSoundEngine::displayOpenALError(error, "alSourcef", __LINE__);
    }

    alSourcef(m_source, AL_GAIN, 1.0f);

    // Traitement des erreurs
    if ((error = alGetError() ) != AL_NO_ERROR)
    {
        CSoundEngine::displayOpenALError(error, "alSourcef", __LINE__);
    }

    alSource3f(m_source, AL_POSITION, 0.0f, 0.0f, 0.0f);

    // Traitement des erreurs
    if ((error = alGetError()) != AL_NO_ERROR)
    {
        CSoundEngine::displayOpenALError(error, "alSource3f", __LINE__);
    }

    m_loaded = true;

#endif

    return true;
}