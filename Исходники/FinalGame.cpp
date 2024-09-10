void FinalGame::draw(double delta)
{
    static Window win;

    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(!multiView)
    {
        glViewport(0,0,win.getWidth(),win.getHeight());
        drawObjects();

        fb->Bind();
        glClearColor(0.0f,0.0f,0.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUniform1i(8,1);
        drawObjects();
        picking();
        glUniform1i(8,0);
        fb->Unbind();



    }
    else
        drawMultiCam();

    win.SwapBuffers();
}