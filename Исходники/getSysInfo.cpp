void dectectOS() //TODO:Fix this as it doesn't know how to check version
{
    char *osVersion;
    //if(IsWindows10OrGreater()) osVersion = "Windows 10";
    if(IsWindows8Point1OrGreater()) osVersion = "Windows 8.1";
    else if(IsWindows8OrGreater()) osVersion = "Windows 8";
    else if(IsWindows7SP1OrGreater()) osVersion = "Windows 7 Service Pack 1";
    else if(IsWindowsVistaSP2OrGreater()) osVersion = "Windows Vista Service Pack 2";
    else if(IsWindowsVistaSP1OrGreater()) osVersion = "Windows Vista Service Pack 1";
    else if(IsWindowsVistaOrGreater()) osVersion = "Windows Vista";
    else if(IsWindowsXPSP3OrGreater()) osVersion = "Windows XP Service Pack 3";
    else if(IsWindowsXPSP2OrGreater()) osVersion = "Windows XP Service Pack 2";
    else if(IsWindowsXPSP1OrGreater()) osVersion = "Windows XP Service Pack 1";
    else if(IsWindowsXPOrGreater()) osVersion = "Windows XP";
    else if(IsWindowsServer()) osVersion = "Windows Server";

    printf("\nOS Version : %s", osVersion);
}