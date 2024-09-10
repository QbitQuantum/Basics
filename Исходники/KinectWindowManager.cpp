/// <summary>
/// Show all the kinect windows
/// </summary>
void KinectWindowManager::ShowAllKinectWindows()
{
    for (auto iter = m_sensorMap.begin(); iter != m_sensorMap.end(); ++iter)
    {
        if (nullptr != iter->second.KinectWindow)
        {
            PostMessageW(iter->second.KinectWindow->GetWindow(), WM_SHOWKINECTWINDOW, 1, 0);
        }
    }
}