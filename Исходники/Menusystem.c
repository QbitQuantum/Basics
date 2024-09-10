static void navigateElevationMenu(int inputResult)
{
        switch (inputResult) {
        case 1:
            // Go to elevation angle
            setMenu(ElGoto);
            break;
        case 2:
            // Set elevation minimum
            setMenu(ElMin);
            break;
        case 3:
            // Set elevation maximum
            setMenu(ElMax);
            break;
        case 4:
            if (m_userMode == FACTORY) {
                // Calibrate the elevation servo
            } else {
                m_currentMenu.returnToPrevious();
                // Go back one level
            }
            break;
        case 5:
            if (m_userMode == FACTORY) {
                // Calibrate the elevation servo
                break;
            }
            // If not in factory mode, this is an error;
        default:
            if (m_userMode == FACTORY) errOutOfRange(1, 5);
            else errOutOfRange(1, 4);
            break;
    }
}