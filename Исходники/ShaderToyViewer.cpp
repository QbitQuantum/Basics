void MyWindow::display()
{
    WindowInertiaCamera::display();
    glClearColor(0.4f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    //
    // timing for frames
    //
    //ViewerStates::realtime.update(true);
    ViewerStates::fTime += (float)m_realtime.frameDT;
    //
    // SCENE-LEVEL TEST
    //
    nvFX::PassInfo pr;
    memset(&pr, 0, sizeof(pr));
    if(fx_TechScene)
    {
        int np = fx_TechScene->getNumPasses();
        for(int i=0; i<np; i++)
        {
            nvFX::IPass* scenePass = fx_TechScene->getPass(i, &pr);
            if(!pr.bActive)
                continue;
            if(!scenePass->isValidated())
            {
                continue;
            }
            pr.renderingGroup = 0; // set back to 0 before each pass. So no persistent value across passes
            scenePass->execute(&pr);
            iResolution->updateValue3f((float)m_W, (float)m_H, 0, scenePass);
            iGlobalTime->updateValue1f(ViewerStates::fTime, scenePass);
            iMouse->updateValue4fv(m_mouse, scenePass);
            //iDate       = fx_EffectScene->findUniform("iDate");
            //iSampleRate = fx_EffectScene->findUniform("iSampleRate");
            switch(pr.renderingMode)
            {
            default:
                break;
            }
    glUseProgram(0);
        }
    }
    // Draw tweak bars
#ifdef USEANTTWEAKBAR
    //TwDraw();
#endif
    swapBuffers();
}