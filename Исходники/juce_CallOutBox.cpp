void CallOutBox::updatePosition (const Rectangle<int>& newAreaToPointTo, const Rectangle<int>& newAreaToFitIn)
{
    targetArea = newAreaToPointTo;
    availableArea = newAreaToFitIn;

    const int borderSpace = getBorderSize();

    Rectangle<int> newBounds (content.getWidth()  + borderSpace * 2,
                              content.getHeight() + borderSpace * 2);

    const int hw = newBounds.getWidth() / 2;
    const int hh = newBounds.getHeight() / 2;
    const float hwReduced = (float) (hw - borderSpace * 2);
    const float hhReduced = (float) (hh - borderSpace * 2);
    const float arrowIndent = borderSpace - arrowSize;

    Point<float> targets[4] = { Point<float> ((float) targetArea.getCentreX(), (float) targetArea.getBottom()),
                                Point<float> ((float) targetArea.getRight(),   (float) targetArea.getCentreY()),
                                Point<float> ((float) targetArea.getX(),       (float) targetArea.getCentreY()),
                                Point<float> ((float) targetArea.getCentreX(), (float) targetArea.getY()) };

    Line<float> lines[4] = { Line<float> (targets[0].translated (-hwReduced, hh - arrowIndent),    targets[0].translated (hwReduced, hh - arrowIndent)),
                             Line<float> (targets[1].translated (hw - arrowIndent, -hhReduced),    targets[1].translated (hw - arrowIndent, hhReduced)),
                             Line<float> (targets[2].translated (-(hw - arrowIndent), -hhReduced), targets[2].translated (-(hw - arrowIndent), hhReduced)),
                             Line<float> (targets[3].translated (-hwReduced, -(hh - arrowIndent)), targets[3].translated (hwReduced, -(hh - arrowIndent))) };

    const Rectangle<float> centrePointArea (newAreaToFitIn.reduced (hw, hh).toFloat());
    const Point<float> targetCentre (targetArea.getCentre().toFloat());

    float nearest = 1.0e9f;

    for (int i = 0; i < 4; ++i)
    {
        Line<float> constrainedLine (centrePointArea.getConstrainedPoint (lines[i].getStart()),
                                     centrePointArea.getConstrainedPoint (lines[i].getEnd()));

        const Point<float> centre (constrainedLine.findNearestPointTo (targetCentre));
        float distanceFromCentre = centre.getDistanceFrom (targets[i]);

        if (! centrePointArea.intersects (lines[i]))
            distanceFromCentre += 1000.0f;

        if (distanceFromCentre < nearest)
        {
            nearest = distanceFromCentre;

            targetPoint = targets[i];
            newBounds.setPosition ((int) (centre.x - hw),
                                   (int) (centre.y - hh));
        }
    }

    setBounds (newBounds);
}