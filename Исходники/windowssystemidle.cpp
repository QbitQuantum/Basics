/**   Platform specific routine for checking the idle state

    * @return bool
*/
bool WindowsSystemIdle::CheckIdle(void)
{
    LASTINPUTINFO inputInfo  = {0};
    DWORD         dwTicksNow = 0;

    inputInfo.cbSize = sizeof(inputInfo);

    if (GetLastInputInfo(&inputInfo) == FALSE)
    {
        return false;
    }

    dwTicksNow = GetTickCount();

    inputInfo.dwTime /= 1000;
    dwTicksNow /= 1000;

    dwTicksNow -= inputInfo.dwTime;

    int nInterval = 0;

    m_pConfiguration->getInterval(nInterval);

    return (dwTicksNow >= nInterval);
}