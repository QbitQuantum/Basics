bool CCLuaJavaBridge::CallInfo::getMethodInfo(void)
{
	m_methodID = 0;
    m_env = 0;

    JavaVM* jvm = cocos2d::JniHelper::getJavaVM();
    jint ret = jvm->GetEnv((void**)&m_env, JNI_VERSION_1_4);
    switch (ret) {
        case JNI_OK:
            break;

        case JNI_EDETACHED :
            if (jvm->AttachCurrentThread(&m_env, NULL) < 0)
            {
                LOGD("%s", "Failed to get the environment using AttachCurrentThread()");
                m_error = LUAJ_ERR_VM_THREAD_DETACHED;
                return false;
            }
            break;

        case JNI_EVERSION :
        default :
            LOGD("%s", "Failed to get the environment using GetEnv()");
            m_error = LUAJ_ERR_VM_FAILURE;
            return false;
    }

    m_classID = m_env->FindClass(m_className.c_str());
    m_methodID = m_env->GetStaticMethodID(m_classID, m_methodName.c_str(), m_methodSig.c_str());
    if (!m_methodID)
    {
    	m_env->ExceptionClear();
        LOGD("Failed to find method id of %s.%s %s",
        		m_className.c_str(),
        		m_methodName.c_str(),
        		m_methodSig.c_str());
        m_error = LUAJ_ERR_METHOD_NOT_FOUND;
        return false;
    }

    return true;
}