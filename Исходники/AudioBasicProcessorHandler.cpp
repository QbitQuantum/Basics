// As soon as we know the channel count of our input, we can lazily initialize.
// Sometimes this may be called more than once with different channel counts, in which case we must safely
// uninitialize and then re-initialize with the new channel count.
void AudioBasicProcessorHandler::checkNumberOfChannelsForInput(AudioNodeInput* input)
{
    ASSERT(context()->isAudioThread());
    ASSERT(context()->isGraphOwner());

    ASSERT(input == &this->input(0));
    if (input != &this->input(0))
        return;

    ASSERT(processor());
    if (!processor())
        return;

    unsigned numberOfChannels = input->numberOfChannels();

    if (isInitialized() && numberOfChannels != output(0).numberOfChannels()) {
        // We're already initialized but the channel count has changed.
        uninitialize();
    }

    if (!isInitialized()) {
        // This will propagate the channel count to any nodes connected further down the chain...
        output(0).setNumberOfChannels(numberOfChannels);

        // Re-initialize the processor with the new channel count.
        processor()->setNumberOfChannels(numberOfChannels);
        initialize();
    }

    AudioHandler::checkNumberOfChannelsForInput(input);
}