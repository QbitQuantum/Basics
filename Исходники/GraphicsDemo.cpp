    void drawDemo (Graphics& g) override
    {
        const Path& p = logoPath;

        if (useLinearGradient || useRadialGradient)
        {
            Colour c1 (gradientColours[0].getValue(), gradientColours[1].getValue(), gradientColours[2].getValue(), 1.0f);
            Colour c2 (gradientColours[3].getValue(), gradientColours[4].getValue(), gradientColours[5].getValue(), 1.0f);
            Colour c3 (gradientColours[6].getValue(), gradientColours[7].getValue(), gradientColours[8].getValue(), 1.0f);

            float x1 = gradientPositions[0].getValue() * getWidth()  * 0.25f;
            float y1 = gradientPositions[1].getValue() * getHeight() * 0.25f;
            float x2 = gradientPositions[2].getValue() * getWidth()  * 0.75f;
            float y2 = gradientPositions[3].getValue() * getHeight() * 0.75f;

            ColourGradient gradient (c1, x1, y1,
                                     c2, x2, y2,
                                     useRadialGradient);

            gradient.addColour (gradientIntermediate.getValue(), c3);

            g.setGradientFill (gradient);
        }
        else
        {
            g.setColour (Colours::blue);
        }

        g.setOpacity (getAlpha());
        g.fillPath (p, getTransform());
    }