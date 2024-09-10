// FIXME: this can go away when we do mixing with gain directly in summing junction of AudioNodeInput
//
// As soon as we know the channel count of our input, we can lazily initialize.
// Sometimes this may be called more than once with different channel counts, in which case we must safely
// uninitialize and then re-initialize with the new channel count.
void GainNode::checkNumberOfChannelsForInput(ContextRenderLock& r, AudioNodeInput* input)
{
    if (!input)
        return;

    ASSERT(r.context());

    if (input != this->input(0).get())
        return;
        
    unsigned numberOfChannels = input->numberOfChannels(r);
    
    if (isInitialized() && numberOfChannels != output(0)->numberOfChannels())
    {
        // We're already initialized but the channel count has changed.
        uninitialize();
    }

    if (!isInitialized())
    {
        // This will propagate the channel count to any nodes connected further downstream in the graph.
        output(0)->setNumberOfChannels(r, numberOfChannels);
        initialize();
    }

    AudioNode::checkNumberOfChannelsForInput(r, input);
}