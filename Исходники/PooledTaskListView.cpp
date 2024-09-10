void TaskContextListBoxModel::ItemComponent::paint (juce::Graphics& g)
{
	Colour colour (Colours::lightgrey);

	if (getTaskContext() != nullptr)
	{
		if (getTaskContext()->getState() == TaskContext::taskCompleted)
		{
			if (getTaskContext()->getResult().wasOk())
				colour = Colours::lightgreen;
			else colour = Colours::red.brighter();
		}
	}

	g.setColour (colour);
	g.fillRect(getLocalBounds());
	g.setColour (colour.darker(0.05f));
	g.drawHorizontalLine(getHeight()-1,0.0f,(float)getWidth());
}