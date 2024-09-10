void tgSimViewGraphics::displayCallback()
{
    if (isInitialzed())
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
        renderme();
        // optional but useful: debug drawing to detect problems
        if (m_dynamicsWorld)
        {
            m_dynamicsWorld->debugDrawWorld();
        }
        glFlush();
        swapBuffers();
    }
}