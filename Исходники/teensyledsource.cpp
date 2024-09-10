void TeensyLedSource::pollEvent(EventStage& next)
{
    if (keyboard_leds != mMaskValue)
    {
        mMaskValue = keyboard_leds;
        
        next.processEvent(LedMaskEvent::create(mMaskValue));
    }
}