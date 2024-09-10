//-------------------------------------------------------------------------------------
// Name: Update()
// Desc: Updates the world for the next frame
//-------------------------------------------------------------------------------------
void Update()
{
    // Set the world matrix
    float fAngle = fmodf( -g_Time.fAppTime, XM_2PI );
    static const XMVECTOR vAxisZ = { 0, 0, 1.0f, 0 };
    g_matWorld = XMMatrixRotationAxis( vAxisZ, fAngle );
}