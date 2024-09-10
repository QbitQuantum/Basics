// ----------------------------------------------------------------
// gets the location of the specified eye
// ----------------------------------------------------------------
Ogre::Matrix4 OgreOpenVR::getHMDMatrixPoseEye(vr::Hmd_Eye nEye)
{
    if (!m_pHMD)
        return Ogre::Matrix4();

    vr::HmdMatrix34_t matEye = m_pHMD->GetEyeToHeadTransform(nEye);    
    Ogre::Matrix4 eyeTransform = convertSteamVRMatrixToOgreMatrix4(matEye);

    return eyeTransform.inverse();
}