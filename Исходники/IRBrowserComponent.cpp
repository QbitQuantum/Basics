void IRBrowserComponent::paint(juce::Graphics& g)
{
  if (_fileTreeComponent && _infoLabel)
  {
    const int width = getWidth();
    const int height = getHeight();
    
    g.setColour(juce::Colour(0xE5, 0xE5, 0xF0));
    g.fillRect(0.0f, 0.0f, static_cast<float>(width), static_cast<float>(height));
    
    g.setColour(juce::Colours::grey);
    g.drawRect(0.0f, 0.0f, static_cast<float>(width), static_cast<float>(height));
    g.drawVerticalLine(_fileTreeComponent->getX()+_fileTreeComponent->getWidth(), 0.0f, static_cast<float>(height-1));
  }
}