//
// Render
//
void Render(unsigned Width, unsigned Height)
{
    g_ElapsedTime = GetElapsedMilliseconds();

    BeginFrame();

    glViewport(0, 0, Width, Height);
    glClear(GL_DEPTH_BUFFER_BIT); // No need to clear color buffer, because we draw background image
    
    g_View = XMMatrixTranslation(0.0f, 0.0f, g_Distance);
    g_Proj = XMMatrixPerspectiveFovRH(XMConvertToRadians(45.0f),
        Width / (float)Height, 0.1f, 100.0f);

    // Bunny rotation
    g_SpinX += g_ElapsedTime / 50.0f;

    // Setup light positions
    for (int i = 0; i < MAX_POINT_LIGHTS; ++i)
    {
        POINT_LIGHT_SOURCE *pLight = &g_PointLights[i]; 
        CalcLightPosition(pLight);
    }

    g_pBackground->SetScreenSize(Width, Height);
    g_pBackground->Draw();

    DrawBunny();
    DrawLights();
    DrawHUD(Width, Height);

    EndFrame();

    g_pFraps->OnPresent();
}