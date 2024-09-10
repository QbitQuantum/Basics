    //-----------------------------------------------------------------------
    void RenderTarget::update(bool swap)
    {
        OgreProfileBeginGPUEvent("RenderTarget: " + getName());
        // call implementation
        updateImpl();


        if (swap)
        {
            // Swap buffers
            swapBuffers();
        }
        OgreProfileEndGPUEvent("RenderTarget: " + getName());
    }