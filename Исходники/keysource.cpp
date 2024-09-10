void KeySource::processLayerChange(const LayerStack::Mask& currentMask,
                                   const LayerStack::Mask& nextMask,
                                   EventStage&             next)
{
    mKeyHardware.pressed(KeyHardwareEventHandler::create([&](const KeyHardwareEvent& event)
    {
        auto currentEvent(mLayerStack.at(currentMask,
                                        event.row,
                                        event.column));
        
        auto nextEvent(mLayerStack.at(nextMask,
                                     event.row,
                                     event.column));

        if (currentEvent != nextEvent)
        {
            next.processEvent(currentEvent.invert());
            next.processEvent(nextEvent);
        }
    }));
}