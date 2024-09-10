    void BulletOpenGLViewer::displayCallback()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (m_dynamicsWorld)
        {
            m_dynamicsWorld->debugDrawWorld();
        }

        renderme();

        glFlush();
        swapBuffers();
    }