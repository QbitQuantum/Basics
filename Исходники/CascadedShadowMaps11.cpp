//--------------------------------------------------------------------------------------
// Calcaulte the camera based on size of the current scene
//--------------------------------------------------------------------------------------
void UpdateViewerCameraNearFar()
{
    XMVECTOR vMeshExtents = g_CascadedShadow.GetSceneAABBMax() - g_CascadedShadow.GetSceneAABBMin();
    XMVECTOR vMeshLength = XMVector3Length(vMeshExtents);
    FLOAT fMeshLength = XMVectorGetByIndex(vMeshLength, 0);
    g_ViewerCamera.SetProjParams(XM_PI / 4, g_fAspectRatio, 0.05f, fMeshLength);
}