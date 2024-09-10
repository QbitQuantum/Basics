AndroidSurfaceTexture::~AndroidSurfaceTexture()
{
    if (QtAndroidPrivate::androidSdkVersion() > 13 && m_surfaceView.isValid())
        m_surfaceView.callMethod<void>("release");

    if (m_surfaceTexture.isValid()) {
        release();
        g_objectMap.remove(m_texID);
    }
}