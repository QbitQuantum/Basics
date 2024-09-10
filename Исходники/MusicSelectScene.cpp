// On selecting the your music menu item, start the file explore activity for the user to choose a song
//   on their SD card
//
// sender [in] - the object that sent the selected event?
void MusicSelect::HandleYourMusicPressed(CCObject* sender)
{
    jclass tmpClass;            // Prevent a stale local ref bug
    jobject tmpObject;          // Prevent a stale local ref bug

	SimpleAudioEngine::sharedEngine()->playEffect("SFX/select.wav");

	// if we haven't before, retrieve all the JNI data to be able to call java methods
    if (!m_haveJniData)
    {
        JavaVM* jvm = cocos2d::JniHelper::getJavaVM();
        if (NULL == jvm)
            CCLog("Failed to get the JavaVM");

        jint ret = jvm->GetEnv((void**)&m_env, JNI_VERSION_1_4);
        if (ret != JNI_OK)
            CCLog("Failed to get then JNIEnv");

        tmpClass = m_env->FindClass("org/cocos2dx/extbeatanni/ExtremeBeatAnnihilation");
        if (!tmpClass)
            CCLog("Failed to find class ExtremeBeatAnnihilation");
        m_extBeatAnniClass = (jclass)m_env->NewGlobalRef(tmpClass);

        jmethodID getObjectMethod = m_env->GetStaticMethodID(m_extBeatAnniClass, "getObject", "()Ljava/lang/Object;");
        if(!getObjectMethod)
            CCLog("Failed to find method getObject");

        tmpObject = m_env->CallStaticObjectMethod(m_extBeatAnniClass, getObjectMethod);
        if(!tmpObject)
            CCLog("Failed to get the current instance of the running activity");
        m_extBeatAnniInstance = (jobject)m_env->NewGlobalRef(tmpObject);

        m_startupFileExploreMethod = m_env->GetMethodID(m_extBeatAnniClass, "startupFileExplore", "()V");
        if (!m_startupFileExploreMethod)
            CCLog("Failed to find method startupFileExplore");

        m_getSelectedSongMethod = m_env->GetMethodID(m_extBeatAnniClass, "getSelectedSong", "()Ljava/lang/String;");
        if (!m_getSelectedSongMethod)
            CCLog("Failed to find method getSelectedSong");

        m_haveJniData = true;
    }

    // call the java method within the ExtremeBeatAnnihilation activity that will start up file explore
    m_env->CallNonvirtualVoidMethod(m_extBeatAnniInstance, m_extBeatAnniClass, m_startupFileExploreMethod);

    m_choseUserMusic = true;

    // if song wasn't selected previously, set up the scene to start the game
    if (!m_songSelected)
    {
        m_header->setString("Song selected! Press Play or choose another!");
        m_itemPlay->setVisible(true);
        m_itemPlay->setEnabled(true);
        m_songSelected = true;
    }
}