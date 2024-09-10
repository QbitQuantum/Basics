void IMUThread::finishThread()
{
    if (m_timer != -1)
        killTimer(m_timer);

    m_timer = -1;

    if (m_imu != NULL)
        delete m_imu;

    m_imu = NULL;

    if (m_pressure != NULL)
        delete m_pressure;

    m_pressure = NULL;

    delete m_settings;
}