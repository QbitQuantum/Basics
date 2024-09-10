bool JavascriptJavaBridge::CallInfo::getMethodInfo(void)
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
                m_error = JSJ_ERR_VM_THREAD_DETACHED;
                return false;
            }
            break;

        case JNI_EVERSION :
        default :
            LOGD("%s", "Failed to get the environment using GetEnv()");
            m_error = JSJ_ERR_VM_FAILURE;
            return false;
    }
    jstring _jstrClassName = m_env->NewStringUTF(m_className.c_str());
    m_classID = (jclass) m_env->CallObjectMethod(cocos2d::JniHelper::classloader,
                                                   cocos2d::JniHelper::loadclassMethod_methodID,
                                                   _jstrClassName);

    if (NULL == m_classID) {
        LOGD("Classloader failed to find class of %s", m_className.c_str());
    }

    m_env->DeleteLocalRef(_jstrClassName);
    m_methodID = m_env->GetStaticMethodID(m_classID, m_methodName.c_str(), m_methodSig.c_str());
    if (!m_methodID)
    {
        m_env->ExceptionClear();
        LOGD("Failed to find method id of %s.%s %s",
                m_className.c_str(),
                m_methodName.c_str(),
                m_methodSig.c_str());
        m_error = JSJ_ERR_METHOD_NOT_FOUND;
        return false;
    }

    return true;
}