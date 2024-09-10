    void paint (Graphics& g)
    {
        Path p;
        const float h = (float) getHeight();
        p.addEllipse (2.0f, 2.0f, h - 4.0f, h - 4.0f);
        p.startNewSubPath (h - 2.0f, h / 2.0f);
        p.lineTo ((float) getWidth(), h / 2.0f);

        g.setColour (findColour (TreeView::dragAndDropIndicatorColourId, true));
        g.strokePath (p, PathStrokeType (2.0f));
    }