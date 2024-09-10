Profile* HMDDeviceCreateDesc::GetProfileAddRef() const
{
    // Create device may override profile name, so get it from there is possible.
    ProfileManager* profileManager = GetManagerImpl()->GetProfileManager();
    ProfileType     profileType    = GetProfileType();
    const char *    profileName    = pDevice ?
                        ((HMDDevice*)pDevice)->GetProfileName() :
                        profileManager->GetDefaultProfileName(profileType);
    
    return profileName ? 
        profileManager->LoadProfile(profileType, profileName) :
        profileManager->GetDeviceDefaultProfile(profileType);
}