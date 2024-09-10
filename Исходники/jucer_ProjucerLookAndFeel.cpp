void ProjucerLookAndFeel::drawCallOutBoxBackground (CallOutBox&, Graphics& g, const Path& path, Image&)
{
    g.setColour (findColour (secondaryBackgroundColourId));
    g.fillPath (path);

    g.setColour (findColour (userButtonBackgroundColourId));
    g.strokePath (path, PathStrokeType (2.0f));
}