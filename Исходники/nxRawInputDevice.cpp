bool nxRawInputDevice::Enumerate(std::vector<nxRawInputDevice>&vcRawDevices)
{
    nxRawInputDevice objDevice;
    UINT uNumDev;
    vcRawDevices.clear();
    try
    {
        if (GetRawInputDeviceList(NULL,&uNumDev,sizeof(RAWINPUTDEVICELIST)) != 0)
            nxThrow("Error retrieving number of raw input devices.");
        std::vector<RAWINPUTDEVICELIST> rdl(uNumDev);
        if (uNumDev && (GetRawInputDeviceList(&rdl[0],&uNumDev,sizeof(RAWINPUTDEVICELIST)) == (UINT)-1))
            nxThrow("Error retrieving list of raw input devices.");

        for (std::vector<RAWINPUTDEVICELIST>::iterator it=rdl.begin();it!=rdl.end();++it)
        {

            objDevice.hDevice = it->hDevice;
            objDevice.dwType = it->dwType;


            if (objDevice.GetInformation())
				vcRawDevices.push_back(objDevice);

            objDevice.Clear();
        }

    } catch (const std::exception&e)
    {
        nxLog << e.what() << std::endl;
        return false;
    }
    return true;

}