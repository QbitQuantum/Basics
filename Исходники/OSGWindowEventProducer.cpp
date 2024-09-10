void WindowEventProducer::produceKeyTyped(const KeyEventDetails::Key& TheKey, const UInt32& Modifiers)
{
    //Check if Input is blocked
    if(_BlockInput) { return; }

   KeyEventDetailsUnrecPtr Details = KeyEventDetails::create( this, getSystemTime(), TheKey, Modifiers, this );

   WindowEventProducerBase::produceKeyTyped(Details);
}