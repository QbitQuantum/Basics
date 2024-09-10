void ZenAudioProcessorValueTreeState::valueTreePropertyChanged(ValueTree& tree, const Identifier& prop)
{
	if (prop == idPropertyID && tree.hasType(valueType) && tree.getParent() == state)
		updateParameterConnectionsToChildTrees();
}