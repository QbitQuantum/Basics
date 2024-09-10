void SolidColour::paint (Graphics& g, const Rectangle<int>& bounds)
{
    g.setColour (m_colour);
    g.fillRect (bounds);
}