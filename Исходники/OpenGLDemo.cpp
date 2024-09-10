    void drawBackground2DStuff()
    {
        // Create an OpenGLGraphicsContext that will draw into this GL window..
        ScopedPointer<LowLevelGraphicsContext> glRenderer (createOpenGLGraphicsContext (openGLContext,
                                                                                        getContextWidth(),
                                                                                        getContextHeight()));

        if (glRenderer != nullptr)
        {
            Graphics g (glRenderer);
            g.addTransform (AffineTransform::scale ((float) getScale()));

            // This stuff just creates a spinning star shape and fills it..
            Path p;
            const float scale = getHeight() * 0.4f;
            p.addStar (Point<float> (getWidth() * 0.7f, getHeight() * 0.4f), 7,
                       scale * (float) sizeSlider.getValue(), scale,
                       rotation / 50.0f);

            g.setGradientFill (ColourGradient (Colours::green.withRotatedHue (fabsf (::sinf (rotation / 300.0f))),
                                               0, 0,
                                               Colours::green.withRotatedHue (fabsf (::cosf (rotation / -431.0f))),
                                               0, (float) getHeight(), false));
            g.fillPath (p);
        }
    }