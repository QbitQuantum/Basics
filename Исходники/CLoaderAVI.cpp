bool CLoaderAVI::loadFromFile(const CString& fileName)
{
    CApplication::getApp()->log(CString::fromUTF8("Chargement de la vidéo %1").arg(fileName));

#ifdef T_SYSTEM_WINDOWS
    AVIStreamGetFrameClose(m_pgf);

    // Suppression des flux
    if (m_video)
        AVIStreamRelease(m_video);

    if (m_audio)
    {
        //AVIStreamRelease(m_audio);
        Game::soundEngine->removeMusic(m_audio);
        delete m_audio;
        m_audio = nullptr;
    }

    Game::textureManager->deleteTexture(m_texture);
    AVIFileExit();
#endif

    m_time = 0;
    m_play = false;

    // Suppression de la précédente texture
    if (m_texture)
    {
        Game::textureManager->deleteTexture(m_texture);
    }

#ifdef T_SYSTEM_WINDOWS

    AVIFileInit();

    // Ouverture du flux vidéo
    if (AVIStreamOpenFromFile(&m_video, fileName.toCharArray(), streamtypeVIDEO, 0, OF_READ, nullptr))
    {
        CApplication::getApp()->log(CString::fromUTF8("AVIStreamOpenFromFile : impossible de lire le flux video."), ILogger::Error);
        return false;
    }

    // Infos sur le stream video
    AVISTREAMINFO psi;

    if (AVIStreamInfo(m_video, &psi, sizeof(psi)))
    {
        CApplication::getApp()->log("AVIStreamInfo donne une erreur", ILogger::Error);
        return false;
    }

    // Dimensions de la vidéo
    m_width = psi.rcFrame.right - psi.rcFrame.left;
    m_height = psi.rcFrame.bottom - psi.rcFrame.top;

    m_fileName = fileName;

    m_pixels.resize(4 * m_width * m_height);

    for (int i = 0; i < m_width * m_height; ++i)
    {
        m_pixels[4 * i + 0] = 0x00;
        m_pixels[4 * i + 1] = 0x00;
        m_pixels[4 * i + 2] = 0x00;
        m_pixels[4 * i + 3] = 0xFF;
    }

    // Création de la texture
    CImage img(m_width, m_height, reinterpret_cast<CColor *>(&m_pixels[0]));

    m_texture = Game::textureManager->loadTexture(m_fileName, img, CTextureManager::FilterNone);


    m_lastFrame = AVIStreamLength(m_video);

    if (m_lastFrame == 0)
    {
        return false;
    }

    m_frameTime = AVIStreamSampleToTime(m_video, m_lastFrame) / m_lastFrame;
    m_pgf = AVIStreamGetFrameOpen(m_video, nullptr);

    // On ne peut pas récupérer les frames
    if (m_pgf == nullptr)
    {
        CApplication::getApp()->log("AVIStreamGetFrameOpen retourne un pointeur nul", ILogger::Error);
        return false;
    }

    // Ouverture du flux audio
    m_audio = new CMusic();
    m_audio->loadFromVideo(m_fileName);

    if (m_loop)
    {
        m_audio->setLoop();
    }

    m_audio->play();
    Game::soundEngine->addMusic(m_audio);

#endif

    //m_play = true;
    return true;
}